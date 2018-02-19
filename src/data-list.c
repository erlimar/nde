// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <string.h>

#include "nde.h"
#include "nde/api/runtime.h"
#include "nde/data-list.h"

// --------------------------
// Declaração privada do tipo
// --------------------------
typedef struct _nde_data_list_item_s
{
    NdePtr value;
    struct _nde_data_list_item_s *next;
} _nde_data_list_item;

typedef _nde_data_list_item *_nde_data_list_item_p;

typedef struct _nde_data_list_s
{
    _nde_data_list_item_p first_item;
} _nde_data_list;

typedef _nde_data_list *_nde_data_list_p;

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_data_list_init(_nde_data_list_p list);
void _nde_data_list_free_items(_nde_data_list_p list);
_nde_data_list_item_p _nde_data_list_item_create(NdePtr item_value);

// ---------------------------------
// Implementação de métodos públicos
// ---------------------------------
/**
 * @constructor
 */
NdeDataList nde_data_list_create(void)
{
    NdePtrSize p_size = sizeof(_nde_data_list);
    NdeDataList list = (NdeDataList)nde_runtime_alloc_memory(p_size);

    _nde_data_list_init(list);

    return list;
}

/**
 * @destructor
 */
void nde_data_list_destroy(NdeDataList list)
{
    _nde_data_list_free_items((_nde_data_list_p)list);
    nde_runtime_free_memory((void *)list);
    // TODO: atribuir NULL ao ponteiro. usar NdeDataList &p
}

int nde_data_list_get_size(NdeDataList list)
{
    if (list == NdeNullPtr)
        return NDE_DATA_LIST_ERROR_RVALUE;

    _nde_data_list_p self = ((_nde_data_list_p)list);

    int size = 0;
    _nde_data_list_item_p item = self->first_item;

    while (item != NdeNullPtr)
    {
        size++;
        item = item->next;
    }

    return size;
}

int nde_data_list_add(NdeDataList list, NdePtr item)
{
    if (list == NdeNullPtr || item == NdeNullPtr)
        return NDE_DATA_LIST_ERROR_RVALUE;

    _nde_data_list_p self = ((_nde_data_list_p)list);

    int size = 0;
    _nde_data_list_item_p previous = NdeNullPtr;
    _nde_data_list_item_p last = self->first_item;

    while (last != NdeNullPtr)
    {
        previous = last;
        last = last->next;
        size++;
    }

    _nde_data_list_item_p next_item = _nde_data_list_item_create(item);

    if (previous == NdeNullPtr)
        self->first_item = next_item;
    else
        previous->next = next_item;

    return size + 1;
}

NdePtr nde_data_list_get_item(NdeDataList list, int pos)
{
    if (list == NdeNullPtr || pos < 0)
        return NDE_DATA_LIST_ERROR_RVALUE;

    _nde_data_list_p self = ((_nde_data_list_p)list);

    int count = 0;
    _nde_data_list_item_p find = NdeNullPtr;
    _nde_data_list_item_p last = self->first_item;

    while (last != NdeNullPtr)
    {
        if (count == pos)
        {
            find = last;
            break;
        }

        last = last->next;
        count++;
    }

    if (find == NdeNullPtr)
        return NDE_DATA_LIST_ERROR_RVALUE;

    return find->value;
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------
void _nde_data_list_init(_nde_data_list_p list)
{
    list->first_item = (_nde_data_list_item_p)NdeNullPtr;
}

void _nde_data_list_free_items(_nde_data_list_p list)
{
    if (list == NdeNullPtr)
        return;

    _nde_data_list_item_p previous = NdeNullPtr;
    _nde_data_list_item_p current = list->first_item;

    while (current != NdeNullPtr)
    {
        if (previous != NdeNullPtr)
            nde_runtime_free_memory(previous);

        previous = current;
        current = current->next;
    }

    if (previous != NdeNullPtr)
        nde_runtime_free_memory(previous);
}

_nde_data_list_item_p _nde_data_list_item_create(NdePtr item_value)
{
    NdePtrSize struct_size = sizeof(_nde_data_list_item);
    _nde_data_list_item_p item = (_nde_data_list_item_p)nde_runtime_alloc_memory(struct_size);

    item->next = NdeNullPtr;
    item->value = item_value;

    return item;
}
