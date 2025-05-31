#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "book.h"
#include "utils.h"

struct book
{
    int id;
    char *title;
    char *author;
    char *gender;
    int yearOfPublication;
};

Book *CreateBook(int id, char *title, char *author, char *gender, int yearOfPublication)
{
    Book *book = malloc(sizeof(Book));
    assert(book);
    book->id = id;
    book->title = title;
    book->author = author;
    book->gender = gender;
    book->yearOfPublication = yearOfPublication;

    return book;
}

int IsSameIdOfBook(void *ptr, int id)
{
    Book *book = (Book *)ptr;
    assert(book);

    return book->id == id;
}

Book *ReadBook(FILE *file)
{
    int id = 0;
    char *title = malloc(MAX_LINE_LENGTH * sizeof(char));
    char *author = malloc(MAX_LINE_LENGTH * sizeof(char));
    char *gender = malloc(MAX_LINE_LENGTH * sizeof(char));
    int yearOfPublication = 0;
    if (fscanf(file, "%d;%[^;];%[^;];%[^;];%d", &id, title, author, gender, &yearOfPublication) == EOF)
        return NULL;

    return CreateBook(id, title, author, gender, yearOfPublication);
}

void FreeBook(void *ptr)
{
    Book *book = (Book *)ptr;
    assert(book);
    free(book->title);
    free(book->author);
    free(book->gender);
    free(book);
}

void PrintBook(void *ptr)
{
    Book *book = (Book *)ptr;
    assert(book);
    printf("%s\n", book->title);
}