#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h>/*size_t*/


typedef struct fsa fsa_t;


/* DESCRIPTION:
 * Function initiates an allocator at specified position.
 * Passing an invalid position may cause undefined behaviour.
 *
 * PARAMS:
 * memory_pool 		 - location to initiate our allocator
 * block_size 		 - size of each block
 * pool_size 	     - size of memory pool
 *         
 * RETURN:
 * A pointer to our allocator.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(n)
 */
fsa_t *FSAInit(void *memory_pool, size_t pool_size, size_t block_size);


/* DESCRIPTION:
 * Function returns the size required for properly allocate num_of_blocks blocks of size block_size
 *
 * PARAMS:
 * block_size 		 - size of each block
 * num_of_blocks 	 - num_of_blocks of blocks to allocate
 *         
 * RETURN:
 * the size required to properly host the requested data
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks);


/* DESCRIPTION:
 * Function allocates a block of memory from the allocator.
 *
 * PARAMS:
 * allocator - the allocator to request a block from.
 *         
 * RETURN:
 * The requested memory block.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *FSAAllocate(fsa_t *allocator);


/* DESCRIPTION:
 * Function Free a block of memory from the allocator.
 *
 * PARAMS:
 * allocator - the allocator to free space from
 * to_free   - the pointer to free
 *         
 * RETURN:
 * void.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void FSAFree(fsa_t *allocator, void *to_free);


/* DESCRIPTION:
 * Function return amount of free blocks in our allocator
 *
 * PARAMS:
 * allocator - the allocator to get the free space of
 *         
 * RETURN:
 * The amount of free blocks emaining in the allocator
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
size_t FSACountFree(const fsa_t *allocator);

#endif /* __FSA_H__ */
