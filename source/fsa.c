#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "fsa.h"

#define CLOSEST_ALIGNMENT(x) ((x + (WORD_SIZE - 1)) & (~(WORD_SIZE - 1)))
#define WORD_SIZE (sizeof(void *))
#define OFFSET (CLOSEST_ALIGNMENT(sizeof(fsa_t)))
#define END_BLOCK ((size_t)0)

/*static size_t CLOSEST_ALIGNMENT(size_t block_size);*/

struct fsa
{
	size_t block_size;
	size_t offset_next_available;
};

fsa_t *FSAInit(void *memory_pool, size_t pool_size, size_t block_size)
{
	fsa_t *fsa;
	char *byte_writer;
	size_t num_of_blocks = 0;
	block_size = CLOSEST_ALIGNMENT(block_size);

	assert(NULL != memory_pool);
	assert(pool_size > block_size);
	assert(0 != block_size);

	fsa = (fsa_t *)memory_pool;
	fsa->block_size = block_size;
	fsa->offset_next_available = OFFSET;

	byte_writer = (char *)memory_pool + OFFSET;
	num_of_blocks = (pool_size - OFFSET) / block_size;

	while (1 < num_of_blocks--)
	{
		*byte_writer = (byte_writer - (char *)memory_pool) + block_size;
		byte_writer += block_size;
	}

	*(size_t *)byte_writer = END_BLOCK;

	return (fsa);
}

void *FSAAllocate(fsa_t *allocator)
{
	void *to_return = NULL;

	assert(NULL != allocator);

	if (END_BLOCK != allocator->offset_next_available)
	{
		to_return = (char *)allocator + allocator->offset_next_available;
		allocator->offset_next_available = *((size_t *)to_return);
	}

	return (to_return);
}

void FSAFree(fsa_t *allocator, void *to_free)
{
	assert(NULL != allocator);
	assert(NULL != to_free);

	*(size_t *)to_free = allocator->offset_next_available;
	allocator->offset_next_available = (size_t)to_free - (size_t)allocator;
}

size_t FSACountFree(const fsa_t *allocator)
{
	size_t counter = 0;
	size_t runner = 0;

	assert(NULL != allocator);

	runner = allocator->offset_next_available;

	while (END_BLOCK != runner)
	{
		++counter;
		runner = *(size_t *)((size_t)allocator + runner);
	}
	return (counter);
}

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
	block_size = CLOSEST_ALIGNMENT(block_size);
	return ((num_of_blocks * block_size) + OFFSET);
}

