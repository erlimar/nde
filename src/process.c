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
nde_process_p
nde_process_create(void)
{
    nde_ptr_size p_size = sizeof(nde_process);
    nde_process_p p = (nde_process_p)nde_runtime_get_memory(p_size);

    _nde_process_init(p);

    return p;
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------

/**
 * Inicializa uma instância de <process>
 * 
 * @param {process} Referência a um <nde_process_p>
 */
void
_nde_process_init(nde_process_p process)
{
    process->input_handle = 0;
}
