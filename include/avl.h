/*
    team: OL125-126
    version: 1.0
*/
#ifndef _AVL_H_
#define _AVL_H_

#include <stddef.h> /* size_t */

typedef int (*action_func_t)(void *data, void *param);
typedef int (*cmp_func_t)(const void *data1, const void *data2);

typedef struct avl avl_t;

typedef enum traverse
{
    PRE_ORDER,
    POST_ORDER,
    IN_ORDER

} traverse_t;

/**
 * @brief Function creates an empty avl
 * complexity
 * time: best - O(1)
 * space: O(1)
 * @param cmp_fun pointer to the compare function
 * @return avl_t* Returns a pointer to the created avl
 */
avl_t *AVLCreate(cmp_func_t cmp_fun);

/**
 * @brief Function destroys and performs cleanup on the given avl.
 * passing an invalid avl pointer would result in undefined behaviour
 * This function should be used when finshing using the avl.
 * COMPLEXITY-
 * time: O(n)
 * space: O(1)
 * @param tree pointer to the avl to be destroyed
 */
void AVLDestroy(avl_t *tree);

/**
 * @brief Function returns the data of the given element after inserting it to the given avl.
 * passing an invalid tree would result in undefined behaviour.
 * COMPLEXITY-
 * average time: O(log n)
 * space: O(1)
 * @param tree avl to insert the data to
 * @param data the data to insert
 * @return int 0 for success, 1 if fail.
 */
int AVLInsert(avl_t *tree, void *data);

/**
 * @brief Function removes node for the tree based on the given key from the avl.
 * passing an invalid node would result in undefined behaviour.
 * COMPLEXITY-
 * time: O(log n)
 * space: O(1)
 * @param tree avl tree to remove from.
 * @param key key to find node to remove.
 */
void AVLRemove(avl_t *tree, const void *key);

/**
 * @brief Function checks whether the avl is empty
 * COMPLEXITY-
 * time: O(1)
 * space: O(1)
 * @param tree pointer to the tree to check if empty
 * @return int 1 if the avl is empty or 0 otherwise
 */
int AVLIsEmpty(const avl_t *tree);

/**
 * @brief Function returns the number of elements in the avl.
 * passing an invalid avl would result in undefined behaviour.
 *
 * @param tree pointer to a avl
 *
 * @return size_t number of elements
 */
size_t AVLSize(const avl_t *tree);

/**
 * @brief Function checks the tree's height.
 * COMPLEXITY-
 * time: O(1)
 * space: O(1)
 * @param tree pointer to the tree to check height
 * @return size_t The tree's height - leaf height is 1.
 */
size_t AVLHeight(const avl_t *tree);

/**
 * @brief Function finds elements base on the return value of is_match function ,in a given range.
 * passing invalid nodeators would result in undefined behaviour.
 *
 * @param tree avl tree to find key in.
 * @param key key to find node in avl.
 * @return void* node to the found data. NULL if not found.
 */
void *AVLFind(const avl_t *tree, const void *key);

/**
 * @brief Function performs an action on each element in the given tree.
 * passing an invalid node would result in undefined behaviour.
 *
 * COMPLEXITY-
 * time: O(n)
 * space: O(1)
 * @param tree pointer to the avl tree
 * @param action_func function pointer to an action to perform on a node
 * @param param element for action function
 * @param type enum type of traversal (PRE/POST/IN ORDER)
 * @return int 0 if success 1 else.
 */
int AVLForEach(avl_t *tree, action_func_t action_func, void *param, traverse_t type);

#endif /* __AVL_H__ */