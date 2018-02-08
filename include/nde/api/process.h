// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_PROCESS_H_
#define _NDE_PROCESS_H_

typedef struct
{
    int stdin;
    int stdout;
} NdeProcess;

NdeProcess nde_create_process(void);

#endif // _NDE_PROCESS_H_
