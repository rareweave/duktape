#include "duk_internal.h"
#include "duk_gas.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void *duk_gas_respecting_alloc_function(void *udata, duk_size_t size)
{
    HeapConfig *heapData = (HeapConfig *)udata;
    GasData *gasData = heapData->gasConfig;
    size_t cost = size * gasData->mem_cost_per_byte;
    gasData->gas_used += cost;

    if (gasData->gas_used > gasData->gas_limit)
    {
        duk_context *ctx = (duk_context *)heapData->ctx;
        
        ctx->heap->fatal_func(ctx->heap->heap_udata, "Out of gas");

        return NULL;
    }

    return malloc(size);
}

void *duk_gas_respecting_realloc_function(void *udata, void *ptr, duk_size_t size)
{
    HeapConfig *heapData = (HeapConfig *)udata;
    GasData *gasData = heapData->gasConfig;
    size_t cost = size * gasData->mem_cost_per_byte;
    gasData->gas_used += cost;

    if (gasData->gas_used > gasData->gas_limit)
    {
       
        return NULL;
    }

    return realloc(ptr, size);
}

void duk_gas_respecting_free_function(void *udata, void *ptr)
{
    free(ptr);
}

GasData * duk_get_gas_info(duk_context *ctx){
    HeapConfig *heapData = (HeapConfig *)ctx->heap->heap_udata;
    return heapData->gasConfig;
}


duk_bool_t duk_check_gas(void *udata)
{
    HeapConfig *heapData = (HeapConfig *)udata;
    GasData *gasData = heapData->gasConfig;
    gasData->gas_used++;
    if (gasData->gas_used > gasData->gas_limit)
    {
        return 1;
    }

    return 0;
}
