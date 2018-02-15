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
    struct _nde_string_list_item_s *next;
};

typedef struct _nde_string_list_s
{
    struct _nde_string_list_item_s *first_item;
} _nde_string_list;

typedef _nde_string_list *_nde_string_list_p;

// -----------------------------
// Interface de métodos privados
// -----------------------------
void _nde_string_list_init(_nde_string_list_p list);
struct _nde_string_list_item_s *_nde_string_list_item_create(char *);

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

int nde_string_list_get_size(NdeStringList list)
{
    if (list == NdeNullPtr)
        return NDE_STRING_LIST_ERROR_RVALUE;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    int size = 0;
    struct _nde_string_list_item_s *item = self->first_item;

    while (item != NdeNullPtr)
    {
        size++;
        item = item->next;
    }

    return size;
}

int nde_string_list_add(NdeStringList list, char *string)
{
    if (list == NdeNullPtr || string == NdeNullPtr)
        return NDE_STRING_LIST_ERROR_RVALUE;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    int size = 0;
    struct _nde_string_list_item_s *previous = NdeNullPtr;
    struct _nde_string_list_item_s *last = self->first_item;

    while (last != NdeNullPtr)
    {
        previous = last;
        last = last->next;
        size++;
    }

    struct _nde_string_list_item_s *next_item = _nde_string_list_item_create(string);

    if (previous == NdeNullPtr)
        self->first_item = next_item;
    else
        previous->next = next_item;

    return size + 1;
}

char *nde_string_list_get_item(NdeStringList list, int pos)
{
    if (list == NdeNullPtr || pos < 0)
        return NDE_STRING_LIST_ERROR_RVALUE;

    _nde_string_list_p self = ((_nde_string_list_p)list);

    int count = 0;
    struct _nde_string_list_item_s *find = NdeNullPtr;
    struct _nde_string_list_item_s *last = self->first_item;

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
        return NDE_STRING_LIST_ERROR_RVALUE;

    return find->value;
}

// ---------------------------------
// Implementação de métodos privados
// ---------------------------------
void _nde_string_list_init(_nde_string_list_p list)
{
    list->first_item = (struct _nde_string_list_item_s *)NdeNullPtr;
}

struct _nde_string_list_item_s *_nde_string_list_item_create(char *value)
{
    struct _nde_string_list_item_s *item = (struct _nde_string_list_item_s *)nde_runtime_alloc_memory(sizeof(struct _nde_string_list_item_s));

    item->next = NdeNullPtr;
    item->value = value;

    return item;
}
