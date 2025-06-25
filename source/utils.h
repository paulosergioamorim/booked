/**
 * @file utils.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <stdio.h>

#define MAX_LINE_LENGTH 256

FILE *OpenFileToRead(char *source);

typedef void (*free_fn)(void *);

typedef int (*compare_key_fn)(void *, int);

typedef int (*compare_items_fn)(void *, void *);

typedef void (*print_fn)(void *, int);

typedef void (*for_each_fn)(void *);

typedef void (*iter_fn)(void *, void *);