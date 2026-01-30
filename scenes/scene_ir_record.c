#include "../helpers/ir_helper.h"
#include "../timed_remote.h"
#include "timed_remote_scene.h"

#define RECORD_TIMEOUT_MS 30000

void timed_remote_scene_ir_record_on_enter(void *context) {
  TimedRemoteApp *app = context;

  widget_reset(app->widget);
  widget_add_string_element(app->widget, 64, 10, AlignCenter, AlignTop,
                            FontPrimary, "Recording IR...");
  widget_add_string_element(app->widget, 64, 26, AlignCenter, AlignTop,
                            FontSecondary, "Point remote at Flipper");
  widget_add_string_element(app->widget, 64, 40, AlignCenter, AlignTop,
                            FontSecondary, "and press a button");

  view_dispatcher_switch_to_view(app->view_dispatcher, TimedRemoteViewWidget);

  /* Start recording in a thread or use async approach */
  /* For now, blocking call - consider making async for better UX */
  InfraredSignal *signal = NULL;
  bool success = ir_helper_record(&signal, RECORD_TIMEOUT_MS);

  if (success && signal) {
    /* Free any previous signal */
    if (app->ir_signal) {
      infrared_signal_free(app->ir_signal);
    }
    app->ir_signal = signal;
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventRecordComplete);
  } else {
    /* Timeout or error - go back */
    scene_manager_previous_scene(app->scene_manager);
  }
}

bool timed_remote_scene_ir_record_on_event(void *context,
                                           SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventRecordComplete) {
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneSignalName);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_ir_record_on_exit(void *context) {
  TimedRemoteApp *app = context;
  widget_reset(app->widget);
}
