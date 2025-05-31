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

void FreeCell(Cell *cell, free_fn free_fn)
{
    assert(cell);
    free_fn(cell->value);
    free(cell);
}

int IsLast(Cell *cell)
{
    assert(cell);
    return !cell->next;
}