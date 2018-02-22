// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/process.h"
#include "nde/log.h"

int main(int argc, char *argv[], char *envp[])
{
    nde_log_config_level(NDE_LOG_LEVEL_TRACE);

    if (argc < 2)
    {
        printf("Usage: nde <command> [args]\n");
    }

    NdeProcess process = nde_process_create();

    nde_process_set_command(process, argv[1]);

    nde_process_set_args_from_argv(process, --argc, ++argv);
    nde_process_set_env_from_envp(process, envp);

    printf("<command>: %s\n", nde_process_get_command(process));
    printf("<cwd>: %s\n", nde_process_get_current_directory(process));

    printf("<aguments>:\n");
    int args_size = nde_process_get_args_size(process);

    for (int i = 0; i < args_size; i++)
    {
        char *arg_value = nde_process_get_arg(process, i);

        printf("    arg[%d] %s\n", i, arg_value);
    }

    printf("<environment>:\n");
    int env_size = nde_process_get_env_size(process);

    for (int i = 0; i < env_size; i++)
    {
        char *env_key = nde_process_get_env_key(process, i);
        char *env_value = nde_process_get_env(process, env_key);

        printf("    [%s] = {%s}\n", env_key, env_value);

        if (i >= 5)
        {
            printf("    [...]\n");
            break;
        }
    }

    nde_process_destroy(process);

    return 0;
}
