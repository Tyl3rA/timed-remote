#pragma once

#include <gui/scene_manager.h>

/* Scene IDs */
typedef enum {
  TimedRemoteSceneMainMenu,
  TimedRemoteSceneIrSource,
  TimedRemoteSceneIrRecord,
  TimedRemoteSceneSignalName,
  TimedRemoteSceneIrBrowse,
  TimedRemoteSceneIrSelect,
  TimedRemoteSceneTimerMode,
  TimedRemoteSceneTimeInput,
  TimedRemoteSceneRepeatOptions,
  TimedRemoteSceneTimerRunning,
  TimedRemoteSceneConfirm,
  TimedRemoteSceneCount,
} TimedRemoteScene;

/* Scene event IDs */
typedef enum {
  TimedRemoteSceneEventConsumed = true,
  TimedRemoteSceneEventNotConsumed = false,
} TimedRemoteSceneEvent;

/* Custom events */
typedef enum {
  /* Main menu */
  TimedRemoteEventStartTimer,
  /* IR source */
  TimedRemoteEventRecordSignal,
  TimedRemoteEventBrowseFiles,
  /* Recording complete */
  TimedRemoteEventRecordComplete,
  /* File/signal selected */
  TimedRemoteEventFileSelected,
  TimedRemoteEventSignalSelected,
  /* Timer mode */
  TimedRemoteEventModeCountdown,
  TimedRemoteEventModeScheduled,
  /* Time input complete */
  TimedRemoteEventTimeSet,
  /* Repeat options */
  TimedRemoteEventRepeatConfigured,
  /* Timer events */
  TimedRemoteEventTimerTick,
  TimedRemoteEventTimerFired,
  /* Confirmation */
  TimedRemoteEventConfirmDone,
} TimedRemoteCustomEvent;

/* Scene handlers - declared extern, defined in individual scene files */
extern void timed_remote_scene_main_menu_on_enter(void *context);
extern bool timed_remote_scene_main_menu_on_event(void *context,
                                                  SceneManagerEvent event);
extern void timed_remote_scene_main_menu_on_exit(void *context);

extern void timed_remote_scene_ir_source_on_enter(void *context);
extern bool timed_remote_scene_ir_source_on_event(void *context,
                                                  SceneManagerEvent event);
extern void timed_remote_scene_ir_source_on_exit(void *context);

extern void timed_remote_scene_ir_record_on_enter(void *context);
extern bool timed_remote_scene_ir_record_on_event(void *context,
                                                  SceneManagerEvent event);
extern void timed_remote_scene_ir_record_on_exit(void *context);

extern void timed_remote_scene_signal_name_on_enter(void *context);
extern bool timed_remote_scene_signal_name_on_event(void *context,
                                                    SceneManagerEvent event);
extern void timed_remote_scene_signal_name_on_exit(void *context);

extern void timed_remote_scene_ir_browse_on_enter(void *context);
extern bool timed_remote_scene_ir_browse_on_event(void *context,
                                                  SceneManagerEvent event);
extern void timed_remote_scene_ir_browse_on_exit(void *context);

extern void timed_remote_scene_ir_select_on_enter(void *context);
extern bool timed_remote_scene_ir_select_on_event(void *context,
                                                  SceneManagerEvent event);
extern void timed_remote_scene_ir_select_on_exit(void *context);

extern void timed_remote_scene_timer_mode_on_enter(void *context);
extern bool timed_remote_scene_timer_mode_on_event(void *context,
                                                   SceneManagerEvent event);
extern void timed_remote_scene_timer_mode_on_exit(void *context);

extern void timed_remote_scene_time_input_on_enter(void *context);
extern bool timed_remote_scene_time_input_on_event(void *context,
                                                   SceneManagerEvent event);
extern void timed_remote_scene_time_input_on_exit(void *context);

extern void timed_remote_scene_repeat_options_on_enter(void *context);
extern bool timed_remote_scene_repeat_options_on_event(void *context,
                                                       SceneManagerEvent event);
extern void timed_remote_scene_repeat_options_on_exit(void *context);

extern void timed_remote_scene_timer_running_on_enter(void *context);
extern bool timed_remote_scene_timer_running_on_event(void *context,
                                                      SceneManagerEvent event);
extern void timed_remote_scene_timer_running_on_exit(void *context);

extern void timed_remote_scene_confirm_on_enter(void *context);
extern bool timed_remote_scene_confirm_on_event(void *context,
                                                SceneManagerEvent event);
extern void timed_remote_scene_confirm_on_exit(void *context);
