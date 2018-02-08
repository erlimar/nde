// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_API_RUNTIME_H_
#define _NDE_API_RUNTIME_H_

#include "nde.h"

/**
 * Allocates @size bytes of memory
 * 
 * @param {size} size of memory to alocate
 * @return {nde_ptr} reference
 */
nde_ptr nde_runtime_get_memory(nde_ptr_size size);

/**
 * De-allocates memory used by @ptr
 * 
 * @param {ptr} {nde_ptr} reference
 */
void nde_runtime_clear_memory(nde_ptr ptr);

#endif // _NDE_API_RUNTIME_H_
