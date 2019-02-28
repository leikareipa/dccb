/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 * 
 * Triangle filler.
 *
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "renderer.h"
#include "gs.h"
#include "rs.h"

/* The surface we'll render to.*/
static frame_buffer_s *FRAME_BUFFER;

/* Properties of the triangle we're current rasterizing (i.e. this isn't thread-safe).*/
static u8 *TEXTURE_PTR;
static palette_idx BASE_COLOR;

void rs_init_tri_filler(frame_buffer_s *const frameBuffer)
{
    FRAME_BUFFER = frameBuffer;

    return;
}

/* Split the triangle into two straight-based triangles, one pointing up and one pointing down.
 * (Split algo from Bastian Molkenthin's www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html.)*/
static void rs_split_tri(vertex4_s *split,
                         const vertex4_s *high, const vertex4_s *mid, const vertex4_s *low)
{
    real splitRatio = (mid->y - high->y) / (real)(low->y - high->y);

    split->x = high->x + ((low->x - high->x) * splitRatio);
    split->y = mid->y;
    split->uv[0] = LERP(high->uv[0], low->uv[0], splitRatio);
    split->uv[1] = LERP(high->uv[1], low->uv[1], splitRatio);

    return;
}

/* ('High' here means in the sense of low y such that y = 0 is the top of the screen.)*/
static void rs_sort_tri_verts_by_height(const vertex4_s **high, const vertex4_s **mid, const vertex4_s **low)
{
    #define SWAP_VERTICES(v1, v2) const vertex4_s *const t = v1; \
                                  v1 = v2; \
                                  v2 = t;

    if ((*low)->y < (*mid)->y)
    {
        SWAP_VERTICES((*low), (*mid));
    }
    if ((*mid)->y < (*high)->y)
    {
        SWAP_VERTICES((*mid), (*high));
    }
    if ((*low)->y < (*mid)->y)
    {
        SWAP_VERTICES((*low), (*mid));
    }

    #undef SWAP_VERTICES

    return;
}

static void rs_fill_tri_row(const u16 row,
                            i32 startX, i32 endX,
                            i16 leftU, i16 leftV,
                            const i16 rightU, const i16 rightV)
{
    i16 x;
    i32 width;
    i16 uDelta, vDelta;
    i32 screenIdx;

    if ((endX - startX) <= 0)
    {
        return;
    }

    width = endX - startX;
    uDelta = ((rightU - leftU)) / (width + 1);
    vDelta = ((rightV - leftV)) / (width + 1);

    /* Draw the pixels.*/
    screenIdx = (startX + (row * FRAME_BUFFER->resolution.w));
    for (x = startX; x <= endX; x++)
    {
        u8 color = 2 + r_texture_color_at(UN_FIXEDP_UV(leftU), UN_FIXEDP_UV(leftV), 0);
        FRAME_BUFFER->canvas[screenIdx++] = color;

        leftU += uDelta;
        leftV += vDelta;
    }

    return;
}

/* Rasterizes into the frame buffer the triangle formed by the given three vertices.
 * Note that this expects the vertices to be in screen-space, and for the triangle's
 * base to be flat. You'd call this function after you've horizontally split the
 * triangle, passing each piece into the function separately.*/
static void rs_fill_tri_part(vertex4_s *peak, vertex4_s *base1, vertex4_s *base2)
{
    i16 startRow, endRow, y;
    i16 height, flipped = 0;

    /* We'll interpolate by deltas each pixel.*/
    i32 pleft, pright, dLeft, dRight, leftU, leftV, rightU, rightV, dLeftU, dLeftV, dRightU, dRightV;

    /* Figure out which of the base's vertices is on the left and which on the right.*/
    vertex4_s *left = base2, *right = base1;
    if (base1->x < base2->x)
    {
        left = base1;
        right = base2;
    }

    startRow = peak->y;
    endRow = base1->y;

    /* Flip depending on whether the peak vertex is above or below the base.*/
    if (startRow > endRow)
    {
        i16 temp = startRow;
        startRow = endRow;
        endRow = temp;

        /* Don't draw the base row twice; i.e. skip it for the down-triangle.*/
        startRow++;

        flipped = 1;
    }

    if ((startRow == endRow) ||
        ((endRow - startRow) <= 0))
    {
        return;
    }

    height = (endRow - startRow);

    pleft = FIXEDP((i32)peak->x);
    pright = FIXEDP((i32)peak->x);
    dLeft = FIXEDP((i32)left->x - peak->x) / (height + 1);
    dRight = FIXEDP((i32)right->x - peak->x) / (height + 1);

    leftU = (peak->uv[0]);
    leftV = (peak->uv[1]);
    rightU = (peak->uv[0]);
    rightV = (peak->uv[1]);
    dLeftU = (left->uv[0] - peak->uv[0]) / (height + 1);
    dLeftV = (left->uv[1] - peak->uv[1]) / (height + 1);
    dRightU = (right->uv[0] - peak->uv[0]) / (height + 1);
    dRightV = (right->uv[1] - peak->uv[1]) / (height + 1);

    if (flipped)
    {
        pleft = FIXEDP((i32)left->x);
        pright = FIXEDP((i32)right->x);
        dLeft = FIXEDP((i32)peak->x - left->x) / (height + 1);
        dRight = FIXEDP((i32)peak->x - right->x) / (height + 1);

        leftU = (left->uv[0]);
        leftV = (left->uv[1]);
        rightU = (right->uv[0]);
        rightV = (right->uv[1]);
        dLeftU = (peak->uv[0] - left->uv[0]) / (height + 1);
        dLeftV = (peak->uv[1] - left->uv[1]) / (height + 1);
        dRightU = (peak->uv[0] - right->uv[0]) / (height + 1);
        dRightV = (peak->uv[1] - right->uv[1]) / (height + 1);
    }

    /* Iterate over each y row in the triangle, on each row filling in a horizontal line between
     * the left and right edge of the triangle.*/
    for (y = startRow; y <= endRow; y++)
    {
        pleft += dLeft;
        pright += dRight;

        leftU += dLeftU;
        leftV += dLeftV;
        rightU += dRightU;
        rightV += dRightV;

        rs_fill_tri_row(y, UN_FIXEDP(pleft), UN_FIXEDP(pright), leftU, leftV, rightU, rightV);
    }

    return;
}

void rs_fill_tri(triangle_s *const t)
{
    vertex4_s split;
    vertex4_s *high = &t->v[0],
              *mid = &t->v[1],
              *low = &t->v[2];

    BASE_COLOR = t->baseColor;
    TEXTURE_PTR = t->texturePtr;

    /* Rasterize the triangle into the frame buffer in two parts.*/
    rs_sort_tri_verts_by_height(&high, &mid, &low);
    rs_split_tri(&split, high, mid, low);
    rs_fill_tri_part(high, mid, &split); /* Up triangle.*/
    rs_fill_tri_part(low, mid, &split);  /* Down triangle.*/

    return;
}


