#pragma once

#include <furi.h>
#include <infrared.h>
#include <lib/infrared/signal/infrared_signal.h>

/**
 * IR signal container with name.
 */
typedef struct {
  InfraredSignal *signal;
  FuriString *name;
} IrSignalItem;

/**
 * List of signals parsed from an .ir file.
 */
typedef struct {
  IrSignalItem *items;
  size_t count;
  size_t capacity;
} IrSignalList;

/**
 * Allocate an IR signal list.
 */
IrSignalList *ir_signal_list_alloc(void);

/**
 * Free an IR signal list and all contained signals.
 */
void ir_signal_list_free(IrSignalList *list);

/**
 * Record an IR signal from the receiver.
 * Blocks until signal is received or timeout.
 *
 * @param signal Output: allocated InfraredSignal (caller must free)
 * @param timeout_ms Timeout in milliseconds
 * @return true if signal recorded, false on timeout/error
 */
bool ir_helper_record(InfraredSignal **signal, uint32_t timeout_ms);

/**
 * Save a signal to an .ir file (appends if file exists).
 *
 * @param signal The signal to save
 * @param name Signal name (e.g., "Power")
 * @param path File path (e.g., "/ext/infrared/timed_remote.ir")
 * @return true on success
 */
bool ir_helper_save(InfraredSignal *signal, const char *name, const char *path);

/**
 * Load all signals from an .ir file.
 *
 * @param path File path to load
 * @param list Output list of signals
 * @return true on success
 */
bool ir_helper_load_file(const char *path, IrSignalList *list);

/**
 * Transmit an IR signal.
 *
 * @param signal The signal to transmit
 */
void ir_helper_transmit(InfraredSignal *signal);

/**
 * List .ir files in a directory.
 *
 * @param dir_path Directory path (e.g., "/ext/infrared")
 * @param files Output: array of FuriString* (caller frees)
 * @param count Output: number of files
 * @return true on success
 */
bool ir_helper_list_files(const char *dir_path, FuriString ***files,
                          size_t *count);

/**
 * Free a list of file paths.
 */
void ir_helper_free_file_list(FuriString **files, size_t count);
