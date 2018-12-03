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

/* For int86().*/
#if defined(__WATCOMC__)
    #include <i86.h>
#elif defined(__PACIFIC__) || defined(__TURBOC__)
    #include <dos.h>
#else
    #include <bios.h>
#endif

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

/* Returns 1 if the user is pressing a key on the keyboard which indicates that they want to quit.
 * Otherwise, returns 0.*/
static u16 user_wants_to_quit(void)
{
    u16 wants = 0;
    union REGS regs;

    /* Get keyboard status.*/
    regs.h.ah = 1;
    int86(0x16, &regs, &regs);

    /* If Q pressed = user wants to quit.*/
    if (regs.h.ah == 0x10) wants = 1;

    /* Clear the keyboard buffer.*/
    regs.h.ah = 0x0c;
    regs.h.al = 0;
    int86(0x21, &regs, &regs);

    return wants;
}

int main(void)
{
    const time_t startTime = time(NULL);
    u16 testFinished = 0; /* Will be set to 1 once the benchmark is fully completed.*/
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

        if (user_wants_to_quit()) goto end_test;

        secsElapsed = (time(NULL) - startTime);
    }
    testFinished = 1;

    end_test:

    /* Cleanup.*/
    k_release_system();
    free(transfScene.tris);
    free(scene.tris);

    if (testFinished) printf("Result: %u frames in %u seconds (%u FPS).", frameCount, TEST_DUR_SEC, (frameCount / TEST_DUR_SEC));
    else printf("The run was aborted.");

    return 0;
}
