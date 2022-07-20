/*============================LIBRARIES && MACROS ================================*/
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include "binary_tree.h"

/*================================ STRUCTS =======================================*/
typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_CHILDREN

}children_t;

typedef struct binary_tree_node tree_node_t;
struct binary_tree_node
{
	void *data;
	tree_node_t *parent;
	tree_node_t *children[NUM_CHILDREN];
};

struct binary_tree
{
    tree_node_t dummy;
	compare_t compare_func;
};
/*========================== FUNCTION DECLARATION ================================*/
static tree_node_t *GoToDirection(const binary_tree_t *binary_tree,tree_node_t *runner, void *data);
static binary_tree_iterator_t NodeToIter(tree_node_t *node);
static tree_node_t *IterToNode(binary_tree_iterator_t iter);
static void InitializeChilderns(tree_node_t *node);
static tree_node_t *CreateNode(void *data);

/*============================= FUNCTION DEFINITION ==============================*/
/*
	do outsoure to node create
	dummy == runner or is iter equal with runner and end what is better
	what kind of order you do in destroy?
	do itertonode and nodetoiter
	return dummy or end on error (its the same)
	remove in o(1)
	macro for 1 and 0	
*/

binary_tree_t *BinaryTreeCreate(compare_t compare_func)
{
	binary_tree_t *tree = (binary_tree_t *)malloc(sizeof(binary_tree_t));
	if(NULL == tree)
	{
		return NULL;
	}

	tree->compare_func = compare_func;
	tree->dummy.data = NULL;
	tree->dummy.parent = NULL;
	InitializeChilderns(&tree->dummy);

	return (tree);
}


void BinaryTreeDestroy(binary_tree_t *binary_tree)
{
	tree_node_t *runner;
	tree_node_t *runner_next;
	
	assert(NULL != binary_tree);

	if(NULL != binary_tree->dummy.children[LEFT])
	{
		runner = BinaryTreeBegin(binary_tree);
		while (NULL != runner && &binary_tree->dummy != runner)
		{	
			runner_next = BinaryTreeNext(runner);
			BinaryTreeRemove(runner);
			runner = runner_next;
		}
	}
	free(binary_tree);
}


binary_tree_iterator_t BinaryTreeInsert(binary_tree_t *binary_tree, void *data)
{
	tree_node_t *runner_parent = NULL;
	tree_node_t *runner = NULL;
	tree_node_t *new_node = CreateNode(data);
	InitializeChilderns(new_node);

	assert(NULL != binary_tree);

	runner_parent = binary_tree->dummy.children[LEFT];
	runner = runner_parent;
	
	if (NULL == new_node)
	{
		return BinaryTreeEnd(binary_tree);
	}

	if(NULL == runner)
	{
		binary_tree->dummy.children[LEFT] = new_node;
		new_node->parent = &binary_tree->dummy;
	}
	else
	{
	
		while (NULL != runner) 
		{
			runner_parent = runner;
			runner = GoToDirection(binary_tree, runner, data);
		}

		if (0 < binary_tree->compare_func(data, BinaryTreeGetData(runner_parent)))
		{
			runner_parent->children[RIGHT] = new_node;
		}
		else
		{
			runner_parent->children[LEFT] = new_node;
		}
		
		new_node->parent = runner_parent;
	}
	return(NodeToIter(new_node));
}
    


void BinaryTreeRemove(binary_tree_iterator_t iter)
{
	tree_node_t *iter_node;
	tree_node_t *tmp;
	assert(NULL != iter);

	iter_node = IterToNode(iter);
	if(NULL != iter_node->children[RIGHT] && NULL != iter_node->children[LEFT])
    {
        tmp = BinaryTreeNext(iter_node);
        iter_node->data = BinaryTreeGetData(tmp);
        iter_node = tmp;
    }
    tmp = (NULL == iter_node->children[LEFT]) ? iter_node->children[RIGHT] : iter_node->children[LEFT];
    
	if(iter_node->parent->children[RIGHT] == iter_node)
    {
        iter_node->parent->children[RIGHT] = tmp;
    }
    else
    {
        iter_node->parent->children[LEFT] = tmp;
    }

    if(NULL != tmp)
    {
        tmp->parent = iter_node->parent;
    }

	free(iter_node);
}

binary_tree_iterator_t BinaryTreeNext(binary_tree_iterator_t iter)
{
	tree_node_t *node_iter;
	tree_node_t *to_return = NULL;

	assert(NULL != iter);

	node_iter = IterToNode(iter);
	if(node_iter->children[RIGHT] != NULL)
	{
		node_iter = node_iter->children[RIGHT];
		while (node_iter->children[LEFT] != NULL)
		{
			node_iter = node_iter->children[LEFT];
		}
		to_return = node_iter;
		
	}
	else
	{
		while (NULL != node_iter->parent->parent && node_iter == node_iter->parent->children[RIGHT])
		{
			node_iter = node_iter->parent;
		}
		to_return = node_iter->parent;
	}

	return (NodeToIter(to_return));
}


