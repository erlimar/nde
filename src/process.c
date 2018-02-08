// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stddef.h>

#include "nde/api/runtime.h"
#include "nde/process.h"

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_process_init(nde_process_p process);

// ---------------------------------
// Implementação de métodos públicos
// ---------------------------------

/**
 * @constructor
 */
nde_process_p nde_process_create(void)
{
    nde_ptr_size p_size = sizeof(nde_process);
    nde_process_p p = (nde_process_p)nde_runtime_alloc_memory(p_size);

    _nde_process_init(p);

    return p;
}

/**
 * @destructor
 */
void nde_process_destroy(nde_process_p p)
{
    nde_runtime_free_memory((void *)p);
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------

/**
 * Inicializa uma instância de <nde_process>
 * 
 * @param {process} Referência a um <nde_process_p>
 */
void _nde_process_init(nde_process_p process)
{
    process->input_handle = nde_nullptr;
    process->output_handle = nde_nullptr;
    process->error_handle = nde_nullptr;
}
