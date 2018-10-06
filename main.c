/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "geometry.h"
#include "renderer.h"
#include "display.h"
#include "common.h"
#include "types.h"
#include "mesh.h"

/* For how many seconds to let the test run.*/
static const u16 TEST_DUR_SEC = 20;

static void k_initialize_system(void)
{
    const frame_buffer_s *const fb = kr_acquire_renderer();
    kr_init_texture_cache();
    kr_load_textures();
    kg_initialize_geometry(&fb->resolution);
	kd_acquire_display(fb);

    return;
}

static void k_release_system(void)
{
    kd_release_display();
    kr_release_renderer();
    kg_release_geometry();

    return;
}

static void draw_progress_bar(const u16 secsElapsed, frame_buffer_s *const frameBuffer)
{
	u16 x;
	const u16 y = 0;
	u16 width = ((frameBuffer->resolution.w / TEST_DUR_SEC) * secsElapsed);

	if (width >= frameBuffer->resolution.w)
	{
		width = (frameBuffer->resolution.w - 1);
	}

	for (x = 0; x < width; x++)
	{
		frameBuffer->canvas[x + y * frameBuffer->resolution.w] = 255;
	}

	return;
}

int main(void)
{
	const time_t startTime = time(NULL);
    u16 frameCount = 0;
	u16 secsElapsed = 0;
    triangle_mesh_s scene, transfScene;

	/* Load the scene to be rendered.*/
    kmesh_load_triangle_mesh_from_file("mesh", &scene);
    transfScene.n = scene.n;
    transfScene.tris = (triangle_s*)malloc(sizeof(triangle_s) * transfScene.n);
	k_assert((transfScene.tris != NULL), "Failed to allocate memory for the scene's triangles.");

	k_initialize_system();

	/* Run the renderer until the test time is up.*/
    while (secsElapsed < TEST_DUR_SEC)
    {
        frame_buffer_s *frameBuffer;

        kg_transform_scene(&transfScene, &scene);
        frameBuffer = kr_render_scene(&transfScene);

		draw_progress_bar(secsElapsed, frameBuffer);

        kd_update_display(frameBuffer);

        k_assert((frameCount < (u16)(~0u)), "The frame counter is going to overflow.");
        frameCount++;

		secsElapsed = (time(NULL) - startTime);
    }

    /* Cleanup.*/
    k_release_system();
    free(transfScene.tris);
    free(scene.tris);

	printf("Result: %u frames in %u seconds (%u FPS).", frameCount, TEST_DUR_SEC, (frameCount / TEST_DUR_SEC));
    return 0;
}