binary_tree_iterator_t BinaryTreePrev(binary_tree_iterator_t iter)
{
	tree_node_t *node_iter;
	tree_node_t *to_return = NULL;

	assert(NULL != iter);

	node_iter = IterToNode(iter);
	if(node_iter->children[LEFT] != NULL)
	{
		node_iter = node_iter->children[LEFT];
		while (node_iter->children[RIGHT] != NULL)
		{
			node_iter = node_iter->children[RIGHT];
		}
		to_return = node_iter;
	}
	else
	{
		while(node_iter->parent->children[LEFT] == node_iter && node_iter->parent->parent != NULL)
		{
			node_iter = node_iter->parent;
		}
		to_return = node_iter->parent;
	}
	return (NodeToIter(to_return));
}


binary_tree_iterator_t BinaryTreeBegin(const binary_tree_t *binary_tree)
{
	tree_node_t *runner;
	assert(NULL != binary_tree);
	runner = binary_tree->dummy.children[LEFT];
	
	if(NULL != runner)
	{
		while (runner->children[LEFT] != NULL)
		{
			runner = runner->children[LEFT];
		}
	}
	return (NodeToIter(runner));
}


binary_tree_iterator_t BinaryTreeEnd(const binary_tree_t *binary_tree)
{
	assert(NULL != binary_tree);
	return ((binary_tree_iterator_t)&binary_tree->dummy);
}


void *BinaryTreeGetData(const binary_tree_iterator_t iter)
{
	tree_node_t *node;
	assert(NULL != iter);
	node = IterToNode(iter);

	return (node->data);
}


int BinaryTreeIsEmpty(const binary_tree_t *binary_tree)
{
	assert(NULL != binary_tree);
	return (NULL == binary_tree->dummy.children[LEFT]);
}


int BinaryTreeIsIterEqual(const binary_tree_iterator_t iter_one, const binary_tree_iterator_t iter_two)
{
	tree_node_t *node_one;
	tree_node_t *node_two;

	assert(NULL != iter_one);
	assert(NULL != iter_two);

	node_one = IterToNode(iter_one);
	node_two = IterToNode(iter_two);

	return (node_one == node_two);
}


size_t BinaryTreeSize(const binary_tree_t *binary_tree)
{
	tree_node_t *runner;
	size_t count = 0;
	assert(NULL != binary_tree);
	runner = BinaryTreeBegin(binary_tree);

	while (runner != NULL && runner != BinaryTreeEnd(binary_tree))
	{
		++count;
		runner = BinaryTreeNext(runner);
	}

	return (count);
	
}



int BinaryTreeForEach(binary_tree_iterator_t from,
					  binary_tree_iterator_t to, 
					  action_t action_func,
					  void *param)
{
	int status = 0;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);

	while (!BinaryTreeIsIterEqual(from, to) && status != 1)
	{	
		status = action_func(from->data,param);
		from = BinaryTreeNext(from);
	}
	
	return (status);
}

binary_tree_iterator_t BinaryTreeFind(const binary_tree_t *binary_tree, void *key_to_data)
{
	tree_node_t *runner = NULL;
	void *data;

	assert(NULL != binary_tree);
	
	runner = binary_tree->dummy.children[LEFT];
	data = runner->data;
	
	while (runner != NULL && binary_tree->compare_func(data, key_to_data) != 0)
	{
		data = runner->data;
		runner = GoToDirection(binary_tree, runner,key_to_data);
	}

	if (runner == NULL)
	{
		runner = BinaryTreeEnd(binary_tree);
	}
	
	return (NodeToIter(runner));
}


static tree_node_t *CreateNode(void *data)
{
	tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	InitializeChilderns(new_node);

	return (new_node);
}

static void InitializeChilderns(tree_node_t *node)
{
	int i = 0;
	for (i = 0; i < NUM_CHILDREN; i++) 
	{
		node->children[i] = NULL;
	}
}


static tree_node_t *IterToNode(binary_tree_iterator_t iter)
{
    return ((tree_node_t *)iter);
}

static binary_tree_iterator_t NodeToIter(tree_node_t *node)
{
    return (node);
}

static tree_node_t *GoToDirection(const binary_tree_t *binary_tree, tree_node_t *runner, void *data)
{
	if(binary_tree->compare_func(runner->data, data) > 0)
	{
		runner = runner->children[LEFT];
	}
	else
	{
		runner = runner->children[RIGHT];
	}
	
	return (runner);
}