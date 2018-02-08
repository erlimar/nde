// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_PROCESS_H_
#define _NDE_PROCESS_H_

typedef struct nde_process_s
{
    int input_handle;
} nde_process;

typedef nde_process *nde_process_p;

/**
 * @constructor
 * Creates an instance of nde_process
 */
nde_process_p nde_process_create(void);

/**
 * @destructor
 * Releases the memory allocated by the nde_process instance
 */
void nde_process_destroy(nde_process_p);

#endif // _NDE_PROCESS_H_