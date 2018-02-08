// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdlib.h>

#include "nde/api/runtime.h"

nde_ptr
nde_runtime_get_memory(nde_ptr_size size)
{
    void *ptr = malloc(size);

    if(ptr == NULL)
    {
        /* THROW ERROR! */
    }

    return (nde_ptr)ptr;
}

void nde_runtime_clear_memory(nde_ptr ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    free((void*)ptr);
}
