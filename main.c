#include "list.h"
#include "book.h"
#include "user.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    List *bookList = CreateList(PrintBook, IsSameIdOfBook);
    List *userList = CreateList(PrintUser, IsSameIdOfUser);
    FILE *bookFile = OpenFileToRead(BOOK_SOURCE_FILE);
    FILE *userFile = OpenFileToRead(USER_SOURCE_FILE);

    while (1)
    {
        Book *book = ReadBook(bookFile);

        if (!book)
            break;

        AppendList(bookList, book);
    }

    while (1)
    {
        User *user = ReadUser(userFile);

        if (!user)
            break;

        AppendList(userList, user);
    }

    PrintList(bookList);
    PrintList(userList);

    FreeList(bookList);
    FreeList(userList);
    return 0;
}
