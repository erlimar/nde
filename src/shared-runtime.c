// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdlib.h>

#include "nde/api/runtime.h"

NdePtr
nde_runtime_alloc_memory(NdePtrSize size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
    {
        // TODO: Lançar erro!
    }

    return (NdePtr)ptr;
}

void nde_runtime_free_memory(NdePtr ptr)
{
    if (ptr == NULL)
        return;

    free((void *)ptr);
}
