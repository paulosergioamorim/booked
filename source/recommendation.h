#pragma once
#include "book.h"
#include "user.h"

typedef struct recommendation Recommendation;

Recommendation *CreateRecommendation(Book *book, User *recommendingUser);

Book *GetBookRecommendation(Recommendation *recommendation);

User *GetRecommendingUserRecommendation(Recommendation *recommendation);

void PrintRecommendation(void *ptr, int isLast);

void FreeRecommendation(Recommendation *recommendation);
