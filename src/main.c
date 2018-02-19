// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/process.h"
#include "nde/log.h"

int main(int argc, char *argv[], char *envp[])
{
    NdeProcess process = nde_process_create();

    nde_process_set_env_from_envp(process, envp);

    int env_size = nde_process_get_env_size(process);

    DBUG("env_size: %d\n", env_size);

    for (int i = 0; i < env_size; i++)
    {
        char *env_key = nde_process_get_env_key(process, i);
        char *env_value = nde_process_get_env(process, env_key);
        DBUG("  [%d]: {%s} => {%s}\n", i, env_key, env_value);
    }

    nde_process_destroy(process);

    return 0;
}
