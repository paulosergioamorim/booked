/**
 * @file utils.c
 * @author Paulo Sergio Amorim (@paulosergioamorim)
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

FILE *OpenFileToRead(char *source)
{
    FILE *fp = fopen(source, "r+");
    assert(fp);

    return fp;
}

char *ReadLine()
{
    char *buffer = malloc(MAX_LINE_LENGTH * sizeof(char));
    assert(buffer);
    scanf(" %[^\n]%*c", buffer);

    return buffer;
}