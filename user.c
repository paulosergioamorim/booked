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

void PrintAfinitiesUser(User *user)
{
    assert(user);
    int listSize = CountList(user->afinities);

    if (listSize == 0)
        return;

    for (int i = 0; i < listSize - 1; i++)
    {
        printf("%s, ", ((User *)GetItemByIndexList(user->afinities, i))->name);
    }

    printf("%s", ((User *)GetItemByIndexList(user->afinities, listSize - 1))->name);
}

void PrintUser(void *ptr)
{
    User *user = (User *)ptr;
    assert(user);
    printf("\n");
    printf("Leitor: %s\n", user->name);
    printf("Afinidades: ");
    PrintAfinitiesUser(user);
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

/*
Tive que criar funções para retornar a primeira e a última célula (não o valor) de uma lista. Isso faz com que o usuário "conheça um pouco"
da estrutura interna da lista. A outra opção era colocar essa função ConnectUsers() dentro de list.h, o que parece pior, já que lista vai ter
que conhecer user.h
*/
void ConnectUsers(List *userList)
{
    Cell *cur = GetFirstCellList(userList);

    while (cur)
    {
        User *curUser = GetValue(cur);
        Cell *next = GetNext(cur);

        while (next)
        {
            User *nextUser = GetValue(next);

            if (AreCompatibleUsers(curUser, nextUser))
            {
                AppendList(curUser->afinities, nextUser);
                AppendList(nextUser->afinities, curUser);
            }

            next = GetNext(next);
        }

        cur = GetNext(cur);
    }
}