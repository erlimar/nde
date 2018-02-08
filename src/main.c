// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>

#include "nde/log.h"

int main(int argc, char *argv[])
{
    printf("Configura log de nível crítico:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_CRITICAL);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    printf("Configura log de nível falha:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_FAIL);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    printf("Configura log de nível alerta:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_WARNING);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    printf("Configura // log de nível informação:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_INFORMATION);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    printf("Configura log de nível depuração:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_DEBUG);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    printf("Configura // log de todos os níveis:\n");
    {
        LOG_LEVEL(NDE_LOG_LEVEL_TRACE);

        TRCE("Warning message log.");
        DBUG("Debug message log.");
        INFO("Information message log.");
        WARN("Warning message log.");
        FAIL("Fail message log.");
        CRIT("Critical message log.");
        printf("\n");
    }

    return 0;
}
