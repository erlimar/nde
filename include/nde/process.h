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

/**
 * Atribui o handle para arquivo <input>
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {handle} Handle para arquivo
 */
void nde_process_set_input_handle(NdeProcess, NdePtr);

/**
 * Obtem o valor do handle para arquivo <input>
 * 
 * @param {process} Instância de <NdeProcess>
 * @return (NdePtr) Handle do arquivo
 */
NdePtr nde_process_get_input_handle(NdeProcess);

/**
 * Atribui o handle para arquivo <output>
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {handle} Handle para arquivo
 */
void nde_process_set_output_handle(NdeProcess, NdePtr);

/**
 * Obtem o valor do handle para arquivo <output>
 * 
 * @param {process} Instância de <NdeProcess>
 * @return (NdePtr) Handle do arquivo
 */
NdePtr nde_process_get_output_handle(NdeProcess);

/**
 * Atribui o handle para arquivo <error>
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {handle} Handle para arquivo
 */
void nde_process_set_error_handle(NdeProcess, NdePtr);

/**
 * Obtem o valor do handle para arquivo <error>
 * 
 * @param {process} Instância de <NdeProcess>
 * @return (NdePtr) Handle do arquivo
 */
NdePtr nde_process_get_error_handle(NdeProcess);

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

/**
 * Atribui a lista de variáveis de ambiente do processo
 * de acordo com o parâmetro envp da função <main>
 * 
 * @param {process} Instância de <NdeProcess>
 * @param {envp} Referência as variáveis de ambiente da função <main>
 */

void nde_process_set_env_from_envp(NdeProcess, char *[]);

// int nde_process_get_env_size(NdeProcess);
// char *nde_process_get_env(NdeProcess, int);

//void nde_process_start_and_wait(nde_process_p);

#endif // _NDE_PROCESS_H_
