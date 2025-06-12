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
 * @brief Guarda o void e encadeia o proximo void
 */
typedef struct cell Cell;

/**
 * @brief Cria uma celula de lista encadeada alocada dinamicamente.
 * @param value void previamente criado
 * @returns Celula que deve ser liberada no futuro
 */
Cell *CreateCell(void *value);

/**
 * @param cell Celula previamente criada
 * @returns O void que a celula guarda
 */
void *GetValue(Cell *cell);

/**
 * @param cell Celula previamente criada
 * @returns A proxima celula da celula atual
 */
Cell *GetNext(Cell *cell);

/**
 * @brief Define o void de uma celula
 * @param cell Celula previamente criada
 * @param value void criado
 */
void SetValue(Cell *cell, void *value);

/**
 * @brief Define a proxima celula de uma celula atual
 * @param cell Celula previamente criada
 * @param next Proxima celula a ser encadeada
 */
void SetNext(Cell *cell, Cell *next);

/**
 * @param cell Celula que ainda nao foi liberada
 */
void FreeCell(Cell *cell);

/**
 * @param cell Celula previamente criada
 * @returns Se a celula e a ultima em uma lista encadeada
 */
int IsLast(Cell *cell);