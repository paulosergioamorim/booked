/**
 * @file list.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the list data-structure.
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "utils.h"
#include "cell.h"

/**
 * @brief Tipo opaco que representa uma lista encadeada.
 */
typedef struct list List;

/**
 * @brief Cria uma nova lista encadeada.
 *
 * @param print_fn          Função de impressão dos elementos.
 * @param compare_key_fn    Função para comparar elementos com chaves.
 * @return Ponteiro para a nova List criada.
 */
List *CreateList(print_fn print_fn, compare_key_fn compare_key_fn);

/**
 * @brief Verifica se a lista está vazia.
 *
 * @param list Ponteiro para a lista.
 * @return 1 se vazia, 0 caso contrário.
 */
int IsEmptyList(List *list);

/**
 * @brief Adiciona um elemento ao final da lista.
 *
 * @param list  Ponteiro para a lista.
 * @param value Ponteiro para o dado a ser inserido.
 */
void AppendList(List *list, void *value);

/**
 * @brief Remove um elemento da lista com base em uma chave variádica.
 *
 * @param list Lista da qual o elemento será removido.
 * @param ...  Chaves para busca.
 */
void RemoveList(List *list, ...);

/**
 * @brief Busca um elemento na lista com base em uma chave variádica.
 *
 * @param list Lista onde realizar a busca.
 * @param ...  Chaves para busca.
 * @return Ponteiro para o elemento encontrado, ou NULL se não encontrado.
 */
void *FindList(List *list, ...);

/**
 * @brief Retorna o primeiro elemento da lista.
 *
 * @param list Lista alvo.
 * @return Ponteiro para o primeiro elemento, ou NULL se vazia.
 */
void *GetFirstList(List *list);

/**
 * @brief Retorna o último elemento da lista.
 *
 * @param list Lista alvo.
 * @return Ponteiro para o último elemento, ou NULL se vazia.
 */
void *GetLastList(List *list);

/**
 * @brief Retorna a primeira célula da lista.
 *
 * @param list Lista alvo.
 * @return Ponteiro para a primeira Cell, ou NULL se vazia.
 */
Cell *GetFirstCellList(List *list);

/**
 * @brief Imprime todos os elementos da lista.
 *
 * @param list Lista a ser impressa.
 */
void PrintList(List *list);

/**
 * @brief Libera a estrutura da lista (não libera os elementos).
 *
 * @param list Lista a ser liberada.
 */
void FreeList(List *list);

/**
 * @brief Remove todos os elementos da lista.
 *
 * Mantém a estrutura da lista, mas esvazia seu conteúdo.
 *
 * @param list Lista a ser limpa.
 */
void ClearList(List *list);

/**
 * @brief Executa uma função para cada par de elementos da lista.
 *
 * Usado para operações que combinam dois elementos, como verificação de afinidade.
 *
 * @param list     Lista alvo.
 * @param iter_fn  Função de callback que processa pares de elementos.
 */
void IterList(List *list, iter_fn iter_fn);

/**
 * @brief Executa uma função para cada elemento da lista.
 *
 * @param list        Lista alvo.
 * @param for_each_fn Função de callback que processa cada elemento.
 */
void ForEach(List *list, for_each_fn for_each_fn);

/**
 * @brief Retorna uma nova lista com os elementos comuns entre duas listas.
 *
 * @param list1         Primeira lista.
 * @param list2         Segunda lista.
 * @param compare       Função para comparar elementos por chave.
 * @param print         Função de impressão para os elementos da nova lista.
 * @param compareItems  Função para comparação direta dos elementos.
 * @return Lista contendo os elementos comuns.
 */
List *GetCommonItemsList(List *list1,
                         List *list2,
                         compare_key_fn compare,
                         print_fn print,
                         compare_items_fn compareItems);