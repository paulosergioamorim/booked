#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "recommendation.h"

struct recommendation
{
    Book *book;
    User *recommendingUser;
};

Recommendation *CreateRecommendation(Book *book, User *recommendingUser)
{
    Recommendation *recommendation = malloc(sizeof(Recommendation));
    assert(recommendation);
    recommendation->book = book;
    recommendation->recommendingUser = recommendingUser;

    return recommendation;
}

Book *GetBookRecommendation(Recommendation *recommendation)
{
    assert(recommendation);
    return recommendation->book;
}

User *GetRecommendingUserRecommendation(Recommendation *recommendation)
{
    assert(recommendation);
    return recommendation->recommendingUser;
}

void PrintRecommendation(void *ptr, int isLast)
{
    Recommendation *recommendation = (Recommendation *)ptr;
    assert(recommendation);
    printf("%s", GetTitleBook(recommendation->book));

    if (!isLast)
    {
        printf(", ");
    }
}
