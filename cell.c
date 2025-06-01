/**
 * @file cell.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (email do paulo, vitor.spassamani@gmail.com)
 * @brief Implementation file of functions that manipulate the cell struct.
 * @version 0.1
 * @date 2025-05-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "cell.h"

#include <stdlib.h>
#include <assert.h>

struct cell
{
    void *value;
    Cell *next;
};

Cell *CreateCell(void *value)
{
    Cell *cell = malloc(sizeof(Cell));
    assert(cell);
    cell->value = value;
    cell->next = NULL;

    return cell;
}

void *GetValue(Cell *cell)
{
    assert(cell);
    return cell->value;
}

Cell *GetNext(Cell *cell)
{
    assert(cell);
    return cell->next;
}

void SetValue(Cell *cell, void *value)
{
    assert(cell);
    cell->value = value;
}

void SetNext(Cell *cell, Cell *next)
{
    assert(cell);
    cell->next = next;
}

void FreeCell(Cell *cell)
{
    assert(cell);
    free(cell);
}

int IsLast(Cell *cell)
{
    assert(cell);
    return !cell->next;
}