#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "time_utils.h"

#include "fdb_internal.h"

#define N_DBG_SWITCH (256)

static uint8_t _global_dbg_switch[N_DBG_SWITCH];
static void* _global_dbg_addr[N_DBG_SWITCH];
static uint64_t _global_dbg_uint64_t[N_DBG_SWITCH];

fdb_fatal_error_callback fatal_error_callback = NULL;

// LCOV_EXCL_START
void _dbg_sw_set(int n)
{
    _global_dbg_switch[n] = 1;
}

void _dbg_sw_clear(int n)
{
    _global_dbg_switch[n] = 0;
}

void _dbg_set_addr(int n, void *addr)
{
    _global_dbg_addr[n] = addr;
}

void * _dbg_get_addr(int n)
{
    return _global_dbg_addr[n];
}

void _dbg_set_uint64_t(int n, uint64_t val)
{
    _global_dbg_uint64_t[n] = val;
}

uint64_t _dbg_get_uint64_t(int n)
{
    return _global_dbg_uint64_t[n];
}

int _dbg_is_sw_set(int n)
{
    return _global_dbg_switch[n];
}

void _dbg_assert(int line, const char *file, uint64_t val, uint64_t expected) {
    char *hang_process;
     fprintf(stderr, "Assertion in %p != %p in %s:%d\n",
            (void *)val, (void *)expected, file, line);

     // Invoke the fatal error callback if registered.
     if (fatal_error_callback != NULL) {
         fatal_error_callback();
     }

     hang_process = getenv("HANG_ON_ASSERTION");
     if (hang_process) {
         fprintf(stderr, "Hanging process...");
         fprintf(stderr, "\n");
         while (1) {
             usleep(1000);
         }
     }
}
// LCOV_EXCL_STOP
