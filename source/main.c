#include "list.h"
#include "book.h"
#include "user.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    List *bookList = CreateList(PrintBook, CompareIdBook);
    List *userList = CreateList(PrintUser, CompareIdUser);
    FILE *bookFile = NULL;
    FILE *userFile = NULL;
    FILE *commandFile = NULL;

    if ((bookFile = OpenFileToRead(BOOK_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'livros.txt'\n");
        exit(1);
    }

    if ((userFile = OpenFileToRead(USER_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'leitores.txt'\n");
        exit(1);
    }

    if ((commandFile = OpenFileToRead(COMMAND_SOURCE_FILE)) == NULL)
    {
        printf("[ERRO] - Nao foi possivel abrir o arquivo 'comandos.txt'\n");
        exit(1);
    }

    // Removendo as linhas de cabeçalho:
    fscanf(bookFile, "%*[^\n]\n");
    fscanf(commandFile, "%*[^\n]\n");
    fscanf(userFile, "%*[^\n]\n");

    Book *book = NULL;
    User *user = NULL;

    while ((book = ReadBook(bookFile)))
    {
        AppendList(bookList, book);
    }

    fclose(bookFile);

    while ((user = ReadUser(userFile)))
    {
        AppendList(userList, user);
    }

    fclose(userFile);
    IterList(userList, ConnectUsers);

    while (ExecuteCommand(commandFile, userList, bookList))
        ;

    fclose(commandFile);

    ForEach(bookList, FreeBook);
    ForEach(userList, FreeUser);

    FreeList(bookList);
    FreeList(userList);

    return 0;
}
