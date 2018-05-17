// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdlib.h>

#include "nde/api/runtime.h"
#include "nde/log.h"

NdePtr
nde_runtime_alloc_memory(NdePtrSize size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
    {
        // TODO: Lançar erro!
        WARN("nde_runtime_alloc_memory/malloc return NULL");

        return NdeNullPtr;
    }

    return (NdePtr)ptr;
}

NdePtr
nde_runtime_alloc_str_memory(NdePtrSize size)
{
    void *ptr = calloc(size + 1, sizeof(char));

    if (ptr == NULL)
    {
        // TODO: Lançar erro!
        WARN("nde_runtime_alloc_str_memory/calloc return NULL");

        return NdeNullPtr;
    }

    return (NdePtr)ptr;
}

void nde_runtime_free_memory(NdePtr ptr)
{
    if (ptr == NdeNullPtr)
        return;

    free((void *)ptr);
}
