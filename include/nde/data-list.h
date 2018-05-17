// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_DATA_LIST_H_
#define _NDE_DATA_LIST_H_

#include "nde.h"

typedef void *NdeDataList;

#define NDE_DATA_LIST_ERROR_RVALUE -1

/**
 * @constructor
 * Cria uma instância de <NdeDataList>
 */
NdeDataList nde_data_list_create(void);

/**
 * @destructor
 * Libera a memória alocada por uma instância de <NdeDataList>
 */
void nde_data_list_destroy(NdeDataList);

/**
 * Retorna o tamanho da lista
 * 
 * @param {list} Instância de <NdeDataList>
 * 
 * @return O tamanho da lista, ou -1 se houver um erro
 */
int nde_data_list_get_size(NdeDataList);

/**
 * Obtém um item da lista informando a posição
 * 
 * @param {list} Instância de <NdeDataList>
 * @param {pos} Posição do item na lista
 * 
 * @return NdePtr do item na posição informada, ou NdeNullPtr se não existir
 */
NdePtr nde_data_list_get_item(NdeDataList, int);

/**
 * Adiciona um item no final da lista
 * 
 * @param {list} Instância de <NdeDataList>
 * @param {item} Conteúdo do item para adicionar
 * 
 * @return Tamanho da lista após a adição, ou -1 se houver um erro
 */
int nde_data_list_add(NdeDataList, NdePtr);

/**
 * @param {list} Instância de <NdeDataList>
 * @param {pos} Posição da string na lista
 * 
 * @return Tamanho da lista após a remoção, ou -1 se houver um erro
 */
//int nde_data_list_remove_by_position(NdeDataList, int);

#endif // _NDE_DATA_LIST_H_
