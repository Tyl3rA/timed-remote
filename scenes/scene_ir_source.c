#include "../timed_remote.h"
#include "timed_remote_scene.h"

enum {
  IrSourceIndexRecord,
  IrSourceIndexBrowse,
};

static void ir_source_callback(void *context, uint32_t index) {
  TimedRemoteApp *app = context;
  if (index == IrSourceIndexRecord) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventRecordSignal);
  } else if (index == IrSourceIndexBrowse) {
    view_dispatcher_send_custom_event(app->view_dispatcher,
                                      TimedRemoteEventBrowseFiles);
  }
}

void timed_remote_scene_ir_source_on_enter(void *context) {
  TimedRemoteApp *app = context;

  submenu_reset(app->submenu);
  submenu_set_header(app->submenu, "Select IR Source");
  submenu_add_item(app->submenu, "Record New Signal", IrSourceIndexRecord,
                   ir_source_callback, app);
  submenu_add_item(app->submenu, "Browse IR Files", IrSourceIndexBrowse,
                   ir_source_callback, app);

  view_dispatcher_switch_to_view(app->view_dispatcher, TimedRemoteViewSubmenu);
}

bool timed_remote_scene_ir_source_on_event(void *context,
                                           SceneManagerEvent event) {
  TimedRemoteApp *app = context;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == TimedRemoteEventRecordSignal) {
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneIrRecord);
      consumed = true;
    } else if (event.event == TimedRemoteEventBrowseFiles) {
      scene_manager_next_scene(app->scene_manager, TimedRemoteSceneIrBrowse);
      consumed = true;
    }
  }

  return consumed;
}

void timed_remote_scene_ir_source_on_exit(void *context) {
  TimedRemoteApp *app = context;
  submenu_reset(app->submenu);
}
