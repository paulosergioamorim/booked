#pragma once

#include "utils.h"

typedef struct list List;

List *CreateList(free_fn free_fn, print_fn print_fn, compare_key_fn compare_key_fn);

int IsEmpty(List *list);

int Count(List *list);

void Append(List *list, void *value);

void Prepend(List *list, void *value);

void Insert(List *list, void *value, int index);

void Remove(List *list, int codigo);

void *Find(List *list, int codigo);

void *GetFirst(List *list);

void *GetLast(List *list);

void PrintList(List *list);

void FreeList(List *list);

void Clear(List *list);