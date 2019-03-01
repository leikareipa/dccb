/*
 * Tarpeeksi Hyvae Soft 2018 /
 * DOS C Compiler Benchmark
 *
 */

#include <assert.h>
#include <stdio.h>
#include "display.h"
#include "common.h"
#include "types.h"
#include "file.h"

static FILE *FILE_HANDLE_CACHE[5] = {NULL};

static uint f_is_an_active_handle(const u16 h)
{
    return ((h < NUM_ELEMENTS(FILE_HANDLE_CACHE)) &&
            FILE_HANDLE_CACHE[h] != NULL);
}

static u16 f_next_free_handle()
{
    u16 h;

    /* Loop until we find an unassigned handle.*/
    h = 0;
    while (1)
    {
        if (FILE_HANDLE_CACHE[h] == NULL)
        {
            break;
        }

        h++;
        k_assert((h < NUM_ELEMENTS(FILE_HANDLE_CACHE)), "Overflow while looking for a free file handle.");
    }

    return h;
}

void kf_read_binary(u8 *dst, const u32 numBytes, const u16 handleId)
{
    size_t r;

    k_assert(f_is_an_active_handle(handleId), "Was asked to read with an inactive file handle.");

    r = fread(dst, 1, numBytes, FILE_HANDLE_CACHE[handleId]);

    k_assert((r == numBytes), "Failed to read data from the given file.");

    return;
}

u16 kf_open_binary_file(const char *const filename, const char *const mode)
{
    u16 h = f_next_free_handle();

    MESSAGE(("Opening file '%s' with handle %u.", filename, h));

    FILE_HANDLE_CACHE[h] = fopen(filename, mode);

    k_assert((FILE_HANDLE_CACHE[h] != NULL), "Failed to open the given file.");

    return h;
}

void kf_close_file(const u16 handleId)
{
    int cl;

    k_assert(f_is_an_active_handle(handleId), "Was asked to close an inactive file handle.");

    cl = fclose(FILE_HANDLE_CACHE[handleId]);
    k_assert((cl == 0), "Failed to close a file.");

    FILE_HANDLE_CACHE[handleId] = NULL;

    return;
}
