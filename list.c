#include "list.h"
#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct list
{
    Cell *first;
    Cell *last;
    free_fn free_fn;
    print_fn print_fn;
    compare_key_fn compare_key_fn;
};

int IsEmpty(List *list)
{
    assert(list);
    return !list->first;
}

int Count(List *list)
{
    assert(list);
    int count = 0;
    Cell *cur = list->first;

    while (cur)
    {
        count++;
        cur = GetNext(cur);
    }

    return count;
}

List *CreateList(free_fn free_fn, print_fn print_fn, compare_key_fn compare_key_fn)
{
    List *list = malloc(sizeof(List));
    assert(list);
    list->first = list->last = NULL;
    list->free_fn = free_fn;
    list->print_fn = print_fn;
    list->compare_key_fn = compare_key_fn;

    return list;
}

void Append(List *list, void *value)
{
    assert(list);
    Cell *cell = CreateCell(value);

    if (IsEmpty(list))
    {
        list->first = list->last = cell;
        return;
    }

    SetNext(list->last, cell);
    list->last = cell;
}

void Prepend(List *list, void *value)
{
    assert(list);
    Cell *cell = CreateCell(value);

    if (IsEmpty(list))
    {
        list->first = list->last = cell;
        return;
    }

    SetNext(cell, list->first);
    list->first = cell;
}

void Insert(List *list, void *value, int index)
{
    assert(list);

    if (index == 0)
    {
        Prepend(list, value);
        return;
    }

    int count = Count(list);

    if (index >= count)
    {
        Append(list, value);
        return;
    }

    Cell *prev = NULL;
    Cell *cur = list->first;
    Cell *newCell = CreateCell(value);

    for (int i = 0; i < index; i++)
    {
        prev = cur;
        cur = GetNext(cur);
    }

    SetNext(prev, newCell);
    SetNext(newCell, cur);
}

void Remove(List *list, int codigo)
{
    assert(list);

    if (IsEmpty(list))
    {
        return; // list is empty
    }

    Cell *prev = NULL;
    Cell *cur = list->first;

    while (1)
    {
        if (list->compare_key_fn(GetValue(cur), codigo))
            break;

        if (IsLast(cur))
            return; // not found element

        prev = cur;
        cur = GetNext(cur);
    }

    if (cur == list->first)
    {
        list->first = GetNext(cur);
        FreeCell(cur, list->free_fn);
        return;
    } // first element

    if (cur == list->last)
    {
        list->last = prev;
        SetNext(prev, NULL);
        FreeCell(cur, list->free_fn);
        return;
    } // last element

    SetNext(prev, GetNext(cur));
    FreeCell(cur, list->free_fn); // middle element
}

void *Find(List *list, int codigo)
{
    assert(list);
    Cell *cur = list->first;

    while (cur)
    {
        if (list->compare_key_fn(GetValue(cur), codigo))
            break;

        cur = GetNext(cur);
    }

    if (!cur)
        return NULL;

    return GetValue(cur);
}

void *GetFirst(List *list)
{
    assert(list);
    return GetValue(list->first);
}

void *GetLast(List *list)
{
    assert(list);
    return GetValue(list->last);
}

void PrintList(List *list)
{
    assert(list);
    Cell *cur = list->first;

    while (cur)
    {
        list->print_fn(GetValue(cur));
        cur = GetNext(cur);
    }

    printf("\n");
}

void FreeList(List *list)
{
    assert(list);
    Clear(list);
    free(list);
}

void Clear(List *list)
{
    assert(list);
    Cell *cur = list->first;
    Cell *next = NULL;

    while (cur)
    {
        next = GetNext(cur);
        FreeCell(cur, list->free_fn);
        cur = next;
    }

    list->first = NULL;
}