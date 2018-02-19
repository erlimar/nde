// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <string.h>

#include "nde.h"
#include "nde/api/runtime.h"
#include "nde/log.h"
#include "nde/data-list.h"
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
    NdeDataList command_args;
    NdeDataList command_env;
} _nde_process;

typedef _nde_process *_nde_process_p;

typedef struct _nde_process_str_kv_pair_s
{
    char *key;
    char *value;
} _nde_process_str_kv_pair;

typedef _nde_process_str_kv_pair *_nde_process_str_kv_pair_p;

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_process_init(_nde_process_p process);
void _nde_process_clear_env_items(_nde_process_p process);
void _nde_process_clear_args_items(_nde_process_p process);

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
void nde_process_destroy(NdeProcess process)
{
    _nde_process_p self = ((_nde_process_p)process);

    _nde_process_clear_args_items(self);
    _nde_process_clear_env_items(self);

    nde_runtime_free_memory(self->command_args);
    nde_runtime_free_memory(self->command_env);
    nde_runtime_free_memory(self);

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

void nde_process_set_env_from_envp(NdeProcess process, char *envp[])
{
    if (process == NdeNullPtr || envp == NdeNullPtr)
        return;

    _nde_process_p self = ((_nde_process_p)process);

    _nde_process_clear_env_items(process);

    for (int i = 0; envp != NdeNullPtr && envp[i] != NdeNullPtr; i++)
    {
        char *env_line = envp[i];
        char *sep_p = strpbrk(env_line, "=");
        char *key_str = NdeNullPtr;
        char *value_str = NdeNullPtr;

        if (sep_p)
        {
            int key_size = sep_p - env_line;

            key_str = nde_runtime_alloc_str_memory(key_size);
            strncpy(key_str, env_line, key_size);

            value_str = _nde_process_copy_string(sep_p + 1);
        }

        _nde_process_str_kv_pair_p pair = nde_runtime_alloc_memory(sizeof(_nde_process_str_kv_pair));

        pair->key = key_str;
        pair->value = value_str;

        nde_data_list_add(self->command_env, pair);
    }
}

int nde_process_get_env_size(NdeProcess process)
{
    if (process == NdeNullPtr)
        return -1;

    _nde_process_p self = ((_nde_process_p)process);

    return nde_data_list_get_size(self->command_env);
}

char *nde_process_get_env_key(NdeProcess process, int pos)
{
    if (process == NdeNullPtr)
        return NdeNullPtr;

    _nde_process_p self = ((_nde_process_p)process);

    _nde_process_str_kv_pair_p pair = nde_data_list_get_item(self->command_env, pos);

    if (pair == NdeNullPtr)
        return NdeNullPtr;

    return pair->key;
}

char *nde_process_get_env(NdeProcess process, char *var_name)
{
    if (process == NdeNullPtr)
        return NdeNullPtr;

    _nde_process_p self = ((_nde_process_p)process);

    int env_size = nde_data_list_get_size(self->command_env);
    char *env_value = NdeNullPtr;

    for (int i = 0; i < env_size; i++)
    {
        _nde_process_str_kv_pair_p pair = nde_data_list_get_item(self->command_env, i);

        if (pair == NdeNullPtr)
            break;

        if (strcmp(pair->key, var_name) == 0)
        {
            env_value = pair->value;
            break;
        }
    }

    return env_value;
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
    process->command_args = nde_data_list_create();
    process->command_env = nde_data_list_create();
}

void _nde_process_clear_env_items(_nde_process_p process)
{
    if (process == NdeNullPtr || process->command_env == NdeNullPtr)
        return;

    int items_size = nde_data_list_get_size(process->command_env);

    for (int i = 0; i < items_size; i++)
    {
        _nde_process_str_kv_pair_p item_ptr = (_nde_process_str_kv_pair_p)nde_data_list_get_item(process->command_env, i);

        if (item_ptr != NdeNullPtr)
        {
            nde_runtime_free_memory(item_ptr->key);
            nde_runtime_free_memory(item_ptr->value);
        }

        nde_runtime_free_memory(item_ptr);
    }
}

void _nde_process_clear_args_items(_nde_process_p process)
{
    if (process == NdeNullPtr || process->command_args == NdeNullPtr)
        return;

    int args_size = nde_data_list_get_size(process->command_args);

    for (int i = 0; i < args_size; i++)
    {
        NdePtr item_ptr = nde_data_list_get_item(process->command_args, i);
        nde_runtime_free_memory(item_ptr);
    }
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

    char *result = nde_runtime_alloc_str_memory(string_size);

    strncpy(result, value, string_size);

    return result;
}
