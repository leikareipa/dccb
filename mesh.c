/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "display.h"
#include "common.h"
#include "types.h"
#include "file.h"

void kmesh_load_triangle_mesh_from_file(const char *const filename, triangle_mesh_s *const mesh)
{
    const u16 fileHandle = kf_open_binary_file(filename, "rb");
    u8 numMats, maxTexNameLen;
    u16 numObjs, numTris, numTrisTotal;
    u16 i, p, triIdx = 0;
    char texName[64];

    /* For materials.*/
    u8 *texturePtrs[128];
    palette_idx baseColors[128];

    /* Read in the header.*/
    char idStr[4];
	idStr[3] = '\0';
    kf_read_binary((u8*)idStr, 3, fileHandle);
	k_assert((strcmp(idStr, "KAB") == 0), "Unsupported mesh file format.");
    kf_read_binary((u8*)&maxTexNameLen, sizeof(maxTexNameLen), fileHandle);
    k_assert((NUM_ELEMENTS(texName) >= maxTexNameLen), "Texture names won't fit into buffer.");
    kf_read_binary((u8*)&numMats, sizeof(numMats), fileHandle);
    k_assert((numMats <= 128), "Too many materials in the mesh file.");

    /* Read in the materials.*/
    for (i = 0; i < numMats; i++)
    {
        kf_read_binary((u8*)texName, maxTexNameLen, fileHandle);
        if (texName[0] == '\0')
        {
            /* No texture name defined, so no texture.*/
            texturePtrs[i] = NULL;
        }
        else
        {
           /* texturePtrs[i] = kr_load_texture(texName);*/
        }

        kf_read_binary((u8*)&baseColors[i], sizeof(u8), fileHandle);
    }

    /* Read in the triangles.*/
    kf_read_binary((u8*)&numTrisTotal, sizeof(u16), fileHandle);
    mesh->n = numTrisTotal;
    mesh->tris = (triangle_s*)malloc(sizeof(triangle_s) * numTrisTotal);
    kf_read_binary((u8*)&numObjs, sizeof(u16), fileHandle);
    for (i = 0; i < numObjs; i++)
    {
        kf_read_binary((u8*)&numTris, sizeof(u16), fileHandle);
        for (p = 0; p < numTris; p++)
        {
            u16 i;
            u8 matId;
            triangle_s *t = NULL;

            k_assert((triIdx < numTrisTotal), "");

            t = &mesh->tris[triIdx];

            /* Material.*/
            kf_read_binary((u8*)&matId, sizeof(u8), fileHandle);
            t->baseColor = baseColors[matId];
            t->texturePtr = texturePtrs[matId];

            /* Vertices.*/
            for (i = 0; i < 3; i++)
            {
                kf_read_binary((u8*)&t->v[i].x, sizeof(i32), fileHandle);
                kf_read_binary((u8*)&t->v[i].y, sizeof(i32), fileHandle);
                kf_read_binary((u8*)&t->v[i].z, sizeof(i32), fileHandle);
                t->v[i].w = 1;
            }

            /* Vertex texture coordinates.*/
            for (i = 0; i < 3; i++)
            {
                u8 v;

                kf_read_binary((u8*)&v, sizeof(u8), fileHandle);
                t->v[i].uv[0] = FIXEDP_UV(v);
                kf_read_binary((u8*)&v, sizeof(u8), fileHandle);
                t->v[i].uv[1] = FIXEDP_UV(v);
            }

            triIdx++;
        }
    }

    k_assert((triIdx == numTrisTotal), "Loaded in a different number of triangles than what we had allocated memory for.");

	mesh->n = numTrisTotal;

    kf_close_file(fileHandle);

    MESSAGE(("Loaded %d triangles from mesh file '%s'.", numTrisTotal, filename));

    return;
}
