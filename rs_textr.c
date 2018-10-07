/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "common.h"
#include "types.h"

/* The dimensions that all textures must satisfy.*/
#define TEXTURE_WIDTH 32
#define TEXTURE_HEIGHT 32

static const u16 TEXTURE_BYTESIZE = (TEXTURE_WIDTH * TEXTURE_HEIGHT);

/* How many textures we'll have room for in the texture cache.*/
#define MAX_NUM_TEXTURES 1

/* A byte array into which we store any textures loaded from disk.*/
static palette_idx *TEXTURE_CACHE = NULL;

/* A lookup table for the byte offset at which the nth texture starts in the
 * texture cache.*/
static u16 TEXTURE_IDX_LUT[MAX_NUM_TEXTURES];

void kr_init_texture_cache()
{
    u16 i;

    k_assert((TEXTURE_CACHE == NULL), "Tried to re-initialize the texture cache.");
    TEXTURE_CACHE = (palette_idx*)malloc(sizeof(palette_idx) * (TEXTURE_BYTESIZE * MAX_NUM_TEXTURES));
    k_assert((TEXTURE_CACHE != NULL), "Failed to allocate memory for the texture cache.");

    for (i = 0; i < MAX_NUM_TEXTURES; i++)
    {
        TEXTURE_IDX_LUT[i] = (i * TEXTURE_BYTESIZE);
    }

    return;
}

void kr_release_texture_cache(void)
{
    k_assert((TEXTURE_CACHE != NULL), "Tried to double-delete the texture cache.");
    free(TEXTURE_CACHE);

    return;
}

void kr_load_textures(void)
{
    FILE *const textureFile = fopen("texture", "rb");

    k_assert((textureFile != NULL), "Can't load textures into a null texture cache.");
    if (fread(TEXTURE_CACHE, 1, TEXTURE_BYTESIZE, textureFile) != TEXTURE_BYTESIZE)
    {
        k_assert(0, "Failed to read in the texture data.");
    }

    fclose(textureFile);

    return;
}

u8 r_texture_color_at(const u8 u, const u8 v, const i16 texId)
{
    /* Temp hack. Prevent out-of-upper-bounds u,v access by clearing bits above
     * the maximum size with 0-index. Assumes that the maximum is a power of two.*/
    const u8 uBounded = (u & (TEXTURE_WIDTH - 1));
    const u8 vBounded = (v & (TEXTURE_HEIGHT - 1));

    k_assert((texId < MAX_NUM_TEXTURES), "Trying to access the texture cache out of bounds.");

    return TEXTURE_CACHE[(uBounded + vBounded * TEXTURE_WIDTH) + TEXTURE_IDX_LUT[texId]];
}
