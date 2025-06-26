/**
 * @file user.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the user struct.
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "book.h"
#include "list.h"

#define USER_SOURCE_FILE "./leitores.txt"

/**
 * @brief Opaque definition for the User structure
 */
typedef struct user User;

#include "recommendation.h"

/**
 * @brief Create a User object
 * 
 * @param id Unique identifier for the user
 * @param name Name of the user
 * @param lenPreferences Number of reading preferences
 * @param preferences Array of strings representing the user's preferred genres
 * 
 * @pre name and preferences must be valid pointers; lenPreferences must match the actual number of preferences
 * @post User allocated and initialized with the given parameters and empty lists for books, recommendations, and affinities
 * 
 * @return User* - the initialized User object
 */
User *CreateUser(int id, char *name, int lenPreferences, char **preferences);

/**
 * @brief Read and create a User object from a file
 * 
 * @param file Pointer to a FILE containing user data in the format: id;name;lenPreferences;preference1;preference2;...
 * 
 * @pre file must be a valid, open FILE pointer with properly formatted data
 * @post A new User is created and initialized with the data read from the file;
 *       returns NULL if end-of-file is reached before reading a user
 * 
 * @return User* - the initialized User object, or NULL if no more users to read
 */
User *ReadUser(FILE *file);

/**
 * @brief Compare the ID of a User object with a given ID
 * 
 * @param ptr Pointer to a User object (as void*)
 * @param args Variable argument list containing the ID to compare
 * 
 * @pre ptr must be a valid pointer to a User object; args must contain an int ID
 * @post none
 * 
 * @return int 1 if the User ID matches the given ID, 0 otherwise
 */
int CompareIdUser(void *user, va_list args);

/**
 * @brief Print detailed information about a User
 * 
 * @param ptr Pointer to a User object (as void*)
 * @param unused An unused integer parameter (for compatibility)
 * 
 * @pre ptr must be a valid pointer to a User object
 * @post User information, including finished books, wished books, recommendations, and affinities, is printed to stdout
 * 
 * @return void
 */
void PrintUser(void *user, int);

/**
 * @brief Free all memory associated with a User object
 * 
 * @param ptr Pointer to a User object (as void*)
 * 
 * @pre ptr must be a valid pointer to a User object
 * @post All memory allocated for the User and its internal structures is freed
 * 
 * @return void
 */
void FreeUser(void *user);

/**
 * @brief Retrieve the ID of a User object
 * 
 * @param ptr Pointer to a User object (as void*)
 * 
 * @pre ptr must be a valid pointer to a User object
 * @post none
 * 
 * @return int - the ID of the User
 */
int GetIdUser(void *ptr);

/**
 * @brief Retrieve the name of a User object
 * 
 * @param ptr Pointer to a User object (as void*)
 * 
 * @pre ptr must be a valid pointer to a User object
 * @post none
 * 
 * @return char* - the name of the User
 */
char *GetNameUser(void *ptr);

/**
 * @brief Check if two Users have compatible preferences
 * 
 * @param user1 Pointer to the first User object
 * @param user2 Pointer to the second User object
 * 
 * @pre user1 and user2 must be valid, initialized User pointers
 * @post none
 * 
 * @return int 1 if the users share at least one preference, 0 otherwise
 */
int AreCompatibleUsers(User *user1, User *user2);

/**
 * @brief Connect two Users by adding each other to their affinities if compatible
 * 
 * @param ptr1 Pointer to the first User object (as void*)
 * @param ptr2 Pointer to the second User object (as void*)
 * 
 * @pre ptr1 and ptr2 must be valid pointers to initialized User objects
 * @post If users are compatible, each user is added to the other's affinities list
 * 
 * @return void
 */
void ConnectUsers(void *ptr1, void *ptr2);

/**
 * @brief Add a Book to a User's finishedBooks list if not already present
 * 
 * @param user1 Pointer to the User object
 * @param book Pointer to the Book object
 * 
 * @pre user1 and book must be valid, initialized pointers
 * @post If the book was not already finished by the user, it is appended to finishedBooks and a message is printed;
 *       otherwise, a message indicating the book was already read is printed
 * 
 * @return void
 */
void AddBookToFinishedUser(User *user1, Book *book);

/**
 * @brief Add a Book to a User's wishedBooks list if not already present
 * 
 * @param user1 Pointer to the User object
 * @param book Pointer to the Book object
 * 
 * @pre user1 and book must be valid, initialized pointers
 * @post If the book was not already wished by the user, it is appended to wishedBooks and a message is printed;
 *       otherwise, a message indicating the book is already in the wished list is printed
 * 
 * @return void
 */
void AddBookToWishedUser(User *user1, Book *book);

/**
 * @brief Add a Book recommendation from one User to another if appropriate
 * 
 * @param user1 Pointer to the User making the recommendation
 * @param book Pointer to the Book being recommended
 * @param user2 Pointer to the User receiving the recommendation
 * 
 * @pre user1, user2, and book must be valid, initialized pointers
 * @post If user2 does not already wish to read or has not finished the book, a new Recommendation is created and added to user2's recommendations;
 *       otherwise, appropriate messages are printed indicating no need for recommendation
 * 
 * @return void
 */
void AddBookToRecommendedUser(User *user1, Book *book, User *user2);

/**
 * @brief Accept a recommended Book by adding it to the User's wishedBooks and removing the recommendation
 * 
 * @param user1 Pointer to the User accepting the recommendation
 * @param idBook ID of the recommended Book
 * @param user2 Pointer to the User who made the recommendation
 * 
 * @pre user1 and user2 must be valid, initialized User pointers
 * @post If the recommendation exists, the book is added to user1's wishedBooks, and the recommendation is removed and freed;
 *       otherwise, a message is printed indicating no such recommendation exists
 * 
 * @return void
 */
void AcceptRecommendedBook(User *user1, int idBook, User *user2);

/**
 * @brief Deny a recommended Book by removing the recommendation without adding the book
 * 
 * @param user1 Pointer to the User denying the recommendation
 * @param idBook ID of the recommended Book
 * @param user2 Pointer to the User who made the recommendation
 * 
 * @pre user1 and user2 must be valid, initialized User pointers
 * @post If the recommendation exists, it is removed from user1's recommendations and freed;
 *       otherwise, a message is printed indicating no such recommendation exists
 * 
 * @return void
 */
void DenyRecommendedBook(User *user1, int idBook, User *user2);

/**
 * @brief Print the list of books shared (finished) by two Users
 * 
 * @param user1 Pointer to the first User object
 * @param user2 Pointer to the second User object
 * 
 * @pre user1 and user2 must be valid, initialized User pointers
 * @post Prints the common finished books between the two users; if none, prints a message indicating so
 * 
 * @return void
 */
void PrintSharedBooksUsers(User *user1, User *user2);

/**
 * @brief Check whether two Users are related through affinities using depth-first search
 * 
 * @param user1 Pointer to the starting User
 * @param user2 Pointer to the target User
 * 
 * @pre user1 and user2 must be valid, initialized User pointers
 * @post A depth-first search is performed from user1 through affinities to determine connection to user2
 * 
 * @return int 1 if user2 is reachable from user1 through affinity connections, 0 otherwise
 */
int AreRelatedUsers(User *user1, User *user2);
