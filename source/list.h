/**
 * @file list.h
 * @author Paulo Sergio Amorim, Vitor S. Passamani (@paulosergioamorim, vitor.spassamani@gmail.com)
 * @brief Header file for functions that manipulate the list data-structure.
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "utils.h"
#include "cell.h"

/**
 * @brief Opaque definition for the List structure
 */
typedef struct list List;

/**
 * @brief Create a new List object
 * 
 * @param print_fn Function pointer used to print elements in the list
 * @param compare_key_fn Function pointer used to compare keys within the list
 * 
 * @pre print_fn and compare_key_fn must be valid function pointers
 * @post List allocated and initialized with the given function pointers
 * 
 * @return List* - the initialized List object
 */
List *CreateList(print_fn print_fn, compare_key_fn compare_key_fn);

/**
 * @brief Check if a List is empty
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer
 * @post none
 * 
 * @return int 1 if the list is empty, 0 otherwise
 */
int IsEmptyList(List *list);

/**
 * @brief Append an element to the end of the List
 * 
 * @param list Pointer to the List object
 * @param value Pointer to the value to be inserted
 * 
 * @pre list must be a valid, initialized List pointer; value must not be NULL
 * @post The value is added to the end of the list
 * 
 * @return void
 */
void AppendList(List *list, void *value);

/**
 * @brief Remove an element from the List based on a key
 * 
 * @param list Pointer to the List object
 * @param ... Variable arguments representing the key used for comparison
 * 
 * @pre list must be a valid, initialized List pointer; key must match the expected type used in compare_key_fn
 * @post The first element matching the key is removed from the list, if found
 * 
 * @return void
 */
void RemoveList(List *list, ...);

/**
 * @brief Find an element in the List based on a key
 * 
 * @param list Pointer to the List object
 * @param ... Variable arguments representing the key used for comparison
 * 
 * @pre list must be a valid, initialized List pointer; key must match the expected type used in compare_key_fn
 * @post none
 * 
 * @return void* - pointer to the found element, or NULL if not found
 */
void *FindList(List *list, ...);

/**
 * @brief Retrieve the first element in the List
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer and not empty
 * @post none
 * 
 * @return void* - pointer to the first element
 */
void *GetFirstList(List *list);

/**
 * @brief Retrieve the last element in the List
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer and not empty
 * @post none
 * 
 * @return void* - pointer to the last element
 */
void *GetLastList(List *list);

/**
 * @brief Retrieve the first cell of the List
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer
 * @post none
 * 
 * @return Cell* - pointer to the first Cell in the list, or NULL if the list is empty
 */
Cell *GetFirstCellList(List *list);

/**
 * @brief Print all elements in the List
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer
 * @post All elements in the list are printed using the provided print function
 * 
 * @return void
 */
void PrintList(List *list);

/**
 * @brief Free all memory associated with the List
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer
 * @post All memory used by the list is deallocated (the elements are not)
 * 
 * @return void
 */
void FreeList(List *list);

/**
 * @brief Remove all elements from the List without deallocating the List itself
 * 
 * @param list Pointer to the List object
 * 
 * @pre list must be a valid, initialized List pointer
 * @post The list is emptied, and all element memory is deallocated
 * 
 * @return void
 */
void ClearList(List *list);

/**
 * @brief Iterate over the List and apply a function to each elements pair
 * 
 * @param list Pointer to the List object
 * @param iter_fn Function pointer to apply to each pair
 * 
 * @pre list must be a valid, initialized List pointer; iter_fn must be a valid function pointer
 * @post iter_fn is called once for each pair of elements in the list
 * 
 * @return void
 */
void IterList(List *list, iter_fn iter_fn);

/**
 * @brief Apply a function to each element in the List with access to the element
 * 
 * @param list Pointer to the List object
 * @param for_each_fn Function pointer to apply to each element
 * 
 * @pre list must be a valid, initialized List pointer; for_each_fn must be a valid function pointer
 * @post for_each_fn is called once for each element in the list
 * 
 * @return void
 */
void ForEach(List *list, for_each_fn for_each_fn);

/**
 * @brief Create a new List containing elements common to two Lists
 * 
 * @param list1 Pointer to the first List object
 * @param list2 Pointer to the second List object
 * @param compare Function pointer used to compare keys
 * @param print Function pointer used to print elements
 * @param compareItems Function pointer used to compare items for equality
 * 
 * @pre list1 and list2 must be valid, initialized List pointers;
 *       compare, print, and compareItems must be valid function pointers
 * @post A new list is allocated containing elements present in both input lists
 * 
 * @return List* - the new List containing common elements
 */
List *GetCommonItemsList(List *list1, List *list2, compare_key_fn compare, print_fn print, compare_items_fn compareItems);