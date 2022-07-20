/*============================LIBRARIES && MACROS =================================*/
#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/
#include <math.h>	/*pow sqrt*/

#include "dlist.h"
#include "hasht.h"

#define FAIL 1
#define SUCCESS 0

/*
	ask everyone time complexity of find, insert, remove (Average and worst).space complexity.
								time o(1) with worst o(n) n - num of element in one list
								space o(n + k)
	destroy function
	n - num of elements in alllll of hash table
	k - num of lists

	lazy initialization - option for creating list only when needed

	destory make loop diff func
 */
/*================================= STRUCTS =======================================*/
struct hasht
{
	hash_func_t hash_func; /* hash for key to index */
	hash_is_match_t cmp_func;
	size_t expected_capacity;
	dlist_t **table;
};

/*=========================== FUNCTION DECLARATION ================================*/
static size_t GetHashIndex(hasht_t *table, void *data);
static void DestroyLists(hasht_t *table, size_t to);

/*============================= FUNCTION DEFINITION ==============================*/
hasht_t *HashtCreate(size_t expected_capacity, hash_is_match_t cmp_func, hash_func_t hash_func)
{
	int i = 0;
	hasht_t *hash = (hasht_t *)malloc(sizeof(hasht_t));
	if (hash == NULL)
	{
		return (NULL);
	}

	hash->table = (dlist_t **)malloc(expected_capacity * sizeof(dlist_t *));
	if (hash->table == NULL)
	{
		free(hash);
		return (NULL);
	}

	for (i = 0; i < (int)expected_capacity; ++i)
	{
		hash->table[i] = DoublyListCreate();
	}
	if (i != (int)expected_capacity)
	{
		DestroyLists(hash, i - 1);
		free(hash->table);
		free(hash);
		return (NULL);
	}
	hash->cmp_func = cmp_func;
	hash->hash_func = hash_func;
	hash->expected_capacity = expected_capacity;

	return (hash);
}

void HashtDestroy(hasht_t *table)
{
	DestroyLists(table, table->expected_capacity);
	free(table->table);
	free(table);
}

int HashtInsert(hasht_t *table, void *data)
{
	dlist_t *to_insert;
	assert(NULL != table);
	to_insert = table->table[GetHashIndex(table, data)];
	if (DoublyListPushFront(to_insert, data) != DoublyListEnd(to_insert))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

void HashtRemove(hasht_t *table, void *key)
{
	dlist_t *found_list;
	dlist_iter_t tmp_to_remove;
	assert(NULL != table);
	found_list = table->table[GetHashIndex(table, key)];
	tmp_to_remove = DoublyListFind(DoublyListBegin(found_list), DoublyListEnd(found_list), table->cmp_func, key);
	if (!DoublyListIsSameIter(tmp_to_remove, DoublyListEnd(found_list)))
	{
		DoublyListRemove(tmp_to_remove);
	}
}

int HashtIsEmpty(const hasht_t *table)
{
	size_t i = 0;

	for (i = 0; i < table->expected_capacity; ++i)
	{
		if (!DoublyListIsEmpty(table->table[i]))
		{
			return (FAIL);
		}
	}

	return (SUCCESS);
}

size_t HashtSize(const hasht_t *table)
{
	size_t i = 0;
	size_t size = 0;
	for (i = 0; i < table->expected_capacity; ++i)
	{
		size += DoublyListSize(table->table[i]);
	}
	return (size);
}

int HashtForEach(hasht_t *table, action_func_t action_func, void *param)
{
	size_t i = 0;
	int status = 0;
	assert(NULL != table);
	assert(NULL != action_func);
	for (i = 0; i < table->expected_capacity && status != FAIL; ++i)
	{
		status = DoublyListForEach(DoublyListBegin(table->table[i]), DoublyListEnd(table->table[i]), action_func, param);
	}

	return (status);
}

void *HashtFind(const hasht_t *table, const void *key)
{
	dlist_t *find_from = NULL;
	dlist_iter_t found = NULL;
	void *data = NULL;

	assert(NULL != table);

	find_from = table->table[GetHashIndex((hasht_t *)table, (void *)key)];
	found = DoublyListFind(DoublyListBegin(find_from), DoublyListEnd(find_from), table->cmp_func, key);
	data = DoublyListGetData(found);
	if (!DoublyListIsSameIter(DoublyListEnd(find_from), found))
	{
		DoublyListRemove(found);
		DoublyListPushFront(find_from, data);
	}
	return (data);
}

double HashtLoad(const hasht_t *table)
{
	assert(NULL != table);
	return (((double)HashtSize(table) / (double)table->expected_capacity));
}

double HashtStandardDeviation(const hasht_t *table)
{
	size_t i = 0;
	double size = 0;
	double load;

	assert(NULL != table);

	load = HashtLoad(table);
	for (i = 0; i < table->expected_capacity; ++i)
	{
		size += pow((DoublyListSize(table->table[i]) - load), 2);
	}

	return (sqrt(size / (double)table->expected_capacity));
}

static size_t GetHashIndex(hasht_t *table, void *data)
{
	return ((table->hash_func(data)) % table->expected_capacity);
}

static void DestroyLists(hasht_t *table, size_t to)
{
	size_t i = 0;
	for (i = 0; i < to; ++i)
	{
		DoublyListDestroy(table->table[i]);
	}
}