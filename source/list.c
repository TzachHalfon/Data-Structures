/*============================LIBRARIES && MACROS ============================*/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../include/slist.h"
#define DUMMY_BUFFER 1

/*========================== FUNCTION DECLARATION ============================*/

static void FreeNodes(slist_ptr_t list);

/*====================== STRUCT && FUNCTION DEFINITION =======================*/

typedef struct slist_node
{
	void *data;
	slist_node_ptr_t next;

} node_t;

typedef struct slist
{
	slist_node_ptr_t head;
	slist_node_ptr_t tail;

} list_t;

slist_ptr_t SListCreate(void)
{
	slist_ptr_t list = (slist_ptr_t)malloc(sizeof(list_t));
	slist_node_ptr_t dummy;
	if (NULL == list)
	{
		return (NULL);
	}
	dummy = (slist_node_ptr_t)malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		return (NULL);
	}
	list->head = dummy;
	list->tail = dummy;
	dummy->next = NULL;
	dummy->data = list;

	return (list);
}

void SListDestroy(slist_ptr_t list)
{
	assert(NULL != list);
	FreeNodes(list);
	free(list);
	list = NULL;
}

static void FreeNodes(slist_ptr_t list)
{
	slist_node_ptr_t tmp = NULL;
	size_t i = 0;
	size_t limit = 0;
	assert(NULL != list);
	limit = SListCount(list);

	for (i = 0; i < limit + DUMMY_BUFFER; ++i)
	{
		tmp = list->head;
		list->head = list->head->next;
		free(tmp);
		tmp = NULL;
	}
}

slist_iter SListInsertBefore(slist_iter place_to_insert, const void *data)
{
	slist_node_ptr_t new_node = (slist_node_ptr_t)malloc(sizeof(node_t));

	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = place_to_insert->data;
	new_node->next = place_to_insert->next;

	if (NULL == new_node->next)
	{
		((slist_ptr_t)new_node->data)->tail = new_node;
	}

	place_to_insert->next = new_node;
	place_to_insert->data = (void *)data;

	return (place_to_insert);
}

void SListRemove(slist_iter iter)
{
	slist_iter temp = NULL;

	assert(NULL != iter);

	temp = SListIterNext(iter);
	iter->data = temp->data;
	iter->next = temp->next;
	if (NULL == iter->next)
	{
		((slist_ptr_t)(iter->data))->tail = iter;
	}
	free(temp);
}

const void *SListGetData(const slist_iter iter)
{
	assert(NULL != iter);
	return iter->data;
}

void SListSetData(slist_iter iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	iter->data = data;
}

size_t SListCount(const slist_ptr_t list)
{
	size_t count = 0;
	slist_iter iter = NULL;
	assert(NULL != list);
	iter = SListBegin(list);

	while (iter->next != NULL)
	{
		iter = SListIterNext(iter);
		++count;
	}
	return (count);
}

slist_iter SListFind(slist_iter from, slist_iter to, is_match_t func, void *data)
{
	int found = 0;

	while (!SListIsIterEqual(from, to))
	{
		found = func(from->data, data);
		if (1 == found)
		{
			return (from);
		}
		from = SListIterNext(from);
	}

	return (to);
}

int SListIsIterEqual(slist_iter iter_one, slist_iter iter_two)
{
	assert(NULL != iter_one);
	assert(NULL != iter_two);
	return (iter_one == iter_two);
}

int SListForEach(slist_iter from, slist_iter to, slist_action_t action_func,
				 void *param)
{
	int status = 0;
	while (!SListIsIterEqual(from, to) && 0 == status)
	{
		status = action_func(from->data, param);
		from = from->next;
	}
	return status;
}

slist_iter SListIterNext(slist_iter iter)
{
	iter = iter->next;

	return iter;
}

slist_iter SListBegin(const slist_ptr_t list)
{
	assert(NULL != list);

	return (list->head);
}

slist_iter SListEnd(const slist_ptr_t list)
{
	assert(NULL != list);

	return (list->tail);
}

void SListAppend(slist_ptr_t dest, slist_ptr_t src)
{
	slist_iter dest_dummy = SListEnd(dest);
	slist_iter src_head = SListBegin(src);
	slist_iter src_dummy = SListEnd(src);
	node_t *new_dummy = malloc(sizeof(node_t));
	if (NULL == new_dummy)
	{
		return;
	}

	dest_dummy->next = src_head;
	dest->tail = src_dummy;
	src_dummy->data = dest;
	SListRemove(dest_dummy);
	src->head = new_dummy;
	src->tail = new_dummy;
	new_dummy->data = src;
	new_dummy->next = NULL;
}
