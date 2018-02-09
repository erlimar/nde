// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_STRING_LIST_H_
#define _NDE_STRING_LIST_H_

#include "nde.h"

typedef void *NdeStringList;

/**
 * @constructor
 * Cria uma instância de <NdeStringList>
 */
NdeStringList nde_string_list_create(void);

/**
 * @destructor
 * Libera a memória alocada por uma instância de <NdeStringList>
 */
void nde_string_list_destroy(NdeStringList);

#endif // _NDE_STRING_LIST_H_
