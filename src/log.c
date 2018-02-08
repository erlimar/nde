// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#include <stdio.h>

#include "nde.h"
#include "nde/log.h"

// --------------------------
// Variáveis globais privadas
// --------------------------

#ifdef DEBUG
static byte _nde_log_config_level = NDE_LOG_LEVEL_DEBUG;
#else
static byte _nde_log_config_level = NDE_LOG_LEVEL_FAIL;
#endif

// ---------------------------------
// Implementação de métodos públicos
// ---------------------------------

void nde_log_config_level(byte level)
{
    _nde_log_config_level = level;
}

void nde_log_write(byte level, const char *msg)
{
    if (level > _nde_log_config_level)
    {
        return;
    }

    char *prefix;

    switch (level)
    {
    case NDE_LOG_LEVEL_CRITICAL:
        prefix = "CRIT";
        break;
    case NDE_LOG_LEVEL_FAIL:
        prefix = "FAIL";
        break;
    case NDE_LOG_LEVEL_WARNING:
        prefix = "WARN";
        break;
    case NDE_LOG_LEVEL_INFORMATION:
        prefix = "INFO";
        break;
    case NDE_LOG_LEVEL_DEBUG:
        prefix = "DBUG";
        break;
    case NDE_LOG_LEVEL_TRACE:
    default:
        prefix = "TRCE";
    }

    printf("%s: %s\n", prefix, msg);
}
