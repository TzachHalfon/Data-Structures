#include <stdio.h> /* printf */
#include "heap.h"

static void TestAllFuncs();
static void TestCreate();
static void TestDestroy();
static void TestPush();
static void TestPop();
static void TestPeek();
static void TestRemove();
static void TestSizeEmpty();
static int IntCompare(const void *num1, const void *num2);
static int IntMatch(const void *num1, const void *num2);

int main()
{
    TestAllFuncs();
    return (0);
}

static void TestAllFuncs()
{
    printf("     ~START OF TEST FUNCTION~ \n");
    TestCreate();
    TestPush();
    TestPop();
    TestPeek();
    TestSizeEmpty();
    TestRemove();
    TestDestroy();
    printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
    heap_t *heap = HeapCreate(IntCompare);

    if (NULL != heap)
    {
        printf("HeapCreate working!                               V\n");
    }
    else
    {
        printf("HeapCreate NOT working!                           X\n");
    }

    HeapDestroy(heap);
}

static void TestDestroy()
{
    printf("*Run vlg to test HeapDestroy*\n");
}

static void TestPush()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int size_before = -1;
    int size_after = -1;
    heap_t *heap = HeapCreate(IntCompare);

    size_before = HeapSize(heap);

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);

    size_after = HeapSize(heap);

    if (5 == size_after - size_before && 2 == *(int *)HeapPeek(heap))
    {
        printf("HeapPush working!                                 V\n");
    }
    else
    {
        printf("HeapPush NOT working!                             X\n");
    }

    HeapDestroy(heap);
}

static void TestPop()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int size_before = -1;
    int size_after = -1;
    heap_t *heap = HeapCreate(IntCompare);

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);

    size_before = HeapSize(heap);

    HeapPop(heap);
    HeapPop(heap);

    size_after = HeapSize(heap);

    if (2 == size_before - size_after && 10 == *(int *)HeapPeek(heap))
    {
        printf("HeapPop working!                                  V\n");
    }
    else
    {
        printf("HeapPop NOT working!                              X\n");
    }

    HeapDestroy(heap);
}

static void TestPeek()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int peek1 = -1;
    int peek2 = -1;
    heap_t *heap = HeapCreate(IntCompare);

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    peek1 = *(int *)HeapPeek(heap);
    HeapPush(heap, &d);
    peek2 = *(int *)HeapPeek(heap);
    HeapPush(heap, &e);

    if (2 == peek1 && 2 == peek2)
    {
        printf("HeapPeek working!                                 V\n");
    }
    else
    {
        printf("HeapPeek NOT working!                             X\n");
    }

    HeapDestroy(heap);
}

static void TestSizeEmpty()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int size_before = -1;
    int size_after = -1;
    int empty = -1;
    int not_empty = -1;
    heap_t *heap = HeapCreate(IntCompare);

    size_before = HeapSize(heap);
    empty = HeapIsEmpty(heap);

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);

    size_after = HeapSize(heap);
    not_empty = HeapIsEmpty(heap);

    if (0 == size_before && 5 == size_after)
    {
        printf("HeapSize working!                                 V\n");
    }
    else
    {
        printf("HeapSize NOT working!                             X\n");
    }

    if (1 == empty && 0 == not_empty)
    {
        printf("HeapIsEmpty working!                              V\n");
    }
    else
    {
        printf("HeapIsEmpty NOT working!                          X\n");
    }

    HeapDestroy(heap);
}

static void TestRemove()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int to_find = 2;
    int to_not_find = 144;
    int size_before = -1;
    int size_after = -1;
    heap_t *heap = HeapCreate(IntCompare);

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);

    size_before = HeapSize(heap);

    printf("%d\n", *(int *)HeapPeek(heap));
    HeapRemove(heap, &to_find, IntMatch);
    printf("%d\n", *(int *)HeapPeek(heap));
    HeapRemove(heap, &to_not_find, IntMatch);
    printf("%d\n", *(int *)HeapPeek(heap));
    
    size_after = HeapSize(heap);

    if (5 == size_before && 4 == size_after)
    {
        printf("HeapRemove working!                               V\n");
    }
    else
    {
        printf("HeapRemove NOT working!                           X\n");
    }

    HeapDestroy(heap);
}

static int IntCompare(const void *num1, const void *num2)
{
    return (*(int *)num1 - *(int *)num2);
}

static int IntMatch(const void *num1, const void *num2)
{
    return (*(int *)num1 == *(int *)num2);
}