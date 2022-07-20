#include <stdio.h> /*printf*/
#include "recursion.h"

static void TestAllFuncs();
static void TestFibonacci();
static void TestStrLen();
static void TestStrCmp();
static void TestStrCpy();
static void TestStrCat();
static void TestStrStr();
static void TestFlipList();
static void TestSortedStack();

int main ()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{	
	printf("     ~START OF TEST FUNCTION~ \n");
	TestFibonacci();
	TestFlipList();
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrCat();
	TestStrStr();
	TestSortedStack();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestFibonacci()
{
	int num = Fibonacci(8);
	int num2 = Fibonacci(9);
	int num3 = Fibonacci(10);
	
	if(num + num2 == num3)
	{
		printf("Fibonacci working!                                   V\n");
	}
	else
	{
		printf("Fibonacci NOT working!                               X\n");
	}
}

static void TestFlipList()
{
	node_t node;
	node_t node2;
	node_t node3;
	node_t node4;
	
	node.data = 1;
	node.next = &node2;
	node2.data = 2;
	node2.next = &node3;
	node3.data = 3;
	node3.next = &node4;
	node4.data = 4;
	node4.next = NULL;
	
	FlipList(&node);
	
	if(3 == node4.next->data && 2 == node3.next->data && 1 == node2.next->data)
	{
		printf("FlipList working!                                    V\n");
	}
	else
	{
		printf("FlipList NOT working!                                X\n");
	}
}

static void TestStrLen()
{
	int num = StrLen("hello world");
	int num2 = StrLen("yellow submarine");
	
	if(11 == num && 16 == num2)
	{
		printf("StrLen working!                                      V\n");
	}
	else
	{
		printf("StrLen NOT working!                                  X\n");
	}
}

static void TestStrCmp()
{
	int num = StrCmp("heleoworld", "heleoworld");
	int num2 = StrCmp("helloworle", "heleoworld");
	
	if(0 == num && 7 == num2)
	{
		printf("StrCmp working!                                      V\n");
	}
	else
	{
		printf("StrCmp NOT working!                                  X\n");
	}
}

static void TestStrCpy()
{
	char str[20] = "hello world";
	char str2[20];
	StrCpy(str2,str);
	
	if(0 == StrCmp(str,str2))
	{
		printf("StrCpy working!                                      V\n");
	}
	else
	{
		printf("StrCpy NOT working!                                  X\n");
		printf("%d\n",StrCmp(str,str2));
		printf("%s\n",str2);
	}
}

static void TestStrCat()
{
	char str[10] = " world";
	char str2[20] = "hello";
	StrCat(str2,str);
	
	if(0 == StrCmp(str2, "hello world"))
	{
		printf("StrCat working!                                      V\n");
	}
	else
	{
		printf("StrCat NOT working!                                  X\n");
	}
}

static void TestStrStr()
{
	char needle[10] = "ll";
	char needle2[10] = "f";
	char str2[20] = "hello world";
	char *rtn = StrStr(str2,needle);
	char *rtn2 = StrStr(str2,needle2);
	
	if(NULL != rtn && NULL == rtn2)
	{
		printf("StrStr working!                                      V\n");
	}
	else
	{
		printf("StrStr NOT working!                                  X\n");
	}
}

static void TestSortedStack()
{
	stack_ptr_t stack = StackCreate(10,sizeof(int));
	int nums[10] = {20,-5,2,15,17,0,9,10,12,-10};
	int sorted[10] = {20,17,15,12,10,9,2,0,-5,-10};
					 
	int i = 0;

	for (i = 0; i < 10; ++i)
	{
		StackPush(stack, &nums[i]);	
	}

	SortStack(stack);

	for (i = 0; i < 10; ++i)
	{
		if(*(int*)StackPop(stack) != sorted[i])
		{
			printf("SortStack NOT working!                               X\n");
			return;
		}
	}
	printf("SortStack working!                                   V\n");
	StackDestroy(stack);
}