/**
 * @file user.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
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
#include <string.h>
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

void PrintAfinity(void *ptr, int isLast);

User *CreateUser(int id, char *name, int lenPreferences, char **preferences)
{
    User *user = malloc(sizeof(User));
    assert(user);
    user->id = id;
    user->name = strdup(name);
    user->lenPreferences = lenPreferences;
    user->preferences = preferences;
    user->finishedBooks = CreateList(PrintBook, IsSameIdOfBook);
    user->whishedBooks = CreateList(PrintBook, IsSameIdOfBook);
    user->afinities = CreateList(PrintAfinity, IsSameIdOfUser);

    return user;
}

User *ReadUser(FILE *file)
{
    int id = 0;
    char name[MAX_LINE_LENGTH] = "";
    int lenPreferences = 0;

    if (fscanf(file, "%d;%[^;];%d", &id, name, &lenPreferences) == EOF)
    {
        return NULL;
    }

    char **preferences = malloc(lenPreferences * sizeof(char *));

    for (int i = 0; i < lenPreferences; i++)
    {
        char preference[MAX_LINE_LENGTH] = "";
        fscanf(file, ";%[^;\n]", preference);
        preferences[i] = strdup(preference);
    }

    return CreateUser(id, name, lenPreferences, preferences);
}

int IsSameIdOfUser(void *ptr, int id)
{
    User *user = (User *)ptr;
    assert(user);

    return user->id == id;
}

void PrintUser(void *ptr, int)
{
    User *user = (User *)ptr;
    assert(user);
    printf("\n");
    printf("Leitor: %s\n", user->name);
    printf("Afinidades: ");
    PrintList(user->afinities);
    printf("\n");
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

int GetIdUser(void *ptr)
{
    User *user = (User *)ptr;
    assert(user);
    return user->id;
}

int AreCompatibleUsers(User *user1, User *user2)
{
    assert(user1);
    assert(user2);

    for (int i = 0; i < user1->lenPreferences; i++)
    {
        for (int j = 0; j < user2->lenPreferences; j++)
        {
            if (strcmp(user1->preferences[i], user2->preferences[j]) == 0)
                return 1;
        }
    }

    return 0;
}

void ConnectUsers(void *ptr1, void *ptr2)
{
    User *user1 = (User *)ptr1;
    User *user2 = (User *)ptr2;
    assert(user1 && user2);

    if (AreCompatibleUsers(user1, user2))
    {
        AppendList(user1->afinities, user2);
        AppendList(user2->afinities, user1);
    }
}

void PrintAfinity(void *ptr, int isLast)
{
    User *user = (User *)ptr;
    assert(user);
    printf("%s", user->name);

    if (!isLast)
        printf(", ");
}
