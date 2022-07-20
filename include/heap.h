/*
    team: OL125-126
    version: 1.0
*/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;
typedef int (*cmp_t)(const void *data1, const void *data2);

/* DESCRIPTION:
 * Function creates an empty heap
 *
 * PARAMS:
 * func - compare func, returns a positive int if data1>data2
 *                                negative int if data1<data2
 *                                0 if data1==data2
 *
 * RETURN:
 * Returns a pointer to the created heap
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: O(1)
 */
heap_t *HeapCreate(cmp_t func);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given heap.
 * passing an invalid heap pointer would result in undefined behaviour
 * This function should be used when finshing using the queue.
 *
 * PARAMS:
 * heap - pointer to the heap to be destroyed
 *
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void HeapDestroy(heap_t *heap);

/* DESCRIPTION:
 * Function checks whether the heap is empty
 *
 * PARAMS:
 * heap - pointer to the heap to check if empty
 *
 * RETURN:
 * 1 if the heap is empty or 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
int HeapIsEmpty(const heap_t *heap);

/* DESCRIPTION:
 * Function inserts the given data to the heap in the correct position.
 *
 * PARAMS:
 * heap - pointer to the queue to insert data into
 * data - the data to insert
 *
 * RETURN:
 * 0 on succes,1 on failure.
 *
 * COMPLEXITY:
 * time: O(log(n))
 * space: O(1)
 */
int HeapPush(heap_t *heap, void *data);

/* DESCRIPTION:
 * Function removes the min element of the heap and returns it
 * trying to pop an empty heap will result in undefined behavior
 *
 * PARAMS:
 * heap - pointer to the heap
 *
 * RETURN:
 * pointer to the element.
 *
 * COMPLEXITY:
 * time: O(log(n))
 * space: O(1)
 */
void HeapPop(heap_t *heap);

/* DESCRIPTION:
 * Function finds min element.
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * heap          - pointer to the heap
 *
 * RETURN:
 * pointer to the min element.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *HeapPeek(const heap_t *heap);

/* DESCRIPTION:
 * Function removes the element to remove from heap
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * heap - pointer to a heap
 * data - pointer to data to be removed
 * is_match - pointer to function, returns 1 if true
 * or 0 if false.
 * RETURN:
 * void
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void *HeapRemove(heap_t *heap, void *data, cmp_t is_match);

/* DESCRIPTION:
 * Function returns the size of the heap.
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * heap - pointer to the heap
 *
 * RETURN:
 * Returns a size of heap.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t HeapSize(const heap_t *heap);

#endif /* __HEAP_H__ */
