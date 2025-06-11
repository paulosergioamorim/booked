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

int CountList(List *list);

void AppendList(List *list, void *value);

void PrependList(List *list, void *value);

void InsertList(List *list, void *value, int index);

void RemoveList(List *list, int codigo);

void *FindList(List *list, int codigo);

void *GetFirstList(List *list);

void *GetLastList(List *list);

void *GetItemByIndexList(List *list, int index);

Cell *GetFirstCellList(List* list);

void PrintList(List *list);

void FreeList(List *list);

void ClearList(List *list);

void DestroyItemsList(List *list, get_id_fn get_id_fn, free_fn free_fn);

void IterList(List *list, iter_fn iter_fn);

List *GetCommonItemsList(List* list1, List *list2, compare_key_fn compare, print_fn print, compare_items_fn compareItems);