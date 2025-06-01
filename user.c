/**
 * @file user.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (email do paulo, vitor.spassamani@gmail.com)
 * @brief Implementation file of functions that manipulate the user struct.
 * @version 0.1
 * @date 2025-05-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "user.h"
#include "utils.h"
#include "list.h"

struct user
{
    int id;
    char *name;
    int lenPreferences;
    char **preferences;
    List *finishedBooks;
    List *whishedBooks;
    List *afinities;
};

User *CreateUser(int id, char *name, int lenPreferences, char **preferences)
{
    User *user = malloc(sizeof(User));
    assert(user);
    user->id = id;
    user->name = name;
    user->lenPreferences = lenPreferences;
    user->preferences = preferences;
    user->finishedBooks = CreateList(PrintBook, IsSameIdOfBook);
    user->whishedBooks = CreateList(PrintBook, IsSameIdOfBook);
    user->afinities = CreateList(PrintUser, IsSameIdOfUser);

    return user;
}

User *ReadUser(FILE *file)
{
    int id = 0;
    char *name = malloc(MAX_LINE_LENGTH * sizeof(char));
    int lenPreferences = 0;

    if (fscanf(file, "%d;%[^;];%d", &id, name, &lenPreferences) == EOF)
    {
        free(name);
        return NULL;
    }

    char **preferences = malloc(lenPreferences * sizeof(char *));

    for (int i = 0; i < lenPreferences; i++)
    {
        preferences[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
        fscanf(file, ";%[^;\n]", preferences[i]);
    }

    return CreateUser(id, name, lenPreferences, preferences);
}

int IsSameIdOfUser(void *ptr, int id)
{
    User *user = (User *)ptr;
    assert(user);

    return user->id == id;
}

void PrintUser(void *ptr)
{
    User *user = (User *)ptr;
    assert(user);
    printf("%s\n", user->name);
}

void FreeUser(void *ptr)
{
    User *user = (User *)ptr;
    assert(user);
    free(user->name);

    for (int i = 0; i < user->lenPreferences; i++)
        free(user->preferences[i]);

    free(user->preferences);

    FreeList(user->finishedBooks);
    FreeList(user->whishedBooks);
    FreeList(user->afinities);

    free(user);
}

int GetIdUser(void *ptr) {
    User *user = (User *)ptr;
    assert(user);
    return user->id;
}