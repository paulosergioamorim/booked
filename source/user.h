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

/**
 * @def USER_SOURCE_FILE
 * @brief Caminho padrão para o arquivo de usuários.
 *
 * Usado em main.c para abrir o arquivo de leitores:
 * @code
 * FILE *userF = OpenFileToRead(USER_SOURCE_FILE);
 * @endcode
 */
#define USER_SOURCE_FILE "./leitores.txt"

/**
 * @brief Tipo opaco que representa um usuário.
 */
typedef struct user User;

/**
 * @brief Cria um novo usuário.
 *
 * Aloca e inicializa um objeto User com ID, nome e preferências.
 *
 * @param id              Identificador único do usuário.
 * @param name            Nome completo do usuário (string NUL-terminated).
 * @param lenPreferences  Quantidade de preferências em @p preferences.
 * @param preferences     Vetor de strings com preferências literárias.
 * @return Ponteiro para o novo User, ou NULL em falha de alocação.
 */
User *CreateUser(int id,
                 char *name,
                 int lenPreferences,
                 char **preferences);

/**
 * @brief Lê um usuário de um arquivo de texto.
 *
 * Extrai campos formatados do arquivo e cria um User correspondente.
 * Deve ser chamado após posicionar o cursor do arquivo após o cabeçalho.
 *
 * @param file Ponteiro para FILE aberto em modo leitura.
 * @return Ponteiro para o User lido, ou NULL se EOF for atingido.
 */
User *ReadUser(FILE *file);

/**
 * @brief Compara o ID interno de um User com chave variádica.
 *
 * Extrai um inteiro de @p args e retorna não-zero se corresponder
 * ao ID do usuário.
 *
 * @param user  Ponteiro genérico para User.
 * @param args  va_list contendo um inteiro esperado como ID.
 * @return !=0 se IDs coincidirem, 0 caso contrário.
 */
int CompareIdUser(void *user, va_list args);

/**
 * @brief Imprime informações de um usuário.
 *
 * Exibe ID, nome e listas de livros (lidos, desejados, recomendados,
 * afinidades) com indentação opcional.
 *
 * @param userPtr Ponteiro genérico para User.
 * @param indent  Nível de indentação (número de espaços).
 */
void PrintUser(void *userPtr, int indent);

/**
 * @brief Libera toda a memória associada a um User.
 *
 * Desaloca listas internas, strings e a própria estrutura.
 *
 * @param userPtr Ponteiro genérico para User.
 */
void FreeUser(void *userPtr);

/**
 * @brief Obtém o ID de um usuário.
 *
 * @param ptr Ponteiro genérico para User.
 * @return Identificador numérico do usuário.
 */
int GetIdUser(void *ptr);

/**
 * @brief Obtém o nome de um usuário.
 *
 * @param ptr Ponteiro genérico para User.
 * @return Ponteiro para string contendo o nome do usuário.
 */
char *GetNameUser(void *ptr);

/**
 * @brief Registra afinidade entre dois usuários.
 *
 * Conecta internamente @p ptr1 e @p ptr2 para indicar
 * afinidade mútua em preferências literárias.
 *
 * @param ptr1 Ponteiro genérico para o primeiro User.
 * @param ptr2 Ponteiro genérico para o segundo User.
 */
void ConnectUsers(void *ptr1, void *ptr2);

/**
 * @brief Marca um livro como lido por um usuário.
 *
 * Adiciona @p book à lista de livros finalizados de @p user1.
 *
 * @param user1 Ponteiro para User que leu o livro.
 * @param book  Ponteiro para Book lido.
 */
void AddBookToFinishedUser(User *user1, Book *book);

/**
 * @brief Adiciona um livro à lista de desejos de um usuário.
 *
 * @param user1 Ponteiro para User que deseja o livro.
 * @param book  Ponteiro para Book desejado.
 */
void AddBookToWishedUser(User *user1, Book *book);

/**
 * @brief Registra recomendação de livro entre usuários.
 *
 * @param user1 Ponteiro para User que recomenda.
 * @param book  Ponteiro para Book recomendado.
 * @param user2 Ponteiro para User que recebe a recomendação.
 */
void AddBookToRecommendedUser(User *user1,
                              Book *book,
                              User *user2);

/**
 * @brief Aceita recomendação de livro pendente.
 *
 * @param user1   Ponteiro para User que aceita a recomendação.
 * @param idBook  ID do Book aceito.
 * @param user2   Ponteiro para User que fez a recomendação.
 */
void AcceptRecommendedBook(User *user1,
                           int idBook,
                           User *user2);

/**
 * @brief Nega recomendação de livro pendente.
 *
 * @param user1   Ponteiro para User que nega a recomendação.
 * @param idBook  ID do Book negado.
 * @param user2   Ponteiro para User que fez a recomendação.
 */
void DenyRecommendedBook(User *user1,
                         int idBook,
                         User *user2);

/**
 * @brief Exibe livros compartilhados entre dois usuários.
 *
 * @param user1 Ponteiro para o primeiro User.
 * @param user2 Ponteiro para o segundo User.
 */
void PrintSharedBooksUsers(User *user1, User *user2);

/**
 * @brief Verifica se dois usuários possuem afinidade.
 *
 * @param user1 Ponteiro para o primeiro User.
 * @param user2 Ponteiro para o segundo User.
 * @return !=0 se existe afinidade, 0 caso contrário.
 */
int AreRelatedUsers(User *user1, User *user2);