/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "display.h"
#include "rs.h"
#include "gs.h"

/* The surface we'll render to, and its size.*/
static frame_buffer_s FRAME_BUFFER = {NULL, NULL, {0, 0, 0}};

/* Load the program's palette from disk, and add it into the renderer.*/
void r_assign_palette()
{
	int i;
    FILE *paletteFile;

    /* This function is only supposed to be called once, at program launch when
     * the palette is still uninitialized.*/
    k_assert((FRAME_BUFFER.palette == NULL), "Attempting to re-assign the palette.");

    paletteFile = fopen("palette", "rb");
    k_assert(paletteFile, "Failed to open the palette file.");

    FRAME_BUFFER.palette = (color_rgb_s*)malloc(sizeof(color_rgb_s) * 256);
    k_assert((FRAME_BUFFER.palette != NULL), "Failed to allocate memory for the palette.");

    /* Load the palette from disk.*/
    for (i = 0; i < 256; i++)
    {
		color_rgb_s c;

        if (fread(&c.r, 1, 1, paletteFile) != 1 ||
            fread(&c.g, 1, 1, paletteFile) != 1 ||
            fread(&c.b, 1, 1, paletteFile) != 1)
        {
            k_assert(0, "Failed to load the palette.");
            return;
        }

        FRAME_BUFFER.palette[i].r = c.r;
        FRAME_BUFFER.palette[i].g = c.g;
        FRAME_BUFFER.palette[i].b = c.b;
    }

    fclose(paletteFile);

    return;
}

void r_clear_canvas(void)
{
    const u32 frameSize = sizeof(palette_idx) * FRAME_BUFFER.resolution.w * FRAME_BUFFER.resolution.h * (FRAME_BUFFER.resolution.bpp / 8);

    memset(FRAME_BUFFER.canvas, 4, frameSize);

    return;
}

void r_resize_frame_buffer(const resolution_s *const r)
{
	if (FRAME_BUFFER.canvas != NULL)
	{
		free(FRAME_BUFFER.canvas);
	}

    FRAME_BUFFER.resolution = *r;
    FRAME_BUFFER.canvas = (palette_idx*)malloc(sizeof(palette_idx) * r->w * r->h * (r->bpp / 8));
    k_assert((FRAME_BUFFER.canvas != NULL), "Failed to allocate memory for the frame buffer canvas.");

    r_clear_canvas();

    return;
}

/* Initialize the renderer for an image of width x height x depth. This
 * function must be called before any rendering is attempted.*/
const frame_buffer_s* kr_acquire_renderer(void)
{
	resolution_s resolution;

	/* Set the resolution for VGA mode 13h*/
	resolution.w = 320;
	resolution.h = 200;
	resolution.bpp = 8;

    /* This function is only supposed to be called once, at program launch when
	 * the canvas is still uninitialized.*/
    k_assert((FRAME_BUFFER.canvas == NULL), "Tried to re-initialize the frame buffer canvas.");

    r_resize_frame_buffer(&resolution);

    r_assign_palette();

    rs_init_tri_filler(&FRAME_BUFFER);

    return &FRAME_BUFFER;
}

void kr_release_renderer()
{
    free(FRAME_BUFFER.canvas);
    free(FRAME_BUFFER.palette);

    kr_release_texture_cache();

    return;
}

frame_buffer_s* kr_render_scene(triangle_mesh_s *const scene)
{
	int i = 0;

    r_clear_canvas();

    for (i = 0; i < scene->n; i++)
    {
        rs_fill_tri(&scene->tris[i]);
    }

    return &FRAME_BUFFER;
}
