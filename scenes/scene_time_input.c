#include "../timed_remote.h"
#include "timed_remote_scene.h"

/* State indices for VariableItemList */
enum {
  TimeInputIndexHours,
  TimeInputIndexMinutes,
  TimeInputIndexSeconds,
  TimeInputIndexConfirm,
};

static void time_input_hours_change(VariableItem *item) {
  TimedRemoteApp *app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  app->hours = index;
  char buf[4];
  snprintf(buf, sizeof(buf), "%02d", app->hours);
  variable_item_set_current_value_text(item, buf);
}

static void time_input_minutes_change(VariableItem *item) {
  TimedRemoteApp *app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  app->minutes = index;
  char buf[4];
  snprintf(buf, sizeof(buf), "%02d", app->minutes);
  variable_item_set_current_value_text(item, buf);
}

static void time_input_seconds_change(VariableItem *item) {
  TimedRemoteApp *app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  app->seconds = index;
  char buf[4];
  snprintf(buf, sizeof(buf), "%02d", app->seconds);
  variable_item_set_current_value_text(item, buf);
}

static void time_input_enter_callback(void *context, uint32_t index) {
  TimedRemoteApp *app = context;
  if (index == TimeInputIndexConfirm) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventTimeSet);
  }
}

void timed_remote_scene_time_input_on_enter(void *context) {
  TimedRemoteApp *app = context;
  VariableItem *item;
  char buf[4];

  variable_item_list_reset(app->variable_item_list);

  /* Note: VariableItemList doesn't support headers, the mode context is
   * implicit */

  /* Hours: 0-23 */
  item = variable_item_list_add(app->variable_item_list, "Hours", 24,
                                time_input_hours_change, app);
  variable_item_set_current_value_index(item, app->hours);
  snprintf(buf, sizeof(buf), "%02d", app->hours);
  variable_item_set_current_value_text(item, buf);

  /* Minutes: 0-59 */
  item = variable_item_list_add(app->variable_item_list, "Minutes", 60,
                                time_input_minutes_change, app);
  variable_item_set_current_value_index(item, app->minutes);
  snprintf(buf, sizeof(buf), "%02d", app->minutes);
  variable_item_set_current_value_text(item, buf);

  /* Seconds: 0-59 */
  item = variable_item_list_add(app->variable_item_list, "Seconds", 60,
                                time_input_seconds_change, app);
  variable_item_set_current_value_index(item, app->seconds);
  snprintf(buf, sizeof(buf), "%02d", app->seconds);
  variable_item_set_current_value_text(item, buf);

  /* Confirm button */
  variable_item_list_add(app->variable_item_list, ">> Start Timer <<", 0, NULL,
                         NULL);

  variable_item_list_set_enter_callback(app->variable_item_list,
                                        time_input_enter_callback, app);

  view_dispatcher_switch_to_view(app->view_dispatcher,
                                 TimedRemoteViewVariableItemList);
}

bool timed_remote_scene_time_input_on_event(void *context,
                                            SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventTimeSet) {
      if (app->timer_mode == TimerModeCountdown) {
        /* Countdown mode - go to repeat options */
        scene_manager_next_scene(app->scene_manager,
                                 TimedRemoteSceneRepeatOptions);
      } else {
        /* Scheduled mode - go directly to timer */
        app->repeat_enabled = false;
        scene_manager_next_scene(app->scene_manager,
                                 TimedRemoteSceneTimerRunning);
      }
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_time_input_on_exit(void *context) {
  TimedRemoteApp *app = context;
  variable_item_list_reset(app->variable_item_list);
}
