/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"

void kd_acquire_display(const frame_buffer_s *const fb);

void kd_release_display(void);

void kd_update_display(const frame_buffer_s *const fb);

#endif
