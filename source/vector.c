/*============================LIBRARIES && MACROS =============================*/
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vector.h"

#define EMPTY_VECTOR 0
#define GROWTH_FACTOR 2 

/*====================== STRUCT && FUNCTION DEFINITION =======================*/

struct vector
{
	char *base;
    size_t element_size_in_bytes;
    size_t elements_counter;
    size_t curr_max_element_count;
};


/*
	time  complexity - cannot be determinant because of malloc
	space complexity O(sizeof(struct vector) + (initial_capacity*element_size))
*/
vector_ptr_t VectorCreate(size_t initial_capacity, size_t element_size)
{
	vector_ptr_t vector = (vector_ptr_t)malloc(sizeof(struct vector));
	if(NULL == vector)
	{
		return (NULL);
	}
	vector->base = (char *)malloc((initial_capacity * element_size));
	if(NULL == vector->base)
	{
		return (NULL);
	}
	vector->element_size_in_bytes = element_size;
	vector->elements_counter = 0;
	vector->curr_max_element_count = initial_capacity;

	return (vector);
}

/*
	time  complexity - O(1)
	space complexity -O(1)
*/
void VectorDestroy(vector_ptr_t vector)
{
	assert(NULL != vector);

    free(vector->base);
    vector->base = NULL;

    free(vector);
    vector = NULL;
}


/*
	time  complexity - O(n) because of memcpy
	space complexity -O(1)
*/
int VectorPushBack(vector_ptr_t vector, const void *element_to_push)
{
	char *place_to_push = NULL;
	int status = 1;

	assert(NULL != vector);
	assert(NULL != element_to_push);

	if(vector->curr_max_element_count == vector->elements_counter)
	{
		status = VectorReserve(vector, ((vector->elements_counter) * (GROWTH_FACTOR)));
		if(0 == status)
		{
			return (status);
		}
	}
	
	place_to_push = (vector->base) + (vector->elements_counter) * (vector->element_size_in_bytes);

	vector->elements_counter += 1;
	memcpy(place_to_push, element_to_push, vector->element_size_in_bytes);


	return (status);
}


/*
	time  complexity - O(1)
	space complexity -O(1)
*/
void *VectorPopBack(vector_ptr_t vector)
{
	assert(NULL != vector);

	if(vector->elements_counter < (vector->curr_max_element_count / 2))
	{	
		VectorReserve(vector, (vector->curr_max_element_count / 2));
	}

	vector->elements_counter -= 1;
	return (void *)((vector->base) + (vector->elements_counter * vector->element_size_in_bytes));
}


/*
	time  complexity - O(1)
	space complexity -O(1)
*/
void *VectorAccessAt(const vector_ptr_t vector, size_t index)
{
	assert(NULL != vector);

	return (void *)(vector->base + (index * vector->element_size_in_bytes));
}


/*
	time  complexity - cannot be determinant because of realloc
	space complexity O(new_capacity)
*/
int VectorReserve(vector_ptr_t vector, size_t new_capacity)
{
	assert(NULL != vector);

	vector->base = realloc(vector->base, (new_capacity * vector->element_size_in_bytes));
	if(NULL == vector)
	{
		return (0);
	}

	vector->curr_max_element_count = new_capacity;

	return (1);
}


/*
	time  complexity - O(1)
	space complexity -O(1)
*/
size_t VectorGetSize(const vector_ptr_t vector)
{
	assert(NULL != vector);

	return (vector->elements_counter);
}


/*
	time  complexity - O(1)
	space complexity -O(1)
*/
size_t VectorGetCapacity(const vector_ptr_t vector)
{
	assert(NULL != vector);
	return  (vector->curr_max_element_count);
}


/*
	time  complexity - O(1)
	space complexity -O(1)
*/
int VectorIsEmpty(const vector_ptr_t vector)
{
	assert(NULL != vector);
	return  (EMPTY_VECTOR == vector->elements_counter);
}


/*
	time  complexity - cannot be determinant because of realloc
	space complexity -O(1)
*/
int VectorShrinkToFit(vector_ptr_t vector)
{
	int status = 1;
	
	assert(NULL != vector);

	status = VectorReserve(vector, (vector->elements_counter + 1));

	return (status);	
}
