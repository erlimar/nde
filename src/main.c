// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/process.h"
#include "nde/log.h"

int main(int argc, char *argv[], char *envp[])
{
    NdeProcess process = nde_process_create();

    nde_process_set_args_from_argv(process, argc, argv);

    int args_size = nde_process_get_args_size(process);

    DBUG("args_size: %d\n", args_size);

    for (int i = 0; i < args_size; i++)
    {
        char *arg_value = nde_process_get_arg(process, i);
        
        DBUG("arg[%d], %s\n", i, arg_value);
    }

    nde_process_destroy(process);

    return 0;
}
