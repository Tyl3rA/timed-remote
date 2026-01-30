#include "../timed_remote.h"
#include "timed_remote_scene.h"

enum {
  RepeatOptionsIndexToggle,
  RepeatOptionsIndexCount,
  RepeatOptionsIndexConfirm,
};

static void repeat_toggle_change(VariableItem *item) {
  TimedRemoteApp *app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  app->repeat_enabled = (index == 1);
  variable_item_set_current_value_text(item,
                                       app->repeat_enabled ? "On" : "Off");
}

static void repeat_count_change(VariableItem *item) {
  TimedRemoteApp *app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  app->repeat_count = index; /* 0 = unlimited, 1-99 = fixed */

  char buf[16];
  if (app->repeat_count == 0) {
    snprintf(buf, sizeof(buf), "Unlimited");
  } else {
    snprintf(buf, sizeof(buf), "%d", app->repeat_count);
  }
  variable_item_set_current_value_text(item, buf);
}

static void repeat_options_enter_callback(void *context, uint32_t index) {
  TimedRemoteApp *app = context;
  if (index == RepeatOptionsIndexConfirm) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventRepeatConfigured);
  }
}

void timed_remote_scene_repeat_options_on_enter(void *context) {
  TimedRemoteApp *app = context;
  VariableItem *item;

  variable_item_list_reset(app->variable_item_list);

  /* Repeat toggle: Off/On */
  item = variable_item_list_add(app->variable_item_list, "Repeat", 2,
                                repeat_toggle_change, app);
  variable_item_set_current_value_index(item, app->repeat_enabled ? 1 : 0);
  variable_item_set_current_value_text(item,
                                       app->repeat_enabled ? "On" : "Off");

  /* Repeat count: 0 = unlimited, 1-99 = fixed */
  item = variable_item_list_add(app->variable_item_list, "Count", 100,
                                repeat_count_change, app);
  variable_item_set_current_value_index(item, app->repeat_count);
  if (app->repeat_count == 0) {
    variable_item_set_current_value_text(item, "Unlimited");
  } else {
    char buf[8];
    snprintf(buf, sizeof(buf), "%d", app->repeat_count);
    variable_item_set_current_value_text(item, buf);
  }

  /* Confirm button */
  variable_item_list_add(app->variable_item_list, ">> Start Timer <<", 0, NULL,
                         NULL);

  variable_item_list_set_enter_callback(app->variable_item_list,
                                        repeat_options_enter_callback, app);

  view_dispatcher_switch_to_view(app->view_dispatcher,
                                 TimedRemoteViewVariableItemList);
}

bool timed_remote_scene_repeat_options_on_event(void *context,
                                                SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventRepeatConfigured) {
      /* Initialize repeats remaining */
      app->repeats_remaining =
          app->repeat_enabled
              ? (app->repeat_count == 0 ? 255 : app->repeat_count)
              : 1;
      scene_manager_next_scene(app->scene_manager,
                               TimedRemoteSceneTimerRunning);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_repeat_options_on_exit(void *context) {
  TimedRemoteApp *app = context;
  variable_item_list_reset(app->variable_item_list);
}
