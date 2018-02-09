// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>

#include "nde/log.h"
#include "nde/process.h"

int main(int argc, char *argv[])
{
    NdeProcess p = nde_process_create();

    nde_process_set_current_directory(p, ".\\");
    printf("CD: %s\n", nde_process_get_current_directory(p));

    nde_process_set_current_directory(p, "C:\\Arquivos de Programas\\CMake\\bin");
    printf("CD: %s\n", nde_process_get_current_directory(p));

    nde_process_set_current_directory(p, "/usr/bin/");
    printf("CD: %s\n", nde_process_get_current_directory(p));

    nde_process_set_current_directory(p, nde_nullptr);
    printf("CD: %s\n", nde_process_get_current_directory(p));

    return 0;
}
