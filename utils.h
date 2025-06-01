#pragma once

#include <stdio.h>

#define MAX_LINE_LENGTH 256

FILE *OpenFileToRead(char *source);

char *ReadLine();

typedef void (*free_fn)(void *);

typedef int (*compare_key_fn)(void *, int key);

typedef int (*get_id_fn)(void *item);

typedef void (*print_fn)(void *);