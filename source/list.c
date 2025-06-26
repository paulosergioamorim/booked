/**
 * @file list.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
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
#include <stdarg.h>
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

void RemoveList(List *list, ...)
{
    assert(list);
    Cell *prev = NULL;
    Cell *cur = list->first;
    va_list keys_list;
    va_start(keys_list, list);

    while (cur)
    {
        va_list keys_copy;
        va_copy(keys_copy, keys_list);

        if (list->compare_key_fn(GetValue(cur), keys_copy))
        {
            va_end(keys_copy);
            va_end(keys_list);
            break;
        }

        va_end(keys_copy);
        prev = cur;
        cur = GetNext(cur);
    }

    va_end(keys_list);

    if (!cur)
        return; // not found

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

void *FindList(List *list, ...)
{
    assert(list);
    Cell *cur = list->first;
    va_list keys_list;
    va_start(keys_list, list);

    while (cur)
    {
        va_list keys_copy;
        va_copy(keys_copy, keys_list);

        if (list->compare_key_fn(GetValue(cur), keys_copy))
        {
            va_end(keys_copy);
            va_end(keys_list);
            return GetValue(cur);
        }

        va_end(keys_copy);
        cur = GetNext(cur);
    }

    va_end(keys_list);

    return NULL;
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

Cell *GetFirstCellList(List *list)
{
    assert(list);
    return list->first;
}

void PrintList(List *list)
{
    assert(list);
    Cell *cur = list->first;

    while (cur)
    {
        list->print_fn(GetValue(cur), IsLast(cur));
        cur = GetNext(cur);
    }
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
    Cell *prev = NULL;
    Cell *cur = list->first;

    while (cur)
    {
        prev = cur;
        cur = GetNext(cur);
        FreeCell(prev);
    }

    list->first = NULL;
}

void IterList(List *list, iter_fn iter_fn)
{
    assert(list);
    Cell *cur = list->first;

    while (cur)
    {
        void *curVal = GetValue(cur);
        Cell *next = GetNext(cur);

        while (next)
        {
            void *nextVal = GetValue(next);
            iter_fn(curVal, nextVal);
            next = GetNext(next);
        }

        cur = GetNext(cur);
    }
}

void ForEach(List *list, for_each_fn for_each_fn)
{
    assert(list);
    Cell *cur = list->first;

    while (cur)
    {
        for_each_fn(GetValue(cur));
        cur = GetNext(cur);
    }
}

List *GetCommonItemsList(List *list1, List *list2, compare_key_fn compareKey, print_fn print, compare_items_fn compareItems)
{
    assert(list1);
    assert(list2);
    List *commonItems = CreateList(print, compareKey);

    Cell *c1 = list1->first;
    Cell *c2 = NULL;
    while (c1 != NULL)
    {
        c2 = list2->first;
        while (c2 != NULL)
        {
            if (compareItems(GetValue(c1), GetValue(c2)))
            {
                AppendList(commonItems, GetValue(c1));
                break;
            }
            c2 = GetNext(c2);
        }
        c1 = GetNext(c1);
    }

    return commonItems;
}