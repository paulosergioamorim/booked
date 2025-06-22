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

/**
 * @brief struct that defines a book.
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
 * @brief Compare the book's id with the given id
 * 
 * @param ptr pointer to the book object
 * @param id 
 * 
 * @pre the book exists
 * @post the book data remains unchanged
 * 
 * @return int - 1 if equal, 0 otherwise
 */
int IsSameIdOfBook(void *ptr, int id);

/**
 * @brief Read the data to alocate the book from the file
 * 
 * @param file file with the data
 *
 * @pre the file exists and is pointing to a line containing the correct data 
 * @post the book object is alocated and initialized
 * 
 * @return Book* - the initialized book object
 */
Book *ReadBook(FILE *file);

/**
 * @brief Frees the alocated memory
 * 
 * @param book 
 * 
 * @pre the book exists
 * @post the alocated memory (book, title, author, gender) is freed
 */
void FreeBook(void *book);

/**
 * @brief Print the formated book data;
 * 
 * @param book 
 * @param isLast indicates whether it is the last in the list
 * 
 * @pre the book exists
 * @post the book data remains unchanged
 */
void PrintBook(void *book, int);

/**
 * @brief Get the Id of the Book object
 * 
 * @param ptr pointer to the book object

 * @pre the book exists
 * @post the book data remains unchanged
 * 
 * @return int - the book id
 */
int GetIdBook(void *ptr);

/**
 * @brief check if two books are the same
 * 
 * @param book1 
 * @param book2 
 * 
 * @pre both book exists
 * @post the books data remain unchanged
 * 
 * @return int - 1 if equal, 0 otherwise
 */
int CompareBooks(void *book1, void *book2);
