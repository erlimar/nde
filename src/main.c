// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/string-list.h"
#include "nde/api/runtime.h"

int main(int argc, char *argv[])
{
    NdeStringList list = nde_string_list_create();

    //REPL
    while (1)
    {
        char cmd[102];

        printf("Informe um valor (vazio termina): ");
        gets_s(&cmd, 1024);

        int length = strlen(cmd);
        char *cmd_str = (char *)nde_runtime_alloc_memory(length + 1);
        
        strcpy(cmd_str, cmd);

        if (strncmp(cmd_str, "", length) == 0)
            break;

        nde_string_list_add(list, cmd_str);
    }

    int size = nde_string_list_get_size(list);

    printf("list->size: %d\n", size);

    for (int i = 0; i < size; i++)
    {
        printf("  list[%d]: %s\n", i, nde_string_list_get_item(list, i));
    }

    return 0;
}
