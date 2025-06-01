/**
 * @file user.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (email do paulo, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the user struct.
 * @version 0.1
 * @date 2025-05-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "book.h"

#define USER_SOURCE_FILE "./leitores.txt"

typedef struct user User;

User *CreateUser(int id, char *name, int lenPreferences, char **preferences);

User *ReadUser(FILE *file);

int IsSameIdOfUser(void *user, int id);

void PrintUser(void *user);

void FreeUser(void *user);

int GetIdUser(void *ptr);