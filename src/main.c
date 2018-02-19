// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/data-list.h"
#include "nde/process.h"
#include "nde/log.h"
#include "nde/api/runtime.h"

int main(int argc, char *argv[], char *envp[])
{
    // for (int i = 0; envp != NdeNullPtr && envp[i] != NdeNullPtr; i++)
    // {
    //     char *env_line = envp[i];
    //     char *equal_p = strpbrk(env_line, "=");
    //     char *key = NdeNullPtr;
    //     char *value = NdeNullPtr;

    //     DBUG("env_line: %s\n", env_line);

    //     if (equal_p)
    //     {
    //         int length = equal_p - env_line;
    //         printf(" --> key_length:   {%d}\n", length);
            
    //         key = nde_runtime_alloc_str_memory(length);
    //         strncpy(key, env_line, length);

    //         value = equal_p + 1;
    //     }

    //     printf(" --> key:   {%s}\n", key);
    //     printf(" --> value: {%s}\n", value);

    //     if (i > 5)
    //         break;
    // }

    NdeProcess process = nde_process_create();

    nde_process_set_env_from_envp(process, envp);

    nde_process_destroy(process);

    return 0;
}
