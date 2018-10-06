/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark, geometry
 *
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rs.h"
#include "gs.h"
#include "geometry.h"

static const i32 NEAR_CLIP = 1;
static const i32 FAR_CLIP = 2000;

static matrix44_s SCREEN_SPACE_MAT;
static matrix44_s PERSP_MAT;

void kg_initialize_geometry(const resolution_s *const res)
{
    g_make_screen_space_mat(&SCREEN_SPACE_MAT, (res->w / 2.0f), (res->h / 2.0f));
    g_make_persp_mat(&PERSP_MAT, DEG_TO_RAD(60), (res->w / (real)res->h), NEAR_CLIP, FAR_CLIP);

    return;
}

void kg_release_geometry(void)
{
    return;
}

static void g_tri_perspective_divide(triangle_s *const t)
{
    u16 i;

    for (i = 0; i < 3; i++)
    {
        t->v[i].x /= t->v[i].w;
        t->v[i].y /= t->v[i].w;
        t->v[i].z /= t->v[i].w;
    }

    return;
}

/* Back-face culling. (http://stackoverflow.com/questions/35273279/backface-removal-for-perspective-projection.)*/
static uint g_tri_is_facing_camera(const triangle_s *const t)
{
    i32 ax = t->v[0].x - t->v[1].x;
    i32 ay = t->v[0].y - t->v[1].y;
    i32 bx = t->v[0].x - t->v[2].x;
    i32 by = t->v[0].y - t->v[2].y;
    i32 cz = (ax * by) - (ay * bx);

    if (cz >= 0)
    {
        return 0;
    }

    return 1;
}

void kg_transform_scene(triangle_mesh_s *const dst, const triangle_mesh_s *const src)
{
    u16 i, k = 0;
    matrix44_s rotation, transl, worldSpace, clipSpace;

	/* For some visual interest, make the scene rotate.*/
    static u16 rot = 0;
    rot += (7 << 6);

    /* Create the world-space matrix from the translation and rotation matrices,
	 * and pre-bake the perspective matrix into the world space matrix, producing
     * the clip-space matrix.*/
    g_make_transl_mat(&transl, 0, 0, 120);
    g_make_rot_mat(&rotation, rot, rot, rot);
    g_mul_two_mats(&transl, &rotation, &worldSpace);
    g_mul_two_mats(&PERSP_MAT, &worldSpace, &clipSpace);

    for (i = 0; i < src->n; i++)
    {
        int triIsVisible = 1;

        dst->tris[k] = src->tris[i];

        /* Transform into clip-space.*/
        g_transform_vert(&dst->tris[k].v[0], &clipSpace);
        g_transform_vert(&dst->tris[k].v[1], &clipSpace);
        g_transform_vert(&dst->tris[k].v[2], &clipSpace);

		/* Something might happen in clip-space at some point.*/

        /* Transform into screen-space.*/
        g_transform_vert(&dst->tris[k].v[0], &SCREEN_SPACE_MAT);
        g_transform_vert(&dst->tris[k].v[1], &SCREEN_SPACE_MAT);
        g_transform_vert(&dst->tris[k].v[2], &SCREEN_SPACE_MAT);
        g_tri_perspective_divide(&dst->tris[k]);

        /* Back-face culling.*/
        if (!g_tri_is_facing_camera(&dst->tris[k]))
        {
            triIsVisible = 0;
        }

        /* Depth clipping.*/
        if (dst->tris[k].v[0].w >= FAR_CLIP ||
            dst->tris[k].v[0].w <= NEAR_CLIP)
        {
            triIsVisible = 0;
        }

        /* If the triangle is visible, allow it to be drawn. If it's not, the
         * next triangle, indexed with k, will overwrite this one.*/
        if (triIsVisible)
        {
            k++;
        }
    }

    dst->n = k;

    return;
}
