// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_PROCESS_H_
#define _NDE_PROCESS_H_

#include "nde.h"

typedef void *NdeProcess;

/**
 * @constructor
 * Cria uma instância de <NdeProcess>
 */
NdeProcess nde_process_create(void);

/**
 * @destructor
 * Libera a memória alocada por uma instância de <NdeProcess>
 */
void nde_process_destroy(NdeProcess);

// void nde_process_set_handles(nde_process_p,
//                              NdePtr,
//                              NdePtr,
//                              NdePtr);

/**
 * Obtem o valor do comando do processo
 * 
 * @return (char*) Comando do processo
 */
char *nde_process_get_command(NdeProcess);

/**
 * Atribui o valor do comando do processo
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {command} Valor do comando
 */
void nde_process_set_command(NdeProcess, char *);

/**
 * Obtem o valor do diretório atual do processo
 * 
 * @return (char*) Diretório atual do processo
 */
char *nde_process_get_current_directory(NdeProcess);

/**
 * Atribui o valor do diretório atual do processo
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {command} Valor diretório atual do processo
 */
void nde_process_set_current_directory(NdeProcess, char *);

//void nde_process_start_and_wait(nde_process_p);

#endif // _NDE_PROCESS_H_
