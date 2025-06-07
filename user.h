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

typedef struct user User;

User *CreateUser(int id, char *name, int lenPreferences, char **preferences);

User *ReadUser(FILE *file);

int IsSameIdOfUser(void *user, int id);

void PrintUser(void *user, int);

void FreeUser(void *user);

int GetIdUser(void *ptr);

void ConnectUsers(void *ptr1, void *ptr2);

void AddBookToFinishedUser(User *user1, Book *book, User *user2);

void AddBookToWishedUser(User *user1, Book *book, User *user2);

void AddBookToRecommendedUser(User *user1, Book *book, User *user2);

void AcceptRecommendedBook(User *user1, Book *book, User *user2);

void DenyRecommendedBook(User *user1, Book *book, User *user2);

void PrintSharedBooksUsers(User* user1, User* user2);