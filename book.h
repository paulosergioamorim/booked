#pragma once

#define BOOK_SOURCE_FILE "./livros.txt"

typedef struct book Book;

Book *CreateBook(int id, char *title, char *author, char *gender, int yearOfPublication);

int IsSameIdOfBook(void *book, int id);

Book *ReadBook(FILE *file);

void FreeBook(void *book);

void PrintBook(void *book);
