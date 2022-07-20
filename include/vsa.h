#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /*size_t*/

typedef struct vsa vsa_t;

/*
DESCRIPTION:
 * Function initiates an allocator at specified position.
 * Passing an invalid position may cause undefined behaviour.
 *
 * PARAMS:
 * memory_pool	- location to initiate our allocator
 * pool_size	- size of memory pool
 *         
 * RETURN:
 * A pointer to our allocator.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(n)
 */
vsa_t *VsaInit(void *memory_pool, size_t pool_size);


/* DESCRIPTION:
 * Function allocates a block of memory from the allocator.
 *
 * PARAMS:
 * allocator - the allocator
 *         
 * RETURN:
 * The requested memory block.
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void *VsaAllocate(vsa_t *allocator, size_t block_size);

/* DESCRIPTION:
 * Function free the block of memory from memory pool
 *
 * PARAMS:
 * allocator - the allocator
 * to_free   - the pointer to free
 *         
 * RETURN:
 * void.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void VsaFree(void *to_free);

/* DESCRIPTION:
 * Function return size of the largest chunk in our memory pool.
 *
 * PARAMS:
 * allocator - the allocator
 *         
 * RETURN:
 * The size of the largest chunk in the allocator
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
size_t VsaLargestChunkAvailable(vsa_t *allocator);

#endif /* __VSA_H__ */
