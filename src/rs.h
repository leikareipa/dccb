/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef SOFTWARE_REND_H
#define SOFTWARE_REND_H

#include "renderer.h"

void rs_init_tri_filler(frame_buffer_s *const frameBuffer);

void rs_fill_tri(triangle_s *const t);

u8 r_texture_color_at(const u8 u, const u8 v, const i16 texId);

#endif
