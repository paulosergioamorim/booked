#include "list.h"
#include "book.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

#define COMMAND_SOURCE_FILE "./comandos.txt"

typedef void (*command_fn)(User *user1, Book *book, User *user2);

int ExecuteCommand(FILE *commandFile, command_fn commands[], List *userList, List *bookList);

void format_PrintSharedBooksUsers(User *user1, Book *book, User *user2);

void format_AreRelatedUsers(User *user1, Book *book, User *user2);

int main(int argc, char const *argv[])
{
    List *bookList = CreateList(PrintBook, IsSameIdOfBook);
    List *userList = CreateList(PrintUser, IsSameIdOfUser);

    FILE *bookFile = NULL;
    if ((bookFile =  OpenFileToRead(BOOK_SOURCE_FILE)) == NULL)
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
    
    FILE* commandFile = NULL;
    if ((commandFile = OpenFileToRead(COMMAND_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'comandos.txt'\n");
        exit(1);
    }

    command_fn commands[] = {
        AddBookToFinishedUser,
        AddBookToWishedUser,
        AddBookToFinishedUser,
        AddBookToRecommendedUser,
        AcceptRecommendedBook,
        format_PrintSharedBooksUsers,
        format_AreRelatedUsers,
        DenyRecommendedBook
    };

    // Removebdo as linhas de cabeçalho:
    fscanf(bookFile, "%*[^\n]\n");
    fscanf(commandFile, "%*[^\n]\n");
    fscanf(userFile, "%*[^\n]\n");

    while (1)
    {
        Book *book = ReadBook(bookFile);

        if (!book)
            break;

        AppendList(bookList, book);
    }

    fclose(bookFile);

    while (1)
    {
        User *user = ReadUser(userFile);

        if (!user)
            break;

        AppendList(userList, user);
    }

    IterList(userList, ConnectUsers);

    while (ExecuteCommand(commandFile, commands, userList, bookList))
    {
    }

    fclose(commandFile);
    fclose(userFile);

    DestroyItemsList(bookList, GetIdBook, FreeBook);
    DestroyItemsList(userList, GetIdUser, FreeUser);

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

    if (op == 8)
    {
        PrintList(userList);
        return 1;
    }

    User *user1 = FindList(userList, idUser1);
    Book *book = FindList(bookList, idBook);
    User *user2 = FindList(userList, idUser2);

    // if (op > 6)
    // {
    //     return 1;
    // }

    commands[op - 1](user1, book, user2);
    return 1;
}

void format_PrintSharedBooksUsers(User *user1, Book *book, User *user2) {
    PrintSharedBooksUsers(user1, user2);
}

void format_AreRelatedUsers(User *user1, Book *book, User *user2) {
    if (AreRelatedUsers(user1, user2))
        printf("Existe "); 
    else
        printf("Nao existe ");

    printf("afinidade entre %s e %s.\n", GetNameUser(user1), GetNameUser(user2));
}