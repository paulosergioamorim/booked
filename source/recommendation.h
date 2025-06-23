#pragma once
#include "book.h"

typedef struct recommendation Recommendation;

#include "user.h"

Recommendation *CreateRecommendation(Book *book, User *recommendingUser);

Book *GetBookRecommendation(Recommendation *recommendation);

User *GetRecommendingUserRecommendation(Recommendation *recommendation);

void PrintRecommendation(void *ptr, int isLast);
