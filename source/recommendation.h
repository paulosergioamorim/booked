/**
 * @file recommendation.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate recommendation.
 * @version 0.1
 * @date 2025-06-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "book.h"

typedef struct recommendation Recommendation;

#include "user.h"

Recommendation *CreateRecommendation(Book *book, User *recommendingUser);

Book *GetBookRecommendation(Recommendation *recommendation);

User *GetRecommendingUserRecommendation(Recommendation *recommendation);

void PrintRecommendation(void *ptr, int isLast);
