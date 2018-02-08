// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_API_RUNTIME_H_
#define _NDE_API_RUNTIME_H_

#include "nde.h"

/**
 * Aloca @size bytes de memória
 * 
 * @param {size} Tamanho da memória para alocar
 * @return {nde_ptr} Referência de memória
 */
nde_ptr nde_runtime_alloc_memory(nde_ptr_size size);

/**
 * Desaloca memória usada por <ptr>
 * 
 * @param {ptr} {nde_ptr} Referência de memória
 */
void nde_runtime_free_memory(nde_ptr ptr);

#endif // _NDE_API_RUNTIME_H_
