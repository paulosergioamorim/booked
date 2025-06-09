/**
 * @file book.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the book struct.
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#define BOOK_SOURCE_FILE "./livros.txt"

typedef struct book Book;

Book *CreateBook(int id, char *title, char *author, char *gender, int yearOfPublication);

int IsSameIdOfBook(void *book, int id);

Book *ReadBook(FILE *file);

void FreeBook(void *book);

void PrintBook(void *book, int);

int GetIdBook(void *ptr);

int CompareBooks(void *book1, void *book2);
