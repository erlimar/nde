// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_LOG_H_
#define _NDE_LOG_H_

#include <stdarg.h>

#include "nde.h"

/**
 * Configura o nível do log
 */
void nde_log_config_level(NdeByte);

/**
 * Escreve mensagem no mecanismo de log
 */
void nde_log_write(NdeByte, const char *, ...);

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
#define TRCE(msg, ...) nde_log_write(NDE_LOG_LEVEL_TRACE, msg, ##__VA_ARGS__)
#define DBUG(msg, ...) nde_log_write(NDE_LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__)
#define INFO(msg, ...) nde_log_write(NDE_LOG_LEVEL_INFORMATION, msg, ##__VA_ARGS__)
#define WARN(msg, ...) nde_log_write(NDE_LOG_LEVEL_WARNING, msg, ##__VA_ARGS__)
#define FAIL(msg, ...) nde_log_write(NDE_LOG_LEVEL_FAIL, msg, ##__VA_ARGS__)
#define CRIT(msg, ...) nde_log_write(NDE_LOG_LEVEL_CRITICAL, msg, ##__VA_ARGS__)

/**
 * Atalhos para configurar o mecanismo de log
 */
#define LOG_LEVEL(level) nde_log_config_level(level)

#endif // _NDE_LOG_H_
