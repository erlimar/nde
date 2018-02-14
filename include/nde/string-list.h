// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_STRING_LIST_H_
#define _NDE_STRING_LIST_H_

#include "nde.h"

typedef void *NdeStringList;

#define NDE_STRING_LIST_ERROR_RVALUE -1

/**
 * @constructor
 * Cria uma instância de <NdeStringList>
 */
NdeStringList nde_string_list_create(void);

/**
 * @destructor
 * Libera a memória alocada por uma instância de <NdeStringList>
 */
void nde_string_list_destroy(NdeStringList);

/**
 * Retorna o tamanho da lista
 * 
 * @param {list} Instância de <NdeStringList>
 * 
 * @return O tamanho da lista, ou -1 se houver um erro
 */
int nde_string_list_length(NdeStringList);

/**
 * Obtém uma string da lista informando a posição
 * 
 * @param {list} Instância de <NdeStringList>
 * @param {pos} Posição da string na lista
 * 
 * @return String na posição informada, ou NdeNullPtr se não existir
 */
char *nde_string_list_get_by_position(NdeStringList, int);

/**
 * Adiciona uma string no final dalista
 * 
 * @param {list} Instância de <NdeStringList>
 * @param {string} Conteúdo da string para adicionar
 * 
 * @return Tamanho da lista após a adição, ou -1 se houver um erro
 */
int nde_string_list_add(NdeStringList, char *);

/**
 * @param {list} Instância de <NdeStringList>
 * @param {pos} Posição da string na lista
 * 
 * @return Tamanho da lista após a remoção, ou -1 se houver um erro
 */
int nde_string_list_remove_by_position(NdeStringList, int);

#endif // _NDE_STRING_LIST_H_
