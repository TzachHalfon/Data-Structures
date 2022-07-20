/*============================LIBRARIES && MACROS =================================*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "vector.h"
#include "heap.h"

#define POINTER_SIZE 8
#define BEGINNING 0
#define FOUND 1
#define SUCCESS 1
#define FAIL 0
#define CAP 80
typedef struct vector vector_t;
/*================================= STRUCTS =======================================*/
struct heap
{
	vector_t *vector;
	cmp_t cmp;
};

/*=========================== FUNCTION DECLARATION ================================*/
static void HeapifyUp(heap_t *heap, int index);
static void HeapifyDown(heap_t *heap, size_t i);
static int GetParent(int i);
static int GetLeftChild(int i);
static int GetRightChild(int i);
static void SwapEle(heap_t *heap, int i, int j);
static int Cmp(heap_t *heap, int i, int j);
static int GetLastIndex(heap_t *heap);
static int IsMatch(heap_t *heap, cmp_t is_match, size_t index, void *data);
static int AlwaysTrue(const void *empty1, const void *empty2);
static void *GetData(heap_t *heap, size_t index);

/*============================= FUNCTION DEFINITION ==============================*/
heap_t *HeapCreate(cmp_t cmp_func)
{
	heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
	if (heap != NULL)
	{
		heap->vector = VectorCreate(CAP, POINTER_SIZE);
		if (heap->vector == NULL)
		{
			HeapDestroy(heap);
			return (NULL);
		}
		heap->cmp = cmp_func;
	}

	return (heap);
}

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	VectorDestroy(heap->vector);
	free(heap);
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);
	return (GetData((heap_t *)heap, BEGINNING));
}

int HeapPush(heap_t *heap, void *data)
{
	int status = 0;
	assert(NULL != heap);
	status = VectorPushBack(heap->vector, &data);
	if (status != FAIL && 1 < VectorGetSize(heap->vector))
	{
		HeapifyUp(heap, GetLastIndex(heap));
	}
	return (status);
}

void HeapPop(heap_t *heap)
{
	assert(NULL != heap);
	HeapRemove(heap, NULL, AlwaysTrue);
}

void *HeapRemove(heap_t *heap, void *data, cmp_t is_match)
{
	size_t i = 0, last_index = 0;
	void *to_return = NULL;
	assert(NULL != heap);
	assert(NULL != is_match);
	last_index = GetLastIndex(heap);

	for (i = 0; i <= last_index && IsMatch(heap, is_match, i, data) != FOUND; ++i)
		;
	if (i <= last_index)
	{
		to_return = GetData(heap, i);

		SwapEle(heap, i, GetLastIndex(heap));
		VectorPopBack(heap->vector);
		if (i != last_index)
		{
			HeapifyUp(heap, i);
			HeapifyDown(heap, i);
		}
	}

	return (to_return);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	return (VectorIsEmpty(heap->vector));
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	return (VectorGetSize(heap->vector));
}

static void HeapifyUp(heap_t *heap, int index)
{
	int parent = GetParent(index);

	while (0 < Cmp(heap, parent, index))
	{
		SwapEle(heap, parent, index);
		index = parent;
		parent = GetParent(index);
	}
}

static void HeapifyDown(heap_t *heap, size_t index)
{
	size_t last_index = GetLastIndex(heap);
	size_t left_child_index = GetLeftChild(index);
	size_t right_child_index = GetRightChild(index);
	size_t smallest_index = index;
	if (left_child_index <= last_index && (0 < Cmp(heap, smallest_index, left_child_index)))
	{
		smallest_index = left_child_index;
	}
	if (right_child_index <= last_index && (0 < Cmp(heap, smallest_index, right_child_index)))
	{
		smallest_index = right_child_index;
	}
	if (smallest_index != index)
	{
		SwapEle(heap, index, smallest_index);
		HeapifyDown(heap, smallest_index);
	}
}

static int GetParent(int i)
{
	return ((i - 1) / 2);
}

static int GetLeftChild(int i)
{
	return ((2 * i) + 1);
}

static int GetRightChild(int i)
{
	return ((2 * i) + 2);
}

static int GetLastIndex(heap_t *heap)
{
	return (VectorGetSize(heap->vector) - 1);
}

static void SwapEle(heap_t *heap, int i, int j)
{
	void **ptr1 = (void **)VectorAccessAt(heap->vector, i);
	void **ptr2 = (void **)VectorAccessAt(heap->vector, j);
	void *tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static int Cmp(heap_t *heap, int i, int j)
{
	return (heap->cmp(GetData(heap, i), GetData(heap, j)));
}

static int IsMatch(heap_t *heap, cmp_t is_match, size_t index, void *data)
{
	return (is_match(GetData(heap, index), data));
}

static int AlwaysTrue(const void *empty1, const void *empty2)
{
	(void)empty1;
	(void)empty2;
	return 1;
}

static void *GetData(heap_t *heap, size_t index)
{
	return (*(void **)VectorAccessAt((heap)->vector, index));
}