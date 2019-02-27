/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#ifndef FILE_H
#define FILE_H

#include "types.h"

void kf_read_binary(u8 *dst, const u32 numBytes, const u16 handleId);

u16 kf_open_binary_file(const char *const filename, const char *const mode);

void kf_close_file(const u16 handleId);

#endif
