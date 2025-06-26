/**
 * @file cell.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the cell struct.
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "utils.h"

/**
 * @brief Tipo opaco para uma célula de lista encadeada.
 *
 * Cada célula armazena um ponteiro genérico (void*) e
 * um ponteiro para a próxima célula na lista.
 */
typedef struct cell Cell;

/**
 * @brief Cria uma nova célula alocada dinamicamente.
 *
 * A célula criada terá o campo de valor inicializado com @p value
 * e o ponteiro next definido como NULL.
 *
 * @param value Ponteiro para o dado que a célula deve armazenar.
 *              Não faz cópia; o gerenciamento de memória desse dado
 *              fica a cargo do usuário.
 * @return Ponteiro para a nova célula; NULL se falha na alocação.
 */
Cell *CreateCell(void *value);

/**
 * @brief Retorna o dado armazenado na célula.
 *
 * @param cell Ponteiro para a célula válida (não-NULL).
 * @return Ponteiro genérico (void*) armazenado na célula;
 *         NULL se @p cell for NULL.
 */
void *GetValue(Cell *cell);

/**
 * @brief Retorna a próxima célula no encadeamento.
 *
 * @param cell Ponteiro para a célula válida (não-NULL).
 * @return Ponteiro para a próxima célula;
 *         NULL se @p cell for NULL ou se for a última célula.
 */
Cell *GetNext(Cell *cell);

/**
 * @brief Atualiza o dado armazenado na célula.
 *
 * @param cell  Ponteiro para a célula válida (não-NULL).
 * @param value Novo ponteiro de dado (void*) a ser armazenado.
 *              Não faz cópia; o gerenciamento de memória desse dado
 *              fica a cargo do usuário.
 */
void SetValue(Cell *cell, void *value);

/**
 * @brief Atualiza o ponteiro para a próxima célula.
 *
 * @param cell Ponteiro para a célula atual (não-NULL).
 * @param next Ponteiro para a célula seguinte no encadeamento,
 *             ou NULL para indicar fim de lista.
 */
void SetNext(Cell *cell, Cell *next);

/**
 * @brief Libera a memória alocada para a célula.
 *
 * Não libera o dado armazenado (void*); apenas a estrutura Cell.
 * O usuário é responsável por desalocar o conteúdo apontado
 * por value, se necessário.
 *
 * @param cell Ponteiro para a célula a ser liberada;
 *             ignora se for NULL.
 */
void FreeCell(Cell *cell);

/**
 * @brief Verifica se a célula é a última de uma lista.
 *
 * Uma célula é considerada última se seu ponteiro next for NULL.
 *
 * @param cell Ponteiro para a célula válida (não-NULL).
 * @return 1 se for a última célula (next == NULL),
 *         0 caso contrário.
 */
int IsLast(Cell *cell);