#include <stdio.h>

#include "pq_heap.h"

static void TestAllFuncs(void);
static void TestCreate(void);
static void TestEnqueue(void);
static void TestDequeue(void);
static void TestSizeEmptyAndSize(void);
static void TestErase(void);
static void TestClear(void);

static int IntCompare(const void *num1, const void *num2);
static int IntMatch(const void *num1, const void *num2);

int main(void)
{
	TestAllFuncs();
	return 0;
}

static void TestAllFuncs(void)
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestEnqueue();
	TestDequeue();
	TestSizeEmptyAndSize();
	TestClear();
	TestErase();
	printf("*Run vlg to test HeapDestroy*\n");
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate(void)
{
	pq_heap_t *q = PQHeapCreate(IntCompare);
	if (q != NULL)
	{
		printf("PQHeapCreate working!                               V\n");
	}
	else
	{
		printf("PQHeapCreate NOT working!                           X\n");
	}
	PQHeapQDestroy(q);
}

static void TestEnqueue(void)
{
	int size_after;
	pq_heap_t *q = PQHeapCreate(IntCompare);
	int nums[] = {8, 2, 10, 15, 11};
	int i = 0;
	for (i = 0; i < 5; ++i)
	{
		PQHeapQEnqueue(q, &nums[i]);
	}

	size_after = PQHeapQSize(q);

	if (5 == size_after && 2 == *(int *)PQHeapQPeek(q))
	{
		printf("PQHeapQSize working!                                V\n");
	}
	else
	{
		printf("PQHeapQSize NOT working!                            X\n");
	}

	PQHeapQDestroy(q);
}

static void TestDequeue(void)
{
	int size_after;
	pq_heap_t *q = PQHeapCreate(IntCompare);
	int nums[] = {8, 2, 10, 15, 11};
	int i = 0;
	int tmp, tmp1, tmp2;
	for (i = 0; i < 5; ++i)
	{
		PQHeapQEnqueue(q, &nums[i]);
	}

	tmp = *(int *)PQHeapQDequeue(q);
	tmp1 = *(int *)PQHeapQDequeue(q);
	tmp2 = *(int *)PQHeapQDequeue(q);
	printf("need to be 2 and was %d\nneed to be 8 and was %d\nneed to be 10 and was %d\n", tmp, tmp1, tmp2);

	size_after = PQHeapQSize(q);

	if (2 == size_after && 11 == *(int *)PQHeapQPeek(q))
	{
		printf("PQHeapQDequeue working!                             V\n");
	}
	else
	{
		printf("PQHeapQDequeue NOT working!                         X\n");
	}

	PQHeapQDestroy(q);
}
static void TestSizeEmptyAndSize(void)
{
	int is_empty, not_empty;
	pq_heap_t *q = PQHeapCreate(IntCompare);
	int nums[] = {8, 2, 10, 15, 11};
	int i = 0;
	is_empty = PQHeapQIsEmpty(q);
	for (i = 0; i < 5; ++i)
	{
		PQHeapQEnqueue(q, &nums[i]);
	}

	not_empty = PQHeapQIsEmpty(q);

	if (0 == not_empty && 1 == is_empty)
	{
		printf("PQHeapQIsEmpty working!                             V\n");
	}
	else
	{
		printf("PQHeapQIsEmpty NOT working!                         X\n");
	}

	PQHeapQDestroy(q);
}

static void TestErase(void)
{
	pq_heap_t *q = PQHeapCreate(IntCompare);
	int nums[] = {8, 2, 10, 15, 11};
	int i = 0;

	for (i = 0; i < 5; ++i)
	{
		PQHeapQEnqueue(q, &nums[i]);
	}

	if (2 == *(int *)PQHeapQErase(q, IntMatch, &nums[1]) && 8 == *(int *)PQHeapQPeek(q))
	{
		printf("PQHeapQErase working!                               V\n");
	}
	else
	{
		printf("PQHeapQErase NOT working!                           X\n");
	}
	PQHeapQDestroy(q);
}

static void TestClear(void)
{
	int size_after;
	pq_heap_t *q = PQHeapCreate(IntCompare);
	int nums[] = {8, 2, 10, 15, 11};
	int i = 0;
	for (i = 0; i < 5; ++i)
	{
		PQHeapQEnqueue(q, &nums[i]);
	}
	PQHeapQClear(q);
	size_after = PQHeapQSize(q);
	if (0 == size_after)
	{
		printf("PQHeapQClear working!                               V\n");
	}
	else
	{
		printf("PQHeapQClear NOT working!                           X\n");
	}
	PQHeapQDestroy(q);
}

static int IntCompare(const void *num1, const void *num2)
{
	return (*(int *)num1 - *(int *)num2);
}

static int IntMatch(const void *num1, const void *num2)
{
	return (*(int *)num1 == *(int *)num2);
}