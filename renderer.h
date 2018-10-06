/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "geometry.h"

const frame_buffer_s* kr_acquire_renderer(void);

void kr_release_renderer();

frame_buffer_s* kr_render_scene(triangle_mesh_s *const scene);

void kr_init_texture_cache(void);

void kr_release_texture_cache(void);

void kr_load_textures(void);

#endif
