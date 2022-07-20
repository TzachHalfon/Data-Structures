#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h" /* stack_ptr_t */
#include <stddef.h>

typedef struct node
{
	struct node *next;
	int data;
}node_t;

int Fibonacci(int element_index);
node_t *FlipList(node_t *node);
size_t StrLen(const char *str);
int StrCmp(const char *s1,const char *s2);
char *StrCpy(char *des,const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
void SortStack(stack_ptr_t stack);

#endif /* __RECURSION_H__ */