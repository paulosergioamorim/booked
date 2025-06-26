#pragma once

#include "list.h"
#include "book.h"
#include "user.h"

/**
 * @def COMMAND_SOURCE_FILE
 * @brief Caminho padrão para o arquivo de comandos.
 *
 * Usado em main.c para abrir o arquivo de comandos:
 * @code
 * FILE *cmd = fopen(COMMAND_SOURCE_FILE, "r");
 * @endcode
 */
#define COMMAND_SOURCE_FILE "./comandos.txt"

/**
 * @def COMMAND_PARAMS
 * @brief Assinatura padrão para funções de formatação de comandos.
 *
 * Deve ser usada em todos os protótipos de `format_*`, ex:
 * @code
 * void format_AddBookToFinishedUser(COMMAND_PARAMS);
 * @endcode
 *
 * Expande para:
 * @code
 * List *userList,
 * List *bookList,
 * int   idUser1,
 * int   idBook,
 * int   idUser2
 * @endcode
 */
#define COMMAND_PARAMS  \
    List *userList,     \
        List *bookList, \
        int idUser1,    \
        int idBook,     \
        int idUser2

/**
 * @def __UNIQUE_NOT_NULL(type, var, name, list, id)
 * @brief Macro de baixo nível para buscar e validar um ponteiro em uma lista.
 *
 * - Chama:
 *   @code
 *   var = FindList(list, id);
 *   @endcode
 * - Se o retorno for NULL, imprime:
 *   @verbatim
 *   Erro: <name> com ID <id> não encontrado
 *   @endverbatim
 *   e faz `return;` na função chamadora.
 *
 * @param type   Tipo do ponteiro a ser buscado (por ex. User * ou Book *).
 * @param var    Nome da variável local que receberá o resultado de FindList.
 * @param name   String descritiva (ex.: "Leitor" ou "Livro") usada na mensagem de erro.
 * @param list   Ponteiro para a lista onde se busca (userList ou bookList).
 * @param id     Identificador numérico usado como chave de busca.
 */
#define __UNIQUE_NOT_NULL(type, var, name, list, id)  \
    type var = FindList(list, id);                    \
    if (!var)                                         \
    {                                                 \
        printf("Erro: %s com ID %d não encontrado\n", \
               name, id);                             \
        return;                                       \
    }

/**
 * @def UNIQUE_USER_NOT_NULL(id)
 * @brief Busca um User* em userList pelo ID e valida não-NULL.
 *
 * Equivalente a:
 * @code
 * User *user = FindList(userList, id);
 * if (!user) {
 *     printf("Erro: Leitor com ID %d não encontrado\n", id);
 *     return;
 * }
 * @endcode
 *
 * @param id  ID do leitor a procurar.
 */
#define UNIQUE_USER_NOT_NULL(id) \
    __UNIQUE_NOT_NULL(User *, user, "Leitor", userList, id)

/**
 * @def BOTH_USERS_NOT_NULL(id1, id2)
 * @brief Valida dois leitores distintos em sequência.
 *
 * Expande para duas chamadas de UNIQUE_USER_NOT_NULL, criando localmente:
 *   User *user1 = FindList(userList, id1);
 *   User *user2 = FindList(userList, id2);
 *
 * Se qualquer uma falhar, imprime a mensagem de erro e retorna.
 *
 * @param id1  ID do primeiro leitor (por ex. destinatário ou aceitante).
 * @param id2  ID do segundo leitor (por ex. recomendador).
 */
#define BOTH_USERS_NOT_NULL(id1, id2)                         \
    __UNIQUE_NOT_NULL(User *, user1, "Leitor", userList, id1) \
    __UNIQUE_NOT_NULL(User *, user2, "Leitor", userList, id2)

/**
 * @def UNIQUE_BOOK_NOT_NULL(id)
 * @brief Busca um Book* em bookList pelo ID e valida não-NULL.
 *
 * Equivalente a:
 * @code
 * Book *book = FindList(bookList, id);
 * if (!book) {
 *     printf("Erro: Livro com ID %d não encontrado\n", id);
 *     return;
 * }
 * @endcode
 *
 * @param id  ID do livro a procurar.
 */
#define UNIQUE_BOOK_NOT_NULL(id) \
    __UNIQUE_NOT_NULL(Book *, book, "Livro", bookList, id)

/**
 * @typedef command_fn
 * @brief Define o tipo de função para manipulação de comandos lidos de arquivo.
 *
 * Uma função desse tipo recebe:
 *   - @p userList: lista de todos os usuários cadastrados.
 *   - @p bookList: lista de todos os livros cadastrados.
 *   - @p idUser1: ID do usuário principal (quem inicia a ação).
 *   - @p idBook:   ID do livro alvo da ação (quando aplicável).
 *   - @p idUser2: ID do segundo usuário envolvido (quando aplicável).
 */
typedef void (*command_fn)(COMMAND_PARAMS);

