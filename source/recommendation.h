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
#include "user.h"

/**
 * @brief Tipo opaco que representa uma recomendação de livro.
 */
typedef struct recommendation Recommendation;

/**
 * @brief Cria uma nova recomendação.
 *
 * @param book             Ponteiro para o livro recomendado.
 * @param recommendingUser Ponteiro para o usuário que fez a recomendação.
 * @return Ponteiro para a Recommendation criada.
 */
Recommendation *CreateRecommendation(Book *book, User *recommendingUser);

/**
 * @brief Obtém o livro associado a uma recomendação.
 *
 * @param recommendation Ponteiro para Recommendation.
 * @return Ponteiro para o Book recomendado.
 */
Book *GetBookRecommendation(Recommendation *recommendation);

/**
 * @brief Obtém o usuário que fez a recomendação.
 *
 * @param recommendation Ponteiro para Recommendation.
 * @return Ponteiro para o User recomendador.
 */
User *GetRecommendingUserRecommendation(Recommendation *recommendation);

/**
 * @brief Imprime uma recomendação formatada.
 *
 * @param ptr    Ponteiro para Recommendation.
 * @param isLast Indicador se é o último item na lista (para ajustar formatação).
 */
void PrintRecommendation(void *ptr, int isLast);

/**
 * @brief Compara uma recomendação por ID do livro.
 *
 * @param ptr  Ponteiro para Recommendation.
 * @param args va_list contendo o ID do livro e o ID do usuário a comparar.
 * @return !=0 se o ID coincidir, 0 caso contrário.
 */
int CompareIdRecommendation(void *ptr, va_list args);
