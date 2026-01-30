#include "../timed_remote.h"
#include "timed_remote_scene.h"

enum {
  MainMenuIndexStartTimer,
};

static void main_menu_callback(void *context, uint32_t index) {
  TimedRemoteApp *app = context;
  if (index == MainMenuIndexStartTimer) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventStartTimer);
  }
}

void timed_remote_scene_main_menu_on_enter(void *context) {
  TimedRemoteApp *app = context;

  submenu_reset(app->submenu);
  submenu_set_header(app->submenu, "Timed Remote");
  submenu_add_item(app->submenu, "Start New Timer", MainMenuIndexStartTimer,
                   main_menu_callback, app);

  view_dispatcher_switch_to_view(app->view_dispatcher, TimedRemoteViewSubmenu);
}

bool timed_remote_scene_main_menu_on_event(void *context,
                                           SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventStartTimer) {
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneIrSource);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_main_menu_on_exit(void *context) {
  TimedRemoteApp *app = context;
  submenu_reset(app->submenu);
}
