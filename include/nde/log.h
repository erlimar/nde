// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_LOG_H_
#define _NDE_LOG_H_

#include "nde.h"

/**
 * Configura o nível do log
 */
void nde_log_config_level(byte);

/**
 * Escreve mensagem no mecanismo de log
 */
void nde_log_write(byte, const char *);

/**
 * Níveis de log
 */
#define NDE_LOG_LEVEL_CRITICAL 1
#define NDE_LOG_LEVEL_FAIL 2
#define NDE_LOG_LEVEL_WARNING 3
#define NDE_LOG_LEVEL_INFORMATION 4
#define NDE_LOG_LEVEL_DEBUG 5
#define NDE_LOG_LEVEL_TRACE 6

/**
 * Atalhos para escrever mensagens de log
 */
#define TRCE(msg) nde_log_write(NDE_LOG_LEVEL_TRACE, msg)
#define DBUG(msg) nde_log_write(NDE_LOG_LEVEL_DEBUG, msg)
#define INFO(msg) nde_log_write(NDE_LOG_LEVEL_INFORMATION, msg)
#define WARN(msg) nde_log_write(NDE_LOG_LEVEL_WARNING, msg)
#define FAIL(msg) nde_log_write(NDE_LOG_LEVEL_FAIL, msg)
#define CRIT(msg) nde_log_write(NDE_LOG_LEVEL_CRITICAL, msg)

/**
 * Atalhos para configurar o mecanismo de log
 */
#define LOG_LEVEL(level) nde_log_config_level(level)

#endif // _NDE_LOG_H_
