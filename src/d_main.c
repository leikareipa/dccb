/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 * 
 * Display.
 *
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include "renderer.h"
#include "display.h"
#include "common.h"
#include "types.h"

#ifdef __WATCOMC__
    #include <conio.h> /* For outp().*/
#endif

typedef enum
{
    VGAMODE_GRAPHICS,
    VGAMODE_TEXT
}
video_mode_e;

/* Pointer to video memory in VGA mode 13h.*/
static u8 *const VGA_MEMORY = (u8*)0xA0000000L;

static void d_set_video_mode(const video_mode_e mode)
{
    /* May get called by k_assert, so use regular assert inside here.*/

    union REGS regs;

    if (mode == VGAMODE_GRAPHICS)
    {
        regs.h.ah = 0x00;
        regs.h.al = 0x13;
    }
    else if (mode == VGAMODE_TEXT)
    {
        regs.h.ah = 0x00;
        regs.h.al = 0x03;
    }
    else
    {
        assert(0 && "Was requested to set an unrecognized video mode.");
    }

    int86(0x10, &regs, &regs);

    return;
}

static void d_set_palette(const color_rgb_s *p)
{
    u16 i;

    k_assert((p != NULL), "Tried to operate on a null palette.");

    /* Assign the 256-color palette of VGA mode 13h.*/
    for (i = 0; i < 256; (i++, p++))
    {
        outp(0x03c8, i);
        outp(0x03c9, p->r);
        outp(0x03c9, p->g);
        outp(0x03c9, p->b);
    }

    return;
}

void kd_acquire_display(const frame_buffer_s *const fb)
{
    d_set_video_mode(VGAMODE_GRAPHICS);
    d_set_palette(fb->palette);

    return;
}

void kd_release_display(void)
{
    /* May get called by k_assert, so use regular assert inside here.*/

    d_set_video_mode(VGAMODE_TEXT);

    return;
}

void kd_update_display(const frame_buffer_s *const fb)
{
    memcpy(VGA_MEMORY, fb->canvas, (fb->resolution.w * fb->resolution.h));

    return;
}
