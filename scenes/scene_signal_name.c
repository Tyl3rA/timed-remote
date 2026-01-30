#include "../helpers/ir_helper.h"
#include "../helpers/time_helper.h"
#include "../timed_remote.h"
#include "timed_remote_scene.h"

#define TIMED_REMOTE_IR_PATH "/ext/infrared/timed_remote.ir"

static void signal_name_text_input_callback(void *context) {
  TimedRemoteApp *app = context;
  view_dispatcher_send_custom_event(app->view_dispatcher,
                                    TimedRemoteEventRecordComplete);
}

void timed_remote_scene_signal_name_on_enter(void *context) {
  TimedRemoteApp *app = context;

  /* Generate default name based on timestamp */
  time_helper_generate_signal_name(app->text_input_buffer,
                                   sizeof(app->text_input_buffer));

  text_input_reset(app->text_input);
  text_input_set_header_text(app->text_input, "Name this signal:");
  text_input_set_result_callback(
      app->text_input, signal_name_text_input_callback, app,
      app->text_input_buffer, sizeof(app->text_input_buffer),
      true /* clear default text on focus */);

  view_dispatcher_switch_to_view(app->view_dispatcher,
                                 TimedRemoteViewTextInput);
}

bool timed_remote_scene_signal_name_on_event(void *context,
                                             SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventRecordComplete) {
      /* Save the signal name */
      strncpy(app->signal_name, app->text_input_buffer,
              sizeof(app->signal_name) - 1);
      app->signal_name[sizeof(app->signal_name) - 1] = '\0';

      /* Save signal to file */
      if (app->ir_signal) {
        ir_helper_save(app->ir_signal, app->signal_name, TIMED_REMOTE_IR_PATH);
      }

      /* Proceed to timer mode selection */
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneTimerMode);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_signal_name_on_exit(void *context) {
  TimedRemoteApp *app = context;
  text_input_reset(app->text_input);
}
