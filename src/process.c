// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <string.h>

#include "nde.h"
#include "nde/api/runtime.h"
#include "nde/string-list.h"
#include "nde/process.h"

// --------------------------
// Declaração privada do tipo
// --------------------------
typedef struct _nde_process_s
{
    NdePtr input_handle;
    NdePtr output_handle;
    NdePtr error_handle;
    NdePtr command;
    NdePtr current_directory;
    NdeStringList command_args;
    NdeStringList command_env;
} _nde_process;

typedef _nde_process *_nde_process_p;

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_process_init(_nde_process_p process);
char *_nde_process_get_string_field(NdePtr *field);
char *_nde_process_copy_string(char *value);

// ---------------------------------
// Implementação de métodos públicos
// ---------------------------------

/**
 * @constructor
 */
NdeProcess nde_process_create(void)
{
    NdePtrSize p_size = sizeof(_nde_process);
    NdeProcess p = (NdeProcess)nde_runtime_alloc_memory(p_size);

    _nde_process_init(p);

    return p;
}

/**
 * @destructor
 */
void nde_process_destroy(NdeProcess p)
{
    nde_runtime_free_memory((void *)p);
    // TODO: atribuir NULL ao ponteiro. usar NdeProcess &p
}

NdePtr nde_process_get_input_handle(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    return self->input_handle;
}

void nde_process_set_input_handle(NdeProcess process, NdePtr handle)
{
    _nde_process_p self = ((_nde_process_p)process);

    self->input_handle = handle;
}

NdePtr nde_process_get_output_handle(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    return self->output_handle;
}

void nde_process_set_output_handle(NdeProcess process, NdePtr handle)
{
    _nde_process_p self = ((_nde_process_p)process);

    self->output_handle = handle;
}

NdePtr nde_process_get_error_handle(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    return self->error_handle;
}

void nde_process_set_error_handle(NdeProcess process, NdePtr handle)
{
    _nde_process_p self = ((_nde_process_p)process);

    self->error_handle = handle;
}

char *nde_process_get_command(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    return _nde_process_get_string_field(&self->command);
}

void nde_process_set_command(NdeProcess process, char *command)
{
    _nde_process_p self = ((_nde_process_p)process);

    if (self->command != NdeNullPtr)
    {
        // Limpando valor anterior
        nde_runtime_free_memory(self->command);
        self->command = NdeNullPtr;
    }

    self->command = _nde_process_copy_string(command);
}

char *nde_process_get_current_directory(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    return _nde_process_get_string_field(&self->current_directory);
}

void nde_process_set_current_directory(NdeProcess process, char *cd)
{
    _nde_process_p self = ((_nde_process_p)process);

    if (self->current_directory != NdeNullPtr)
    {
        // Limpando valor anterior
        nde_runtime_free_memory(self->current_directory);
        self->current_directory = NdeNullPtr;
    }

    self->current_directory = _nde_process_copy_string(cd);
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------

/**
 * Inicializa uma instância de <nde_process>
 * 
 * @param {process} Referência a um <nde_process_p>
 */
void _nde_process_init(_nde_process_p process)
{
    process->input_handle = NdeNullPtr;
    process->output_handle = NdeNullPtr;
    process->error_handle = NdeNullPtr;
    process->command = NdeNullPtr;
    process->current_directory = NdeNullPtr;
    process->command_args = nde_string_list_create();
    process->command_env = nde_string_list_create();
}

char *_nde_process_get_string_field(NdePtr *field)
{
    if (field == NdeNullPtr)
    {
        return (char *)NdeNullPtr;
    }

    return (char *)*field;
}

char *_nde_process_copy_string(char *value)
{
    if (value == NdeNullPtr)
    {
        return (char *)NdeNullPtr;
    }

    NdePtrSize string_size = strlen(value);

    char *result = nde_runtime_alloc_memory(string_size + 1);

    strcpy(result, value);

    return result;
}
