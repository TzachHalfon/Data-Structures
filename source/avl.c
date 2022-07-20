/*============================LIBRARIES && MACROS =================================*/
#include <assert.h>  /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "avl.h"

#define SUCCESS 0 
#define FAIL 1
#define MAX(a,b) (((a) > (b))? (a) : (b))

/*================================= STRUCTS =======================================*/
typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_CHILDREN
}children_t;

typedef struct avl_node
{
    void *data;
    size_t height;
    struct avl_node *children[NUM_CHILDREN];
}avl_node_t;

struct avl
{
    avl_node_t *root;
    cmp_func_t cmp_func;
};

/*=========================== FUNCTION DECLARATION ================================*/
static avl_node_t *CreateNode(void *data);
static void DestroyNodesRec(avl_node_t *node);
static avl_node_t *InsertNodeRec(avl_node_t *node, avl_node_t *new, cmp_func_t cmp);
static avl_node_t *RemoveRec(avl_node_t *node, void *data, cmp_func_t cmp);
static size_t TreeSizeRec(avl_node_t *node);
static size_t UpdateNodeHeight(avl_node_t *node);
static void *FindRec(avl_node_t *node, cmp_func_t cmp, void *key);
static int ForEachIn(avl_node_t *node,action_func_t action,void *param);
static int ForEachPost(avl_node_t *node,action_func_t action,void *param);
static int ForEachPre(avl_node_t *node,action_func_t action,void *param);
static avl_node_t *FindMostLeftNode(avl_node_t *node);
static avl_node_t *BalanceTree(avl_node_t *node);
static avl_node_t *RotateRight(avl_node_t *node);
static avl_node_t *RotateLeft(avl_node_t *node);
static int GetHeight(avl_node_t *node, children_t dir);

/*============================= FUNCTION DEFINITION ==============================*/
/*
struct node not in h only in c
struct child not in h only in c
in insert make cure null after malloc is the first thing we check
make sure that in insert nad remove pepole do tree->root = ??
cmp func no more then once
*/
avl_t *AVLCreate(cmp_func_t cmp_func)
{
    avl_t *avl = (avl_t *)malloc(sizeof(avl_t));
    if(NULL == avl)
    {
        return (NULL);
    }

    avl->root = NULL;
    avl->cmp_func = cmp_func;

    return (avl);
}


void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);
    DestroyNodesRec(tree->root); 
    free(tree);
}


int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *new_node;

    assert(NULL != tree);

    new_node = CreateNode(data);
    if (new_node == NULL)
    {
        return (FAIL);
    }
    tree->root = InsertNodeRec(tree->root, new_node, tree->cmp_func);
    
    return (SUCCESS);
}


void AVLRemove(avl_t *tree, const void *key)
{
    assert(NULL != tree);
    tree->root = RemoveRec(tree->root, (void*)key, tree->cmp_func);
}


int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);
    return (tree->root == NULL);
}


size_t AVLSize(const avl_t *tree)
{
    assert(NULL != tree);
    return (TreeSizeRec(tree->root));
}


size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);
    if(NULL == tree->root)
    {
        return (0);
    }
    return (tree->root->height);
}


void *AVLFind(const avl_t *tree, const void *key)
{
    assert(NULL != tree);
    return FindRec(tree->root, tree->cmp_func, (void*)key);
}


int AVLForEach(avl_t *tree, action_func_t action_func, void *param, traverse_t type)
{
    assert(NULL != tree);
    assert(NULL != action_func);
    switch (type)
    {
    case IN_ORDER:
        return ForEachIn(tree->root, action_func, param);
        break;
    case PRE_ORDER:
        return ForEachPre(tree->root, action_func, param);
        break;
    case POST_ORDER:
        return ForEachPost(tree->root, action_func, param);
        break;
    default:
        return (FAIL);
    }
}

/*================================== STATIC FUNCTIONS ==========================================*/
static avl_node_t *CreateNode(void *data)
{
    avl_node_t *new_node = (avl_node_t*) malloc(sizeof(avl_node_t));
    if(NULL != new_node)
    {
        new_node->data = data;
        new_node->height = 1;
        new_node->children[LEFT] = NULL;
        new_node->children[RIGHT] = NULL;
    }
    return (new_node);
}

static void DestroyNodesRec(avl_node_t *node)
{
    if(node == NULL)
    {
        return;
    }
    DestroyNodesRec(node->children[LEFT]);
    node->children[LEFT] = NULL;

    DestroyNodesRec(node->children[RIGHT]);
    node->children[RIGHT] = NULL;
    
    free(node);
}


static avl_node_t *InsertNodeRec(avl_node_t *node, avl_node_t *new, cmp_func_t cmp)
{
    if(node == NULL)
    {
        return (new);
    }
    if(0 < cmp(node->data, new->data))
    {    
        node->children[LEFT] = InsertNodeRec(node->children[LEFT], new, cmp);
    }
    else
    {
        node->children[RIGHT] = InsertNodeRec(node->children[RIGHT], new, cmp);
    }
    node->height = UpdateNodeHeight(node);
    return (BalanceTree(node));
}


