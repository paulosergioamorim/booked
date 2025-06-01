#pragma once

#include "utils.h"

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

void PrintList(List *list);

void FreeList(List *list);

void ClearList(List *list);