/**
 * @file recommendation.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Implementation file for functions that manipulate recommendation.
 * @version 0.1
 * @date 2025-06-25
 *
 * @copyright Copyright (c) 2025
 *
 */

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
