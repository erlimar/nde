// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>

#include "nde/string-list.h"

int main(int argc, char *argv[])
{
    NdeStringList list = nde_string_list_create();

    int s1 = nde_string_list_add(list, "Valor 1");
    int s2 = nde_string_list_add(list, "Valor 2");
    int s3 = nde_string_list_add(list, "Valor 3");
    int s4 = nde_string_list_add(list, "Valor 4");

    int size = nde_string_list_get_size(list);

    printf("list->size: %d, s1: %d, s2: %d, s3: %d, s4: %d\n", size, s1, s2, s3, s4);

    for (int i = 0; i < size; i++)
    {
        printf("  list[%d]: %s\n", i, nde_string_list_get_item(list, i));
    }

    return 0;
}
