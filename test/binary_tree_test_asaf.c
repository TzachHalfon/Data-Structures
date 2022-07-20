#include <stdio.h> /* printf */

#include "binary_tree.h"

static int IntCompare(const void *data1, const void *data2);
static int IntAdd(void *data, void *param);

static void TestAllFuncs();
static void TestCreate();
static void TestSizeAndEmpty();
static void TestInsert();
static void TestGetData();
static void TestRemove();
static void TestIterFuncs();
static void TestDestroy();
static void TestFind();
static void TestForEach();


int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestSizeAndEmpty();
	TestInsert();
	TestGetData();
	TestRemove();
	TestForEach();
	TestFind();
	TestIterFuncs();
	TestDestroy();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	int x = 3;
	int y = 5;
	binary_tree_t *tree = BinaryTreeCreate(IntCompare);
	
	printf ("\033[1;31m");
	
	if(NULL != tree)
	{
		printf("SortedListCreate working!                            V\n");
	}
	else
	{
		printf("SortedListCreate NOT working!                        X\n");
	}
	
	BinaryTreeInsert(tree, (void*)&x);
	BinaryTreeInsert(tree, (void*)&y);
	
	BinaryTreeDestroy(tree);
}

static void TestDestroy()
{
	printf ("\033[1;36m");
	printf("*Run vlg to test BinaryTreeDestroy*\n");
	printf ("\033[0m");
}

static void TestSizeAndEmpty()
{	
	int x = 3;
	int y = 5;
	int before = -1;
	int after = -1;
	int empty = -1;
	int not_empty = -1;
	
	binary_tree_t *tree = BinaryTreeCreate(IntCompare);
	
	before = BinaryTreeSize(tree);
	empty = BinaryTreeIsEmpty(tree);
	
	BinaryTreeInsert(tree, (void*)&x);
	BinaryTreeInsert(tree, (void*)&y);
	
	after = BinaryTreeSize(tree);
	not_empty = BinaryTreeIsEmpty(tree);
	printf ("\033[1;32m");
	if(0 == before && 2 == after)
	{
		printf("BinaryTreeSize working!          		             V\n");
	}
	else
	{
		printf("BinaryTreeSize NOT working!	                     X\n");
	}
	printf ("\033[1;37m");
	if(1 == empty && 0 == not_empty)
	{
		printf("BinaryTreeIsEmpty working!                      	     V\n");
	}
	else
	{
		printf("BinaryTreeIsEmpty NOT working!                      X\n");
	}
	
	BinaryTreeDestroy(tree);
}

