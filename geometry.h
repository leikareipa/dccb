/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "common.h"
#include "types.h"

typedef struct
{
    i32 x, y, z, w;
    i16 uv[2];
}
vertex4_s;

typedef struct
{
    vertex4_s v[3];

    /* If the texture pointer is NULL, baseColor will be used instead when
     * rendering this triangle.*/
    u8 *texturePtr;
    palette_idx baseColor;
}
triangle_s;

typedef struct
{
    real data[4*4];
}
matrix44_s;

typedef struct
{
    triangle_s *tris;
    u32 n;
}
triangle_mesh_s;

void kg_initialize_geometry(const resolution_s *const res);

void kg_release_geometry(void);

void kg_transform_scene(triangle_mesh_s *const dst, const triangle_mesh_s *const src);

#endif
