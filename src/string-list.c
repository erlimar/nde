// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <string.h>

#include "nde.h"
#include "nde/api/runtime.h"
#include "nde/string-list.h"

// --------------------------
// Declaração privada do tipo
// --------------------------
typedef struct _nde_string_list_item_s
{
    char *value;
    _nde_string_list_item_p next;
} _nde_string_list_item;

typedef _nde_string_list_item *_nde_string_list_item_p;

typedef struct _nde_string_list_s
{
    int length;
    _nde_string_list_item_p first_item;
} _nde_string_list;

typedef _nde_string_list *_nde_string_list_p;

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_string_list_init(_nde_string_list_p list);
_nde_string_list_item_p _nde_string_list_item_create(char *);

// ---------------------------------
// Implementação de métodos públicos
// ---------------------------------
/**
 * @constructor
 */
NdeStringList nde_string_list_create(void)
{
    NdePtrSize p_size = sizeof(_nde_string_list);
    NdeStringList list = (NdeStringList)nde_runtime_alloc_memory(p_size);

    _nde_string_list_init(list);

    return list;
}

/**
 * @destructor
 */
void nde_string_list_destroy(NdeStringList list)
{
    nde_runtime_free_memory((void *)list);
    // TODO: atribuir NULL ao ponteiro. usar NdeStringList &p
}

int nde_string_list_length(NdeStringList list)
{
    if (list == NdeNullPtr)
        return NDE_STRING_LIST_ERROR_RVALUE;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    return self->length;
}

char *nde_string_list_get_by_position(NdeStringList list, int pos)
{
    if (list == NdeNullPtr || pos < 0)
        return (char *)NdeNullPtr;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    if (self->length < 1 || self->first_item == NdeNullPtr)
        return (char *)NdeNullPtr;

    int end = self->length - 1;

    if (pos > end)
        return (char *)NdeNullPtr;

    int item_pos = 0;
    _nde_string_list_item_p item = self->first_item;

    while (item_pos <= end && item != NdeNullPtr)
    {
        item = item->next;
        item_pos++;

        if (item_pos == pos)
            break;

    }

    if (item == NdeNullPtr)
        return (char *)NdeNullPtr;

    return item->value;
}

unsigned int nde_string_list_add(NdeStringList list, char *string)
{
    if (list == NdeNullPtr || string == NdeNullPtr)
        return NDE_STRING_LIST_ERROR_RVALUE;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    if (self->length > 0 && self->first_item == NdeNullPtr)
        return NDE_STRING_LIST_ERROR_RVALUE;

    long int pos = 0;
    _nde_string_list_item_p last_item = self->first_item;

    while (pos < self->length)
    {
        last_item = last_item->next;
        pos++;
    }

    _nde_string_list_item_p next_item = _nde_string_list_item_create(string);

    if (last_item == self->first_item)
        self->first_item = next_item;
    else
        last_item->next = next_item;

    return ++self->length;
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------
void _nde_string_list_init(_nde_string_list_p list)
{
    list->length = 0;
    list->first_item = (_nde_string_list_item_p)NdeNullPtr;
}

_nde_string_list_item_p _nde_string_list_item_create(char *value)
{
    NdePtrSize string_size = strlen(value);
    _nde_string_list_item_p item = (_nde_string_list_item_p)nde_runtime_alloc_memory(string_size);

    item->next = NdeNullPtr;
    item->value = value;

    return item;
}