static void TestInsert()
{
	int a = 5, b = 3, c = 4, d = 2, e = 8, f = 12, g = 10, h = 9, i = 11, j = 14;
	binary_tree_iterator_t runner = NULL;
	int first, second, third;

	binary_tree_t *tree = BinaryTreeCreate(IntCompare);

	BinaryTreeInsert(tree, &a);
	BinaryTreeInsert(tree, &b);
	BinaryTreeInsert(tree, &c);
	BinaryTreeInsert(tree, &d);
	BinaryTreeInsert(tree, &e);
	BinaryTreeInsert(tree, &f);
	BinaryTreeInsert(tree, &g);
	BinaryTreeInsert(tree, &h);
	BinaryTreeInsert(tree, &i);
	BinaryTreeInsert(tree, &j);
	
	runner = BinaryTreeBegin(tree);
	first = *(int*)BinaryTreeGetData(runner);
	runner = BinaryTreeNext(runner);
	second = *(int*)BinaryTreeGetData(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	third = *(int*)BinaryTreeGetData(runner);
	printf ("\033[1;33m");
	if((2 == first) && (3 == second) && (5 == third))
	{
		printf("BinaryTreeInsert working!                                   V\n");
	}
	else
	{
		printf("BinaryTreeInsert NOT working!                               X\n");
	}
	
	BinaryTreeDestroy(tree);
}


static void TestGetData()
{
	int a = 5, b = 3, c = 4;
	binary_tree_iterator_t runner = NULL;
	

	binary_tree_t *tree = BinaryTreeCreate(IntCompare);

	BinaryTreeInsert(tree, &a);
	BinaryTreeInsert(tree, &b);
	BinaryTreeInsert(tree, &c);
	
	runner = BinaryTreeBegin(tree);
	runner = BinaryTreeNext(runner);
	
	printf ("\033[1;34m");
	if(3 == *(int*)BinaryTreeGetData(BinaryTreeBegin(tree)) && 4 == *(int *)BinaryTreeGetData(runner))
	{
		printf("BinaryTreeGetData working!                                  V\n");
	}
	else
	{
		printf("BinaryTreeGetData NOT working!                              X\n");
	}
	
	BinaryTreeDestroy(tree);
}

static void TestRemove()
{
	int a = 5, b = 3, c = 4;
	int size_before = -1, size_after = -1;

	binary_tree_t *tree = BinaryTreeCreate(IntCompare);

	BinaryTreeInsert(tree, &a);
	BinaryTreeInsert(tree, &b);
	BinaryTreeInsert(tree, &c);
	
	size_before = BinaryTreeSize(tree);
	
	BinaryTreeRemove(BinaryTreeBegin(tree));
	BinaryTreeRemove(BinaryTreeBegin(tree));
	
	size_after = BinaryTreeSize(tree);
	printf ("\033[1;35m");
	if((2 == size_before - size_after) && 
	5 == *(int *)BinaryTreeGetData(BinaryTreeBegin(tree)))
	{
		printf("BinaryTreeRemove working!                                   V\n");
	}
	else
	{
		printf("BinaryTreeRemove NOT working!                               X\n");
	}
	
	BinaryTreeDestroy(tree);
}

static void TestIterFuncs()
{
	int a = 5, b = 3, c = 4, d = 2, e = 8, f = 12, g = 10, h = 9, i = 11, j = 14;
	binary_tree_iterator_t runner = NULL, runner2 = NULL;
	int first, second, third;

	binary_tree_t *tree = BinaryTreeCreate(IntCompare);

	BinaryTreeInsert(tree, &a);
	BinaryTreeInsert(tree, &b);
	BinaryTreeInsert(tree, &c);
	BinaryTreeInsert(tree, &d);
	BinaryTreeInsert(tree, &e);
	BinaryTreeInsert(tree, &f);
	BinaryTreeInsert(tree, &g);
	BinaryTreeInsert(tree, &h);
	BinaryTreeInsert(tree, &i);
	BinaryTreeInsert(tree, &j);
	
	runner = BinaryTreeBegin(tree);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	first = *(int *)BinaryTreeGetData(runner);


	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreeNext(runner);
	runner = BinaryTreePrev(runner);	
	second = *(int *)BinaryTreeGetData(runner);

	runner = BinaryTreeNext(runner);
	runner = BinaryTreePrev(runner);
	runner = BinaryTreePrev(runner);
	third = *(int *)BinaryTreeGetData(runner);

	runner2 = BinaryTreeBegin(tree);
	runner2 = BinaryTreeNext(runner2);	
	runner2 = BinaryTreeNext(runner2);	
	runner2 = BinaryTreeNext(runner2);	
	runner2 = BinaryTreeNext(runner2);	
	runner2 = BinaryTreeNext(runner2);	
	runner2 = BinaryTreeNext(runner2);	
	runner = BinaryTreePrev(runner);


	printf ("\033[1;36m");
	if(2 == *(int *)BinaryTreeGetData(BinaryTreeBegin(tree)))
	{
		printf("BinaryTreeBegin working!                                    V\n");
	}
	else
	{
		printf("BinaryTreeBegin NOT working!                                X\n");
	}
	printf ("\033[1;37m");
	if(NULL == (binary_tree_t*)BinaryTreeGetData(BinaryTreeEnd(tree)))
	{
		printf("BinaryTreeEnd working!                                      V\n");
	}
	else
	{
		printf("BinaryTreeEnd NOT working!                                  X\n");
	}
	printf ("\033[1;35m");
	if(9 == first)
	{
		printf("BinaryTreeNext working!                                 V\n");
	}
	else
	{
		printf("BinaryTreeNext NOT working!                             X\n");
	}
	printf ("\033[1;31m");
	if(12 == second && 11 == third )
	{
		printf("BinaryTreePrev working!                                 V\n");
	}
	else
	{
		printf("BinaryTreePrev NOT working!                             X\n");
	}
	printf ("\033[1;32m");
	if(runner2 == runner)
	{
		printf("SortedListIsSame working!                        V\n");
	}
	else
	{
		printf("SortedListIsSame NOT working!                    X\n");
	}
	
	BinaryTreeDestroy(tree);
}


static void TestFind()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	int to_find = 5;
	int not_there = 12;

	binary_tree_iterator_t not_found;
	binary_tree_iterator_t found_iter;
	
	binary_tree_t *tree = BinaryTreeCreate(IntCompare);
	
	BinaryTreeInsert(tree, (void*)&a);
	BinaryTreeInsert(tree, (void*)&b);
	BinaryTreeInsert(tree, (void*)&c);
	BinaryTreeInsert(tree, (void*)&d);
	
	found_iter = BinaryTreeFind(tree, (void *)&to_find);
	not_found = BinaryTreeFind(tree, (void *)&not_there);
	printf ("\033[1;33m");
	if(5 == *(int *)BinaryTreeGetData(found_iter) && BinaryTreeEnd(tree) == not_found)
    {
    	printf("BinaryTreeFind working!                                     V\n");
	}
	else
	{
		printf("BinaryTreeFind NOT working!                                 X\n");
	}
	
	BinaryTreeDestroy(tree);
}

static void TestForEach()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	int num_to_add = 10;
	
	binary_tree_t *tree = BinaryTreeCreate(IntCompare);
	
	BinaryTreeInsert(tree, (void*)&a);
	BinaryTreeInsert(tree, (void*)&b);
	BinaryTreeInsert(tree, (void*)&c);
	BinaryTreeInsert(tree, (void*)&d);
	
	BinaryTreeForEach(BinaryTreeBegin(tree), BinaryTreeEnd(tree), IntAdd, (void *)&num_to_add);
	printf ("\033[1;34m");
	if(13 == *(int*)BinaryTreeGetData(BinaryTreeBegin(tree)) && 
		19 == *(int*)BinaryTreeGetData(BinaryTreePrev(BinaryTreeEnd(tree))))
    {
    	printf("BinaryTreeForEach working!                                  V\n");
	}
	else
	{
		printf("BinaryTreeForEach NOT working!                              X\n");
	}
	
	BinaryTreeDestroy(tree);
}



static int IntCompare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

int IntAdd(void *data, void *param)
{
	*(int *)data += *(int *)param;

	return 0;
}


