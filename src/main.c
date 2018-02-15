// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>
#include <string.h>

#include "nde/string-list.h"
#include "nde/process.h"
#include "nde/log.h"
#include "nde/api/runtime.h"

int main(int argc, char *argv[])
{
    NdeProcess proc = nde_process_create();

    nde_process_set_command(proc, "cmd.exe");
    nde_process_set_current_directory(proc, "D:\\temp\\SystemZ");

    printf("main(!)\n");

    DBUG("NdeProcess proc {\n");
    DBUG("  input_handle: \"%d\",\n", nde_process_get_input_handle(proc));
    DBUG("  output_handle: \"%d\",\n", nde_process_get_output_handle(proc));
    DBUG("  error_handle: \"%d\",\n", nde_process_get_error_handle(proc));
    DBUG("  command: \"%s\",\n", nde_process_get_command(proc));
    DBUG("  current_directory: \"%s\",\n", nde_process_get_current_directory(proc));
    DBUG("  command_args: {\n");
    DBUG("  },\n");
    DBUG("  command_env: {\n");
    DBUG("  }\n");
    DBUG("};\n");

    return 0;
}
