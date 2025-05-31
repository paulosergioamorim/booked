#pragma once

#include "book.h"

#define USER_SOURCE_FILE "./leitores.txt"

typedef struct user User;

User *CreateUser(int id, char *name, int lenPreferences, char **preferences);

User *ReadUser(FILE *file);

int IsSameIdOfUser(void *user, int id);

void PrintUser(void *user);

void FreeUser(void *user);