/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include "types.h"

typedef struct
{
    u16 w, h;
    u8 bpp;
}
resolution_s;

typedef struct
{
    u8 r, g, b;
}
color_rgb_s;

typedef struct
{
    palette_idx *canvas;
    color_rgb_s *palette;
    resolution_s resolution;
}
frame_buffer_s;

#define k_assert(condition, error_str) if (!(condition))\
								       {\
											kd_release_display();\
											assert(condition && error_str);\
									   }

/* For converting to and from fixed-point values.*/
#define FIXEDP(value)       ((value) << 16)	/* These expect a 32-bit unsigned value.*/
#define UN_FIXEDP(value)    ((value) >> 16)
#define FIXEDP_UV(value)    ((value) << 9)	/* These expect a 16-bit unsigned value and are meant for u,v texture coordinates.*/
#define UN_FIXEDP_UV(value) ((value) >> 9)

#define NUM_ELEMENTS(array) (int)((sizeof((array)) / sizeof((array)[0])))

#define LERP(x, y, step)    ((x) + ((step) * ((y) - (x))))

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define DEG_TO_RAD(x)       (((x) * (M_PI)) / 180.0)

/* For a sine/cosine lookup.*/
extern const float sin_lut[];
#define SIN(x)              (sin_lut[(x)])
#define COS(x)              (sin_lut[(x) + 256])

#define MESSAGE(args)       (printf("[info ] {%s:%i} ", __FILE__, __LINE__), printf args, printf("\n"), fflush(stdout))
#define ERROR(args)         (printf("[ERROR] {%s:%i} ", __FILE__, __LINE__), printf args, printf("\n"), fflush(stdout))

#endif