static avl_node_t *RemoveRec(avl_node_t *node, void *data, cmp_func_t cmp)
{
    int comp = 0;
    if (NULL == node)
    {
        return (node);
    }

    comp = cmp(data, node->data); 
    if(0 > comp)
    {    
        node->children[LEFT] = RemoveRec(node->children[LEFT], data, cmp);
    }
    else if(0 < comp)
    {
        node->children[RIGHT] = RemoveRec(node->children[RIGHT], data, cmp);
    } 
    else 
    {
        avl_node_t *tmp = NULL;
        if(NULL == node->children[LEFT] || NULL == node->children[RIGHT])
        {
            tmp = ((NULL == node->children[LEFT]) ? node->children[RIGHT] : node->children[LEFT]);
            free(node);
            return (tmp);
        }
        tmp = FindMostLeftNode(node->children[RIGHT]);
        node->data = tmp->data;
        node->children[RIGHT] = RemoveRec(node->children[RIGHT], tmp->data, cmp);
    }
    node->height = UpdateNodeHeight(node);
    return (BalanceTree(node));
}


static size_t TreeSizeRec(avl_node_t *node)
{
    if(node == NULL)
    {
        return (0);
    }
    return (1 + TreeSizeRec(node->children[LEFT]) + TreeSizeRec(node->children[RIGHT]));
}


static size_t UpdateNodeHeight(avl_node_t *node)
{
    int left = GetHeight(node,LEFT);
    int right = GetHeight(node, RIGHT);
    return (MAX(left, right) + 1);
}

static int GetHeight(avl_node_t *node, children_t dir) 
{
    return ((NULL == node->children[dir])? 0 : node->children[dir]->height);
}

static avl_node_t *FindMostLeftNode(avl_node_t *node)
{
    if(node->children[LEFT] == NULL)
    {
        return (node);
    }
    return (FindMostLeftNode(node->children[LEFT]));
}


static void *FindRec(avl_node_t *node, cmp_func_t cmp, void *key)
{
    int comp = 0;
    if(node == NULL)
    {
        return (NULL);
    }
    comp = cmp(node->data, key);
    if(comp == 0)
    {
        return ((node == NULL)? NULL : node->data);
    }
    
    if(comp > 0)
    {
        return (FindRec(node->children[LEFT], cmp, key));
    }

    return (FindRec(node->children[RIGHT], cmp, key));
    
}


static int ForEachIn(avl_node_t *node,action_func_t action,void *param)
{
    if(node == NULL)
    {
        return (SUCCESS);
    }
    if(SUCCESS != ForEachIn(node->children[LEFT], action, param))
    {
        return (FAIL);
    }
    if(SUCCESS != action(node->data, param))
    {
        return (FAIL);
    }
    if(SUCCESS != ForEachIn(node->children[RIGHT], action, param))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

static int ForEachPost(avl_node_t *node,action_func_t action,void *param)
{
    if(node == NULL)
    {
        return (SUCCESS);
    }
    if(SUCCESS != ForEachPost(node->children[LEFT], action, param))
    {
        return (FAIL);
    }
    if(SUCCESS != ForEachPost(node->children[RIGHT], action, param))
    {
        return (FAIL);
    }
    if(SUCCESS != action(node->data, param))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

static int ForEachPre(avl_node_t *node,action_func_t action,void *param)
{
    if(node == NULL)
    {
        return (SUCCESS);
    }
    if(SUCCESS != action(node->data, param))
    {
        return (FAIL);
    }
    if(SUCCESS != ForEachPre(node->children[LEFT], action, param))
    {
        return (FAIL);
    }
    if(SUCCESS != ForEachPre(node->children[RIGHT], action, param))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

static avl_node_t *BalanceTree(avl_node_t *node)
{
    int left_height = GetHeight(node, LEFT);
    int right_height = GetHeight(node, RIGHT);
    if((left_height - right_height) > 1)
    {
        if((GetHeight(node->children[LEFT], RIGHT) - (GetHeight(node->children[LEFT], LEFT))) > 0)
        {
            node->children[LEFT] = RotateLeft(node->children[LEFT]);
        }
        return (RotateRight(node));
    }
    if((right_height - left_height) > 1)
    {
        if((GetHeight(node->children[RIGHT], LEFT) - (GetHeight(node->children[RIGHT], RIGHT))) > 0)
        {
            node->children[RIGHT] = RotateRight(node->children[RIGHT]);
        }
        return (RotateLeft(node));
    }
    return (node);
}

static avl_node_t *RotateRight(avl_node_t *node)
{
    avl_node_t *new_sub_root = node->children[LEFT];
    node->children[LEFT] = new_sub_root->children[RIGHT];
    new_sub_root->children[RIGHT] = node;
    node->height = UpdateNodeHeight(node);
    new_sub_root->height = UpdateNodeHeight(new_sub_root);
    return (new_sub_root);
}

static avl_node_t *RotateLeft(avl_node_t *node)
{
    avl_node_t *new_sub_root = node->children[RIGHT];
    node->children[RIGHT] = new_sub_root->children[LEFT];
    new_sub_root->children[LEFT] = node;
    node->height = UpdateNodeHeight(node);
    new_sub_root->height = UpdateNodeHeight(new_sub_root);
    return (new_sub_root);
}