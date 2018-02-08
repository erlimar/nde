// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>

#include "nde/process.h"

int main(int argc, char *argv[])
{
    nde_process g = {57};

    nde_process_p p = nde_process_create();

    printf("Hello World (%d)!\n", g.input_handle);
    printf("Hello World (%d)!\n", p->input_handle);

#ifdef DEBUG
    printf("Press [ENTER] to close!");
    scanf("debug");
#endif

    return 0;
}
