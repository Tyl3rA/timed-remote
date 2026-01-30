#include "../timed_remote.h"
#include "timed_remote_scene.h"

enum {
  TimerModeIndexCountdown,
  TimerModeIndexScheduled,
};

static void timer_mode_callback(void *context, uint32_t index) {
  TimedRemoteApp *app = context;
  if (index == TimerModeIndexCountdown) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventModeCountdown);
  } else if (index == TimerModeIndexScheduled) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventModeScheduled);
  }
}

void timed_remote_scene_timer_mode_on_enter(void *context) {
  TimedRemoteApp *app = context;

  submenu_reset(app->submenu);
  submenu_set_header(app->submenu, "Timer Mode");
  submenu_add_item(app->submenu, "Countdown (in X time)",
                   TimerModeIndexCountdown, timer_mode_callback, app);
  submenu_add_item(app->submenu, "Scheduled (at X time)",
                   TimerModeIndexScheduled, timer_mode_callback, app);

  view_dispatcher_switch_to_view(app->view_dispatcher, TimedRemoteViewSubmenu);
}

bool timed_remote_scene_timer_mode_on_event(void *context,
                                            SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventModeCountdown) {
      app->timer_mode = TimerModeCountdown;
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneTimeInput);
      consumed = true;
    } else if (event.event == TimedRemoteEventModeScheduled) {
      app->timer_mode = TimerModeScheduled;
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneTimeInput);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_timer_mode_on_exit(void *context) {
  TimedRemoteApp *app = context;
  submenu_reset(app->submenu);
}
