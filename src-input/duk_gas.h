// gas.h
#ifdef __cplusplus
extern "C"
{
#endif

#include "duk_internal.h"

    typedef struct
    {
        size_t gas_limit;
        size_t gas_used;
        size_t mem_cost_per_byte;
    } GasData;

    void *duk_gas_respecting_alloc_function(void *udata, duk_size_t size);
    void *duk_gas_respecting_realloc_function(void *udata, void *ptr, duk_size_t size);
    void duk_gas_respecting_free_function(void *udata, void *ptr);
    void duk_set_execution_gas(duk_context *ctx, GasData *gasData);
    duk_bool_t duk_check_gas(void *udata);

#ifdef __cplusplus
}
#endif
