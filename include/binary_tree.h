/*
	team: OL125-126
	version: 2.0.2
*/
#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include <stddef.h> /* size_t */

typedef struct binary_tree binary_tree_t;
typedef struct binary_tree_node *binary_tree_iterator_t;

typedef int (*action_t)(void *data, void *param);
typedef int (*compare_t)(const void *data, const void *data2);

/**
 * @brief Function creates an empty binary_tree
 * time: best - O(1), worst - indeterminable
 * space: O(1)
 * @param compare_func compare function
 * @return binary_tree_t* Returns a pointer to the head of the binary_tree
 */
binary_tree_t *BinaryTreeCreate(compare_t compare_func);

/**
 * @brief Function destroys and performs cleanup on the given binary_tree.
 * passing an invalid head pointer would result in undefined behaviour
 * time: O(n)
 * space: O(1)
 * @param binary_tree pointer to the binary_tree to be destroyed
 */
void BinaryTreeDestroy(binary_tree_t *binary_tree);

/**
 * @brief Function finds given nodes given a range
 * return value.
 * passing an invalid iterator would result in undefined behaviour.
 * Trying to find an empty node will result in undefined behavior.
 * time: O(log n)
 * space: O(1)
 * @param binary_tree pointer to the binary_tree
 * @param key_to_data key to element to find
 * @return binary_tree_iterator_t
 */
binary_tree_iterator_t BinaryTreeFind(const binary_tree_t *binary_tree, void *key_to_data);

/**
 * @brief Function removes the selected element from the binary_tree.
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(log(n))
 * space: O(1)
 * @param iter selected element to remove.
 */
void BinaryTreeRemove(binary_tree_iterator_t iter);

/**
 * @brief Function returns the data of the given element after inserting it before the given iterator.
 * passing an invalid iterator would result in undefined behaviour.
 * passing an invalid data would result in undefined behaviour.
 * time: O(log(n))
 * space: O(1)
 * @param binary_tree pointer to the binary_tree
 * @param data the data to insert
 * @return binary_tree_iterator_t an iterator to the data that has been inserted if not returns the given iterator again
 */
binary_tree_iterator_t BinaryTreeInsert(binary_tree_t *binary_tree, void *data);

/**
 * @brief Function returns the number of elements on the binary_tree.
 * passing an invalid binary_tree would result in undefined behaviour.
 * time: O(n)
 * space: O(1)
 * @param binary_tree head of the binary_tree to count from
 * @return size_t number of elements
 */
size_t BinaryTreeSize(const binary_tree_t *binary_tree);

/**
 * @brief Function gets the data in the iterator's place
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(1)
 * space: O(1)
 * @param iter iterator to the binary_tree to access from
 * @return void* Returns a pointer to the data that has been accessed,
 * NULL if the binary_tree is empty
 */
void *BinaryTreeGetData(const binary_tree_iterator_t iter);

/**
 * @brief Function performs an action on each element in a given range.
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(n)
 * space: O(1)
 * @param from iterator to start from.
 * @param to   iterator to end at will not check it.
 * @param action_func function pointer to perform an action on an element
 * @param param element for action function
 * @return int 0 if success 1 else.
 */
int BinaryTreeForEach(binary_tree_iterator_t from,
					  binary_tree_iterator_t to,
					  action_t action_func,
					  void *param);

/**
 * @brief Function returns an iterator to the next element in the binary_tree.
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(log(n))
 * space: O(1)
 * @param iter iterator to get his next element.
 * @return binary_tree_iterator_t iterator to the next element.
 */
binary_tree_iterator_t BinaryTreeNext(binary_tree_iterator_t iter);

/**
 * @brief Function returns an iterator to the next element in the binary_tree.
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(log(n))
 * space: O(1)
 * @param iter iterator of the part of the binary_tree to get the next from.
 * @return binary_tree_iterator_t iterator to the next element.
 */
binary_tree_iterator_t BinaryTreePrev(binary_tree_iterator_t iter);

/**
 * @brief Function returns an iterator to the beginning of the binary_tree.
 * passing an empty binary_tree would result in undefined behaviour.
 * time: O(log(n))
 * space: O(1)
 * @param binary_tree pointer to start of the binary_tree
 * @return binary_tree_iterator_t iterator to the start of the binary_tree.
 */
binary_tree_iterator_t BinaryTreeBegin(const binary_tree_t *binary_tree);

/**
 * @brief Function returns an iterator to the end of the binary_tree.
 * passing an empty binary_tree would result in undefined behaviour.
 * time: O(1)
 * space: O(1)
 * @param binary_tree pointer to start of the binary_tree
 * @return binary_tree_iterator_t iterator to the end of the binary_tree.
 */
binary_tree_iterator_t BinaryTreeEnd(const binary_tree_t *binary_tree);

/**
 * @brief Function checks if the tree is empty.
 * passing an empty binary_tree would result in undefined behaviour.
 * time: O(1)
 * space: O(1)
 * @param binary_tree pointer to start of the binary_tree
 * @return int 1 empty, 0 else.
 */
int BinaryTreeIsEmpty(const binary_tree_t *binary_tree);

/**
 * @brief Function compares between two iterators.
 * passing an invalid iterator would result in undefined behaviour.
 * time: O(1)
 * space: O(1)
 * @param iter_one first iterator to compare
 * @param iter_two second iterator to compare
 * @return int 0 when iterators are identical, 1 otherwise.
 */
int BinaryTreeIsIterEqual(const binary_tree_iterator_t iter_one, const binary_tree_iterator_t iter_two);

#endif /* __BINARY_TREE_H__ */
