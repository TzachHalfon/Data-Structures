/*=========================== LIBRARIES & MACROS =============================*/

#include <assert.h> /* assert */
#include "vsa.h"

#define CLOSEST_ALIGNMENT(x) ((x + (WORD_SIZE - 1)) & (~(WORD_SIZE - 1)))
#define STRUCT_SIZE (CLOSEST_ALIGNMENT(sizeof(vsa_t)))
#define WORD_SIZE (sizeof(void *))
#define VALID (long)0xDEADBEEF
#define NOT_VALID (long)0xDEADC0DE
#define EMPTY 0
#define FULL -1
#define ABS(x) (((x) > 0)? (x) : (-1 * (x)))
#define MAX(x,y) (((x) > (y)? (x) : (y)))

/*=========================== FUNCTION DECLARATION ===========================*/

static void ValidSet(vsa_t *vsa);
static void SetNotValid(vsa_t *vsa);
static void FixFragment(vsa_t *vsa);
static vsa_t *FIndBlockToAlloc(vsa_t *vsa, size_t alloc_size);
static void IfPossibleAllocBlock(vsa_t *vsa, size_t alloc_size);

/*======================= STRUCT & FUNCTION DEFINITION =======================*/

struct vsa
{
	long block_size;
	#ifndef NDEBUG
	long is_valid;
	#endif
};

typedef struct vsa vsa_block_t;
/*
block header -> runner for example
char * for running

*/

vsa_t *VsaInit(void *memory_pool, size_t vsa_size)
{
	vsa_t *vsa;
	vsa_block_t *end_vsa;

	assert(NULL != memory_pool);
	assert(EMPTY != vsa_size);

	vsa = memory_pool;
	vsa->block_size = vsa_size - (2 * STRUCT_SIZE);
	ValidSet(vsa);
	
	end_vsa = (vsa_block_t *)((char*)vsa + vsa_size - STRUCT_SIZE);
	end_vsa->block_size = EMPTY;
    ValidSet(end_vsa);
	
	return (vsa);
}

void *VsaAllocate(vsa_t *vsa, size_t alloc_size)
{
	void *to_return = NULL;
	vsa_t *start = vsa;
	
	assert(NULL != vsa);
	assert(0 != alloc_size);
	
	alloc_size = CLOSEST_ALIGNMENT(alloc_size);
	vsa = FIndBlockToAlloc(start, alloc_size);
	
	if(EMPTY == vsa->block_size)
	{
		FixFragment(start);
		vsa = FIndBlockToAlloc(start, alloc_size);
	}
	
	if(EMPTY != vsa->block_size)
	{	
		IfPossibleAllocBlock(vsa, alloc_size);
		to_return = (char*)vsa + STRUCT_SIZE;
	}
	
	return (to_return);
}


void VsaFree(void *to_free)
{
	vsa_block_t *vsa = NULL;
	
	assert(NULL != to_free);
	
    vsa = (vsa_block_t*)((char*)to_free - STRUCT_SIZE);
    assert(vsa->is_valid == VALID);
    vsa->block_size = ABS(vsa->block_size);
}


size_t VsaLargestChunkAvailable(vsa_t *vsa)
{
	size_t max = 0;
	long curr_size = 0;
	
    assert(NULL != vsa);
    
	FixFragment(vsa);
    curr_size = vsa->block_size;

	while(EMPTY != curr_size)
	{
		max = MAX((long)max, vsa->block_size);
		vsa = (vsa_t*)((char*)vsa + ABS(curr_size) + STRUCT_SIZE);
		curr_size = vsa->block_size;
	}
	
	return (max);
}


static void FixFragment(vsa_t *vsa)
{
    vsa_block_t *vsa_next;
    
    do
    {
        vsa_next = (vsa_block_t*)((char*)vsa + STRUCT_SIZE + ABS(vsa->block_size));
        
        if(vsa->block_size > 0 && vsa_next->block_size > 0)
        {
            vsa->block_size += vsa_next->block_size + STRUCT_SIZE;
            SetNotValid(vsa_next);
            continue;
        }
        
        vsa = vsa_next;
    } while(EMPTY != vsa_next->block_size);
}


static void ValidSet(vsa_t *vsa)
{
	#ifndef NDEBUG
	vsa->is_valid = VALID;
	#endif
	(void)vsa;
}


static void SetNotValid(vsa_t *vsa)
{
	#ifndef NDEBUG
	vsa->is_valid = NOT_VALID;
	#endif
	(void)vsa;
}


static vsa_t *FIndBlockToAlloc(vsa_t *vsa, size_t alloc_size)
{
	long curr_size = 0;
	
	assert(NULL != vsa);
	
	curr_size = vsa->block_size;
	
	while(EMPTY != curr_size && (long)alloc_size > curr_size)
	{
		vsa = (vsa_t *)((char*)vsa + ABS(curr_size) + STRUCT_SIZE);
		curr_size = vsa->block_size;
	}
	
	return (vsa);
}


static void IfPossibleAllocBlock(vsa_t *vsa, size_t alloc_size)
{
	
	long curr_size = vsa->block_size;
	vsa_block_t *new_vsa = NULL;
	
	if(curr_size > (long)(alloc_size + STRUCT_SIZE))
	{
		new_vsa = (vsa_block_t *)((char*)vsa + alloc_size + STRUCT_SIZE);
		new_vsa->block_size = vsa->block_size - alloc_size - STRUCT_SIZE;
		ValidSet(new_vsa);
			
		vsa->block_size = FULL * alloc_size;
	}
	else
	{
		vsa->block_size *= FULL;
	}
}
