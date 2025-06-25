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

typedef struct list List;

List *CreateList(print_fn print_fn, compare_key_fn compare_key_fn);

int IsEmptyList(List *list);

void AppendList(List *list, void *value);

void RemoveList(List *list, ...);

void *FindList(List *list, ...);

void *GetFirstList(List *list);

void *GetLastList(List *list);

Cell *GetFirstCellList(List *list);

void PrintList(List *list);

void FreeList(List *list);

void ClearList(List *list);

void IterList(List *list, iter_fn iter_fn);

void ForEach(List *list, for_each_fn for_each_fn);

List *GetCommonItemsList(List *list1, List *list2, compare_key_fn compare, print_fn print, compare_items_fn compareItems);