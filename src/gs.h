/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef GEOMETRY_PC_H
#define GEOMETRY_PC_H

#include "geometry.h"

void g_transform_vert(vertex4_s *const v, const matrix44_s *const m);

void g_mul_two_mats(const matrix44_s *const m1, const matrix44_s *const m2, matrix44_s *const dst);

void g_make_rot_mat(matrix44_s *const m, u16 x, u16 y, u16 z);

void g_make_transl_mat(matrix44_s *const m, const i32 x, const i32 y, const i32 z);

void g_make_persp_mat(matrix44_s *const m, const real fov, const real aspectRatio, const i32 zNear, const i32 zFar);

void g_make_scaling_mat(matrix44_s *const m, const i32 x, const i32 y, const i32 z);

void g_make_screen_space_mat(matrix44_s *const m, const real halfWidth, const real halfHeight);

#endif
