/**
 * @file list.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (email do paulo, vitor.spassamani@gmail.com)
 * @brief Implementation file of functions that manipulate the list data-structure.
 * @version 0.1
 * @date 2025-05-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "list.h"
#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct list
{
    Cell *first;
    Cell *last;
    print_fn print_fn;
    compare_key_fn compare_key_fn;
};

int IsEmptyList(List *list)
{
    assert(list);
    return !list->first;
}

int CountList(List *list) //Da pra adicionar o atributo "tamanho" na sentinela, muito custoso contar toda vez.
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

List *CreateList(print_fn print_fn, compare_key_fn compare_key_fn)
{
    List *list = malloc(sizeof(List));
    assert(list);
    list->first = list->last = NULL;
    list->print_fn = print_fn;
    list->compare_key_fn = compare_key_fn;

    return list;
}

void AppendList(List *list, void *value)
{
    assert(list);
    Cell *cell = CreateCell(value);

    if (IsEmptyList(list))
    {
        list->first = list->last = cell;
        return;
    }

    SetNext(list->last, cell);
    list->last = cell;
}

void PrependList(List *list, void *value)
{
    assert(list);
    Cell *cell = CreateCell(value);

    if (IsEmptyList(list))
    {
        list->first = list->last = cell;
        return;
    }

    SetNext(cell, list->first);
    list->first = cell;
}

void InsertList(List *list, void *value, int index)
{
    assert(list);

    if (index == 0)
    {
        PrependList(list, value);
        return;
    }

    int count = CountList(list);

    if (index >= count)
    {
        AppendList(list, value);
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

void RemoveList(List *list, int codigo)
{
    assert(list);

    if (IsEmptyList(list))
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
        FreeCell(cur);
        return;
    } // first element

    if (cur == list->last)
    {
        list->last = prev;
        SetNext(prev, NULL);
        FreeCell(cur);
        return;
    } // last element

    SetNext(prev, GetNext(cur));
    FreeCell(cur); // middle element
}

void *FindList(List *list, int codigo)
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

void *GetFirstList(List *list)
{
    assert(list);
    return GetValue(list->first);
}

void *GetLastList(List *list)
{
    assert(list);
    return GetValue(list->last);
}

void *GetItemByIndexList(List *list, int index) 
{
    assert(list);

    Cell *aux = list->first;

    for(int i = 0; i < index && aux != NULL; i++)
    {
        aux = GetNext(aux);
    }

    if(aux != NULL)
        return GetValue(aux);
    
    return NULL;
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
    ClearList(list);
    free(list);
}

void ClearList(List *list)
{
    assert(list);
    Cell *cur = list->first;
    Cell *next = NULL;

    while (cur)
    {
        next = GetNext(cur);
        FreeCell(cur);
        cur = next;
    }

    list->first = NULL;
}

void DestroyItemsList(List *list, get_id_fn get_id_fn, free_fn free_fn)
{
    assert(list);
    while(!IsEmptyList(list))
    {
        void *item = GetFirstList(list);
        RemoveList(list, get_id_fn(item));
        free_fn(item);
    }
}