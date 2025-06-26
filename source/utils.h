/**
 * @file utils.c
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <stdio.h>

/**
 * @brief Tamanho máximo de buffer para leitura de linha.
 */
#define MAX_LINE_LENGTH 256

/**
 * @brief Abre um arquivo em modo leitura.
 *
 * Tenta abrir o arquivo especificado em modo "r". Em caso de falha,
 * imprime mensagem de erro e retorna NULL.
 *
 * @param source Caminho para o arquivo a ser lido.
 * @return Ponteiro para FILE em modo leitura, ou NULL em erro.
 */
FILE *OpenFileToRead(char *source);

/**
 * @brief Função genérica para liberar memória de um elemento.
 *
 * @param ptr Ponteiro para o dado a ser liberado.
 */
typedef void (*free_fn)(void *ptr);

/**
 * @brief Função de comparação usando chaves variádicas.
 *
 * Recebe um elemento genérico e uma lista de argumentos contendo chaves
 * para comparação.
 *
 * @param data Ponteiro para o elemento a comparar.
 * @param args Lista de argumentos variáveis (va_list) com as chaves.
 * @return !=0 se o elemento coincidir com as chaves, 0 caso contrário.
 */
typedef int (*compare_key_fn)(void *data, va_list args);

/**
 * @brief Função de comparação entre dois itens.
 *
 * @param a Ponteiro para o primeiro item.
 * @param b Ponteiro para o segundo item.
 * @return !=0 se considerados iguais, 0 caso contrário.
 */
typedef int (*compare_items_fn)(void *a, void *b);

/**
 * @brief Função para imprimir um elemento genérico.
 *
 * @param data   Ponteiro para o elemento a imprimir.
 * @param isLast Indica se o elemento é o último da lista.
 */
typedef void (*print_fn)(void *data, int isLast);

/**
 * @brief Função de callback para percorrer cada elemento.
 *
 * Executada em cada item de uma coleção sem contexto extra.
 *
 * @param data Ponteiro para o elemento atual.
 */
typedef void (*for_each_fn)(void *data);

/**
 * @brief Função de combinação de pares de elementos.
 *
 * Usada quando é necessário processar dois elementos simultaneamente,
 * como ao comparar afinidade ou mesclar informações de duplicatas.
 *
 * @param a Ponteiro para o primeiro elemento.
 * @param b Ponteiro para o segundo elemento.
 */
typedef void (*iter_fn)(void *a, void *b);