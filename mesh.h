/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef MESH_FILE_H
#define MESH_FILE_H

#include "geometry.h"

void kmesh_load_triangle_mesh_from_file(const char *const filename, triangle_mesh_s *const mesh);

#endif
