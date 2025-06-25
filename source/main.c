#include "list.h"
#include "book.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

#define COMMAND_SOURCE_FILE "./comandos.txt"
#define COMMAND_PARAMS List *userList, List *bookList, int idUser1, int idBook, int idUser2
#define __UNIQUE_NOT_NULL(type, val, list, id)                 \
    type val = FindList(list, id);                             \
    if (!val)                                                  \
    {                                                          \
        printf("Erro: Leitor com ID %d não encontrado\n", id); \
        return;                                                \
    }
#define UNIQUE_USER_NOT_NULL(id) __UNIQUE_NOT_NULL(User *, user, userList, id)
#define BOTH_USERS_NOT_NULL(id1, id2)               \
    __UNIQUE_NOT_NULL(User *, user1, userList, id1) \
    __UNIQUE_NOT_NULL(User *, user2, userList, id2)
#define UNIQUE_BOOK_NOT_NULL(id) __UNIQUE_NOT_NULL(Book *, book, bookList, id)
#define __READ_FILE(type, func, file, list) \
    while (1)                               \
    {                                       \
        type val = func(file);              \
        if (!val)                           \
            break;                          \
        AppendList(list, val);              \
    }                                       \
    fclose(file);
#define READ_BOOK_AND_USER_FILES                      \
    __READ_FILE(Book *, ReadBook, bookFile, bookList) \
    __READ_FILE(User *, ReadUser, userFile, userList)

typedef void (*command_fn)(COMMAND_PARAMS);

int ExecuteCommand(FILE *commandFile, command_fn commands[], List *userList, List *bookList);

void format_AddBookToFinishedUser(COMMAND_PARAMS);

void format_AddBookToWishedUser(COMMAND_PARAMS);

void format_AddBookToRecommendedUser(COMMAND_PARAMS);

void format_AcceptRecommendedBook(COMMAND_PARAMS);

void format_DenyRecommendedBook(COMMAND_PARAMS);

void format_PrintSharedBooksUsers(COMMAND_PARAMS);

void format_AreRelatedUsers(COMMAND_PARAMS);

void format_PrintUsers(COMMAND_PARAMS);

int main(int argc, char const *argv[])
{
    List *bookList = CreateList(PrintBook, CompareIdBook);
    List *userList = CreateList(PrintUser, CompareIdUser);

    FILE *bookFile = NULL;
    if ((bookFile = OpenFileToRead(BOOK_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'livros.txt'\n");
        exit(1);
    }

    FILE *userFile = NULL;
    if ((userFile = OpenFileToRead(USER_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'leitores.txt'\n");
        exit(1);
    }

    FILE *commandFile = NULL;
    if ((commandFile = OpenFileToRead(COMMAND_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'comandos.txt'\n");
        exit(1);
    }

    command_fn commands[] = {
        format_AddBookToFinishedUser,    // 1
        format_AddBookToWishedUser,      // 2
        format_AddBookToRecommendedUser, // 3
        format_AcceptRecommendedBook,    // 4
        format_DenyRecommendedBook,      // 5
        format_PrintSharedBooksUsers,    // 6
        format_AreRelatedUsers,          // 7
        format_PrintUsers                // 8
    };

    // Removebdo as linhas de cabeçalho:
    fscanf(bookFile, "%*[^\n]\n");
    fscanf(commandFile, "%*[^\n]\n");
    fscanf(userFile, "%*[^\n]\n");

    READ_BOOK_AND_USER_FILES;

    IterList(userList, ConnectUsers);

    while (ExecuteCommand(commandFile, commands, userList, bookList))
        ;

    fclose(commandFile);

    ForEach(bookList, FreeBook);
    ForEach(userList, FreeUser);

    FreeList(bookList);
    FreeList(userList);
    return 0;
}

int ExecuteCommand(FILE *commandFile, command_fn commands[], List *userList, List *bookList)
{
    int op = 0;
    int idUser1 = 0;
    int idBook = 0;
    int idUser2 = 0;

    if (fscanf(commandFile, "%d;%d;%d;%d", &op, &idUser1, &idBook, &idUser2) == EOF)
        return 0;

    if (op < 1 || op > 8)
    {
        printf("Erro: Comando %d não reconhecido\n", op);
        return 1;
    }

    commands[op - 1](userList, bookList, idUser1, idBook, idUser2);
    return 1;
}

void format_AddBookToFinishedUser(COMMAND_PARAMS)
{
    UNIQUE_USER_NOT_NULL(idUser1);
    UNIQUE_BOOK_NOT_NULL(idBook);
    AddBookToFinishedUser(user, book);
}

void format_AddBookToWishedUser(COMMAND_PARAMS)
{
    UNIQUE_USER_NOT_NULL(idUser1);
    UNIQUE_BOOK_NOT_NULL(idBook);
    AddBookToWishedUser(user, book);
}

void format_AddBookToRecommendedUser(COMMAND_PARAMS)
{
    User *recommendindUser = FindList(userList, idUser1);
    User *recommendedUser = FindList(userList, idUser2);
    UNIQUE_BOOK_NOT_NULL(idBook);

    if (!recommendindUser)
    {
        printf("Erro: Leitor recomendador com ID %d não encontrado\n", idUser1);
        return;
    }

    if (!recommendedUser)
    {
        printf("Erro: Leitor destinatário com ID %d não encontrado\n", idUser2);
        return;
    }

    if (recommendindUser == recommendedUser)
    {
        printf("%s não pode recomendar livros para si mesmo\n", GetNameUser(recommendindUser));
        return;
    }

    AddBookToRecommendedUser(recommendindUser, book, recommendedUser);
}

void format_AcceptRecommendedBook(COMMAND_PARAMS)
{
    BOTH_USERS_NOT_NULL(idUser1, idUser2)
    AcceptRecommendedBook(user1, idBook, user2);
}

void format_DenyRecommendedBook(COMMAND_PARAMS)
{
    User *recommendedUser = FindList(userList, idUser1);
    User *recommendindUser = FindList(userList, idUser2);

    if (!recommendindUser)
    {
        printf("Erro: Leitor recomendador com ID %d não encontrado\n", idUser2);
        return;
    }

    if (!recommendedUser)
    {
        printf("Erro: Leitor destinatário com ID %d não encontrado\n", idUser1);
        return;
    }

    DenyRecommendedBook(recommendedUser, idBook, recommendindUser);
}

void format_PrintSharedBooksUsers(COMMAND_PARAMS)
{
    BOTH_USERS_NOT_NULL(idUser1, idUser2);
    PrintSharedBooksUsers(user1, user2);
}

void format_AreRelatedUsers(COMMAND_PARAMS)
{
    BOTH_USERS_NOT_NULL(idUser1, idUser2);

    if (AreRelatedUsers(user1, user2))
        printf("Existe afinidade entre %s e %s\n", GetNameUser(user1), GetNameUser(user2));
    else
        printf("Não existe afinidade entre %s e %s\n", GetNameUser(user1), GetNameUser(user2));
}

void format_PrintUsers(COMMAND_PARAMS)
{
    printf("Imprime toda a BookED\n\n");
    PrintList(userList);
}