/*============================LIBRARIES && MACROS =================================*/
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "pq_heap.h"

/*================================= STRUCTS =======================================*/
struct pq_heap
{
	heap_t *heap;
};

/*=========================== FUNCTION DECLARATION ================================*/
pq_heap_t *PQHeapCreate(pq_heap_cmp_t func)
{
	pq_heap_t *queue = (pq_heap_t *)malloc(sizeof(pq_heap_t));
	if (NULL == queue)
	{
		return NULL;
	}

	queue->heap = HeapCreate(func);
	if (NULL == queue->heap)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

void PQHeapQDestroy(pq_heap_t *queue)
{
	assert(NULL != queue);
	HeapDestroy(queue->heap);
	queue->heap = NULL;
	free(queue);
}

void PQHeapQClear(pq_heap_t *queue)
{
	size_t i = 0;
	size_t size = HeapSize(queue->heap);
	assert(NULL != queue);
	for (i = 0; i < size; ++i)
	{
		HeapPop(queue->heap);
	}
}

void *PQHeapQErase(pq_heap_t *queue, pq_heap_cmp_t is_match, const void *param)
{
	assert(NULL != queue);
	return (HeapRemove(queue->heap, (void *)param, is_match));
}

int PQHeapQEnqueue(pq_heap_t *queue, void *data)
{
	assert(NULL != queue);
	return (HeapPush(queue->heap, data));
}

void *PQHeapQDequeue(pq_heap_t *queue)
{
	void *data;
	assert(NULL != queue);
	data = HeapPeek(queue->heap);
	HeapPop(queue->heap);

	return (data);
}

void *PQHeapQPeek(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (HeapPeek(queue->heap));
}

int PQHeapQIsEmpty(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (HeapIsEmpty(queue->heap));
}

size_t PQHeapQSize(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (HeapSize(queue->heap));
}
