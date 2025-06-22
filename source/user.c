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
    List *recommendations;
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
    user->recommendations = CreateList(PrintBook, IsSameIdOfBook);
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
    printf("Leitor: %s\n", user->name);
    printf("Lidos: ");
    PrintList(user->finishedBooks);
    printf("\n");
    printf("Desejados: ");
    PrintList(user->whishedBooks);
    printf("\n");
    printf("Recomendacoes: ");
    PrintList(user->recommendations);
    printf("\n");
    printf("Afinidades: ");
    PrintList(user->afinities);
    printf("\n\n");
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
    FreeList(user->recommendations);
    FreeList(user->afinities);

    free(user);
}

int GetIdUser(void *ptr)
{
    User *user = (User *)ptr;
    assert(user);
    return user->id;
}

char *GetNameUser(void *ptr)
{
    assert(ptr);

    return ((User *)ptr)->name;
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
    assert(user1);
    assert(user2);

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
    {
        printf(", ");
    }
}

/*
 * TODO: IMPLEMENTAR FRASES DE LOG DAS FUNÇÕES ABAIXO
 */

void AddBookToFinishedUser(User *user1, Book *book)
{
    assert(user1);
    assert(book);

    if (!FindList(user1->finishedBooks, GetIdBook(book)))
    {
        printf("%s leu \"%s\"\n", user1->name, GetTitleBook(book));
        AppendList(user1->finishedBooks, book);
        return;
    }

    printf("%s já leu \"%s\"\n", user1->name, GetTitleBook(book));
}

void AddBookToWishedUser(User *user1, Book *book)
{
    assert(user1);
    assert(book);

    if (!FindList(user1->whishedBooks, GetIdBook(book)))
    {
        printf("%s deseja ler \"%s\"\n", user1->name, GetTitleBook(book));
        AppendList(user1->whishedBooks, book);
        return;
    }

    printf("%s já deseja ler \"%s\"\n", user1->name, GetTitleBook(book));
}

void AddBookToRecommendedUser(User *user1, Book *book, User *user2)
{
    assert(user1);
    assert(user2);
    assert(book);

    if (FindList(user2->recommendations, GetIdBook(book)))
    {
        printf("%s já deseja ler \"%s\", recomendação desnecessária\n", user2->name, GetTitleBook(book));
        return;
    }

    if (!FindList(user2->finishedBooks, GetIdBook(book)))
    {
        printf("%s recomenda \"%s\" para %s\n", user1->name, GetTitleBook(book), user2->name);
        AppendList(user2->recommendations, book);
        return;
    }

    printf("%s não precisa da recomendação de \"%s\" pois já leu este livro\n", user2->name, GetTitleBook(book));
}

void AcceptRecommendedBook(User *user1, Book *book, User *user2)
{
    assert(user1);
    assert(user2);
    assert(book);

    if (FindList(user1->recommendations, GetIdBook(book)))
    {
        printf("%s aceita recomendação \"%s\" de %s\n", user1->name, GetTitleBook(book), user2->name);
        AppendList(user1->whishedBooks, book);
        RemoveList(user1->recommendations, GetIdBook(book));
        return;
    }

    printf("%s não possui recomendação do livro ID %d feita por %s\n", user1->name, GetIdBook(book), user2->name);
}

void DenyRecommendedBook(User *user1, Book *book, User *user2)
{
    assert(user1);
    assert(user2);
    assert(book);

    if (FindList(user1->recommendations, GetIdBook(book)))
    {
        printf("%s rejeita recomendação \"%s\" de %s\n", user1->name, GetTitleBook(book), user2->name);
        RemoveList(user1->recommendations, GetIdBook(book));
        return;
    }

    printf("%s não possui recomendação do livro ID %d feita por %s\n", user1->name, GetIdBook(book), user2->name);
}

// corrigir depois
void PrintSharedBooksUsers(User *user1, User *user2)
{
    assert(user1);
    assert(user2);

    printf("Livros em comum entre %s e %s: ", user1->name, user2->name);

    // linha terrivelmente longa, desculpa.
    List *sharedBooks = GetCommonItemsList(user1->finishedBooks, user2->finishedBooks, IsSameIdOfBook, PrintBook, CompareBooks);

    if (IsEmptyList(sharedBooks))
        printf("Nenhum livro em comum");
    else
        PrintList(sharedBooks);

    printf("\n");

    FreeList(sharedBooks);
}

int SearchUser(User *user, int id, List *visited)
{
    assert(user);
    assert(visited);

    // Implementação do algoritimo de busca em profundidade:

    // O nó atual já foi visitado.
    if (FindList(visited, GetIdUser(user)))
        return 0;

    AppendList(visited, user);

    // Encontrou o usuário no nó atual.
    if (IsSameIdOfUser(user, id))
        return 1;

    // Inicia a busca nos filhos do nó atual:
    Cell *currentCell = GetFirstCellList(user->afinities);

    // Loop que percorre os irmaos
    while (currentCell != NULL)
    {
        User *currentUser = GetValue(currentCell);

        // Busca recursivamente até encontrar o usuário ou chegar ao fim do ramo.
        if (SearchUser(currentUser, id, visited))
            return 1;

        // Passa para o nó irmão e continua a busca.
        currentCell = GetNext(currentCell);
    }
    // Acabaram os nós irmãos

    return 0;
}

int AreRelatedUsers(User *user1, User *user2)
{
    assert(user1);
    assert(user2);

    List *visitedUsers = CreateList(PrintUser, IsSameIdOfUser);

    int result = SearchUser(user1, user2->id, visitedUsers);

    FreeList(visitedUsers);

    return result;
}