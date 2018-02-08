// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stddef.h>

#include "nde/api/runtime.h"
#include "nde/process.h"

// -------------------------
// Private methods interface
// -------------------------
void _nde_process_init(nde_process_p process);

// -----------------------------
// Public methods implementation
// -----------------------------

/**
 * @constructor
 */
nde_process_p
nde_process_create(void)
{
    nde_ptr_size p_size = sizeof(nde_process);
    nde_process_p p = (nde_process_p)nde_runtime_get_memory(p_size);

    _nde_process_init(p);

    return p;
}

// -----------------------------
// Private methods implementation
// -----------------------------

/**
 * Initialize process instance
 * 
 * @param {process} nde_process_p reference
 */
void
_nde_process_init(nde_process_p process)
{
    process->input_handle = 0;
}
