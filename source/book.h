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

/**
 * @def BOOK_SOURCE_FILE
 * @brief Caminho padrão para o arquivo de livros.
 *
 * Usado em main.c para abrir o arquivo de livros:
 * @code
 * FILE *bookF = OpenFileToRead(BOOK_SOURCE_FILE);
 * @endcode
 */
#define BOOK_SOURCE_FILE "./livros.txt"

/**
 * @brief Tipo opaco que representa um livro.
 */
typedef struct book Book;

/**
 * @brief Create a Book object
 * 
 * @param id 
 * @param title 
 * @param author 
 * @param gender 
 * @param yearOfPublication 
 * 
 * @pre none
 * @post Book alocated and initialized with the given parameters
 * 
 * @return Book* - the initialized Book object
*/
Book *CreateBook(int id, char *title, char *author, char *gender, int yearOfPublication);

/**
 * @brief Compara o ID de um livro com uma chave passada via va_list.
 *
 * @param book Ponteiro para Book.
 * @param args va_list contendo um inteiro representando o ID.
 * @return !=0 se o ID coincidir, 0 caso contrário.
 */
int CompareIdBook(void *book, va_list args);

/**
 * @brief Lê um livro de um arquivo de texto.
 *
 * @param file Ponteiro para arquivo FILE aberto em modo leitura.
 * @return Ponteiro para Book lido, ou NULL se EOF.
 */
Book *ReadBook(FILE *file);

/**
 * @brief Libera a memória associada a um Book.
 *
 * @param book Ponteiro para Book a ser liberado.
 */
void FreeBook(void *book);

/**
 * @brief Imprime as informações de um livro.
 *
 * @param book   Ponteiro para Book.
 * @param indent Nível de indentação (em espaços) para impressão formatada.
 */
void PrintBook(void *book, int indent);

/**
 * @brief Obtém o ID de um livro.
 *
 * @param ptr Ponteiro genérico para Book.
 * @return ID do livro.
 */
int GetIdBook(void *ptr);

/**
 * @brief Compara dois livros pelo ID.
 *
 * @param book1 Ponteiro para o primeiro Book.
 * @param book2 Ponteiro para o segundo Book.
 * @return !=0 se os IDs coincidirem, 0 caso contrário.
 */
int CompareBooks(void *book1, void *book2);

/**
 * @brief Obtém o título de um livro.
 *
 * @param book Ponteiro para Book.
 * @return Ponteiro para string contendo o título.
 */
char *GetTitleBook(Book *book);