/**
 * @brief Lê e executa um comando do arquivo de comandos.
 *
 * Cada linha do arquivo deve ter o formato:
 *   op;idUser1;idBook;idUser2
 * onde:
 *   - @p op é o código da operação (1 a 8),
 *   - @p idUser1 e @p idUser2 são IDs de usuários (ou 0 se não usados),
 *   - @p idBook é o ID de um livro (ou 0 se não usado).
 *
 * A função:
 *   1. Lê quatro inteiros do @p commandFile.
 *   2. Se atingir EOF, retorna 0 para parar o processamento.
 *   3. Valida @p op dentro do intervalo de comandos disponíveis
 *      e chama o handler correspondente.
 *   4. Retorna 1 para continuar processando o próximo comando.
 *
 * @param commandFile  Ponteiro para o arquivo de comandos (já aberto e sem cabeçalho).
 * @param userList     Lista de todos os usuários do sistema.
 * @param bookList     Lista de todos os livros do sistema.
 * @return             0 se EOF for alcançado (encerra loop), 1 caso contrário.
 */
int ExecuteCommand(FILE *commandFile,
                   List *userList,
                   List *bookList);

/**
 * @brief Comando 1: marca um livro como já lido por um usuário.
 *
 * Valida existência de @p idUser1 e @p idBook, e então chama:
 *   AddBookToFinishedUser(user, book);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Lista de livros.
 * @param idUser1    ID do usuário que terminou de ler o livro.
 * @param idBook     ID do livro concluído.
 * @param idUser2    Ignorado (deve ser 0).
 */
void format_AddBookToFinishedUser(COMMAND_PARAMS);

/**
 * @brief Comando 2: adiciona um livro à lista de desejos de um usuário.
 *
 * Valida existência de @p idUser1 e @p idBook, e então chama:
 *   AddBookToWishedUser(user, book);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Lista de livros.
 * @param idUser1    ID do usuário que deseja o livro.
 * @param idBook     ID do livro desejado.
 * @param idUser2    Ignorado (deve ser 0).
 */
void format_AddBookToWishedUser(COMMAND_PARAMS);

/**
 * @brief Comando 3: recomenda um livro de um usuário para outro.
 *
 * Valida existência de:
 *   - @p idUser1 (recomendador),
 *   - @p idUser2 (destinatário),
 *   - @p idBook (livro recomendado),
 * e então chama:
 *   AddBookToRecommendedUser(recommendendor, book, destinatario);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Lista de livros.
 * @param idUser1    ID do usuário que faz a recomendação.
 * @param idBook     ID do livro recomendado.
 * @param idUser2    ID do usuário que receberá a recomendação.
 */
void format_AddBookToRecommendedUser(COMMAND_PARAMS);

/**
 * @brief Comando 4: aceita uma recomendação pendente.
 *
 * Valida existência de:
 *   - @p idUser1 (destinatário que aceita),
 *   - @p idUser2 (recomendador),
 *   - @p idBook (livro recomendado),
 * e então chama:
 *   AcceptRecommendedBook(destinatario, book, recomendador);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Lista de livros.
 * @param idUser1    ID do usuário que aceita a recomendação.
 * @param idBook     ID do livro aceito.
 * @param idUser2    ID do usuário que fez a recomendação.
 */
void format_AcceptRecommendedBook(COMMAND_PARAMS);

/**
 * @brief Comando 5: nega uma recomendação pendente.
 *
 * Valida existência de:
 *   - @p idUser1 (destinatário que nega),
 *   - @p idUser2 (recomendador),
 *   - @p idBook (livro recomendado),
 * e então chama:
 *   DenyRecommendedBook(destinatario, book, recomendador);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Lista de livros.
 * @param idUser1    ID do usuário que nega a recomendação.
 * @param idBook     ID do livro negado.
 * @param idUser2    ID do usuário que fez a recomendação.
 */
void format_DenyRecommendedBook(COMMAND_PARAMS);

/**
 * @brief Comando 6: imprime livros em comum entre dois usuários.
 *
 * Valida existência de @p idUser1 e @p idUser2 e chama:
 *   PrintSharedBooksUsers(user1, user2);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Ignorada.
 * @param idUser1    ID do primeiro usuário.
 * @param idBook     Ignorado (deve ser 0).
 * @param idUser2    ID do segundo usuário.
 */
void format_PrintSharedBooksUsers(COMMAND_PARAMS);

/**
 * @brief Comando 7: verifica afinidade entre dois usuários.
 *
 * Valida existência de @p idUser1 e @p idUser2 e imprime:
 *   “Existe afinidade entre …” ou “Não existe afinidade entre …”
 * com base em AreRelatedUsers(user1, user2).
 *
 * @param userList   Lista de usuários.
 * @param bookList   Ignorada.
 * @param idUser1    ID do primeiro usuário.
 * @param idBook     Ignorado (deve ser 0).
 * @param idUser2    ID do segundo usuário.
 */
void format_AreRelatedUsers(COMMAND_PARAMS);

/**
 * @brief Comando 8: imprime todos os usuários e seus dados.
 *
 * Ignora os parâmetros numéricos e chama:
 *   PrintList(userList);
 *
 * @param userList   Lista de usuários.
 * @param bookList   Ignorada.
 * @param idUser1    Ignorado (0).
 * @param idBook     Ignorado (0).
 * @param idUser2    Ignorado (0).
 */
void format_PrintUsers(COMMAND_PARAMS);
