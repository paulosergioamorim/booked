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

/**
 * @brief Opaque definition for the Recommendation structure
 */
typedef struct recommendation Recommendation;

#include "user.h"

/**
 * @brief Create a Recommendation object
 * 
 * @param book Pointer to the Book being recommended
 * @param recommendingUser Pointer to the User who is recommending the book
 * 
 * @pre book and recommendingUser must be valid, initialized pointers
 * @post Recommendation allocated and initialized with the given Book and User
 * 
 * @return Recommendation* - the initialized Recommendation object
 */
Recommendation *CreateRecommendation(Book *book, User *recommendingUser);

/**
 * @brief Retrieve the Book from a Recommendation
 * 
 * @param recommendation Pointer to the Recommendation object
 * 
 * @pre recommendation must be a valid, initialized Recommendation pointer
 * @post none
 * 
 * @return Book* - pointer to the recommended Book
 */
Book *GetBookRecommendation(Recommendation *recommendation);

/**
 * @brief Retrieve the User who made the Recommendation
 * 
 * @param recommendation Pointer to the Recommendation object
 * 
 * @pre recommendation must be a valid, initialized Recommendation pointer
 * @post none
 * 
 * @return User* - pointer to the User who recommended the Book
 */
User *GetRecommendingUserRecommendation(Recommendation *recommendation);

/**
 * @brief Print the title of the Book in a Recommendation
 * 
 * @param ptr Pointer to a Recommendation object (as void*)
 * @param isLast Integer flag indicating if this is the last element to be printed
 * 
 * @pre ptr must be a valid pointer to a Recommendation object
 * @post The title of the recommended Book is printed to stdout; 
 *       if isLast is 0, a comma and space are printed after the title
 * 
 * @return void
 */
void PrintRecommendation(void *ptr, int isLast);

/**
 * @brief Compare the Book and User IDs in a Recommendation
 * 
 * @param ptr Pointer to a Recommendation object (as void*)
 * @param args Variable argument list containing the Book ID and User ID
 * 
 * @pre ptr must be a valid pointer to a Recommendation object; 
 *      args must contain two integers: the Book ID and the User ID
 * @post none
 * 
 * @return int 1 if both IDs match the Recommendation, 0 otherwise
 */
int CompareIdRecommendation(void *ptr, va_list args);
