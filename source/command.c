#include "command.h"

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
    User *recommendedUser = FindList(userList, idUser1);
    User *recommendindUser = FindList(userList, idUser2);

    if (!recommendindUser)
    {
        printf("Erro: Leitor recomendador com ID %d não encontrado\n", idUser2);
        return;
    }

    if (!recommendedUser)
    {
        printf("Erro: Leitor com ID %d não encontrado\n", idUser1);
        return;
    }

    AcceptRecommendedBook(recommendedUser, idBook, recommendindUser);
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
        printf("Erro: Leitor com ID %d não encontrado\n", idUser1);
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