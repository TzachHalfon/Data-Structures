/*============================LIBRARYS && MACROS =============================*/
#include <string.h>
#include "recursion.h"

/*========================== FUNCTION DECLARATION ============================*/
char *StrCpyRec(char *des,const char *src, int n);
node_t *FlipListRec(node_t *curr,node_t *next, node_t *after_next);
void InsertSorted(stack_ptr_t stack, int num);

/*========================== FUNCTION DEFINITION =============================*/
int FibonacciIterative(int index)
{
	int curr = 1;
	int next = 1;
	int i = 0;

	for (i = 0; i < index; ++i)
	{
		next += curr;
		curr = next;
	}
	return (curr);
}

int Fibonacci(int index)
{
	return  (index == 1 || index == 2)? (1) : (Fibonacci(index - 1) + Fibonacci(index - 2));
}

size_t StrLen(const char *str)
{
	if (*str == '\0')
	{
		return (0);
	}

	return StrLen(str + 1) + 1;
}

int StrCmp(const char *s1,const char *s2)
{
	if(*s1 != *s2 || *s1 == '\0')
	{
		return (*s1 - *s2);
	}

	return StrCmp(s1 +1, s2 +1);
}

char *StrCpy(char *des,const char *src)
{
	return StrCpyRec(des, src , 0);
}

char *StrCpyRec(char *des,const char *src, int n)
{
	*des = *src;
	if(*src == '\0')
	{
		return (des - n);
	}
	return StrCpyRec(des + 1, src + 1, n + 1);
}

char *StrCat(char *dest, const char *src)
{
	dest = dest + StrLen(dest);
	return StrCpyRec(dest, src, 0);
}


char *StrStr(const char *haystack, const char *needle)
{
	if(*haystack == '\0')
	{
		return (NULL);
	}
	if(*haystack == *needle)
	{
		if(strncmp(haystack, needle, StrLen(needle)) == 0)
		{
			return ((char*)haystack);
		}
	}

	return StrStr(haystack + 1, needle);
}


node_t *FlipList(node_t *node)
{
	return FlipListRec(NULL, node, node->next);
}

node_t *FlipListRec(node_t *prev,node_t *curr, node_t *next)
{
	curr->next = prev;

	if(next == NULL)
	{
		return (curr);
	}
	return (FlipListRec(curr, next, next->next));
}


void SortStack(stack_ptr_t stack)
{
	int num;
	if(!StackIsEmpty(stack))
	{
		num = *(int*)StackPop(stack);
		SortStack(stack);
		InsertSorted(stack,num);
	}
	(void)num;
}

void InsertSorted(stack_ptr_t stack, int num)
{
	int temp;
	if (StackIsEmpty(stack) || num > *(int*)StackPeek(stack))
	{
		StackPush(stack, &num);
		return;
	}

	temp = *(int*)StackPop(stack);
	InsertSorted(stack, num);
	StackPush(stack, &temp);
	(void)temp;
}