/*============================LIBRARIES && MACROS ================================*/
#include <stdio.h>

#include "binary_tree.h"

#define MIN(a,b) (((a) < (b))? (a) : (b))

/*========================== FUNCTION DECLARATION ================================*/
void TestFuncs(void);

int TestCreate(void);
int TestInsert(void);
int TestBeginAndEnd(void);
int TestForEach(void);
int TestFind(void);

int AddTwo(void *data, void *param);
int CompareInts(const void *data1,const void *data2);
/*============================= FUNCTION DEFINITION ==============================*/

int main(void)
{
    TestFuncs();
    return 0;
}


void TestFuncs(void)
{
    int status = 1;
    int prev_status = 1;
    printf("~~~STARTING TESTS ALL FUNCS~~~\n");
    /*
    prev_status = TestCreate();
    status = MIN(status, prev_status);
    
    prev_status = TestBeginAndEnd();
    status = MIN(status, prev_status);
    */
    prev_status = TestInsert();
    status = MIN(status, prev_status);
    /*
    prev_status = TestFind();
    status = MIN(status, prev_status);
    
    
    prev_status = TestForEach();
    status = MIN(status, prev_status);
    */
    if (status == 1)
    {
        printf("ALL TESTS FINISHED SUCCESSFULLY\n");
    }
    printf("~~~FINSIHED TESTS ALL FUNCS~~~\n");
    printf("~~~~~~~~~RUN VLAGRIND~~~~~~~~~\n");
}

int TestCreate(void)
{
    int status = 1;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    
    if (tree == NULL)
    {
        status = 0;
        printf("BinaryTreeCreate didnt work!\n");
    }

    BinaryTreeDestroy(tree);
    return (status);
}

int TestInsert(void)
{
    int status = 1;
    int values[4] = {6,3,8,9}; 
    int i = 0;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    binary_tree_iterator_t iter;
    for (i = 0; i < 4; ++i)
    {
        if(NULL == BinaryTreeInsert(tree,&values[i]))
        {
            status = 0;
            printf("BinaryTreeInsert didn't work!\n");
            break;
        }
    }
    iter = BinaryTreeBegin(tree);
    iter = BinaryTreeNext(iter);
    if(6 != *(int *)BinaryTreeGetData(iter))
    {
        status = 0;
        printf("BinaryTreeNext didn't work!\n");
    }

    iter = BinaryTreePrev(iter);
    if(3 != *(int *)BinaryTreeGetData(iter))
    {
        status = 0;
        printf("BinaryTreePrev didn't work!\n");
    }



    BinaryTreeDestroy(tree);
    return (status);
}


int TestBeginAndEnd(void)
{
    int status = 1;
    int value = 6;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    binary_tree_iterator_t iter = BinaryTreeInsert(tree,&value);
    
    if(iter != BinaryTreeBegin(tree))
    {
        status = 0;
        printf("BinaryTreeBegin didn't work!\n");
    }
    if(iter == BinaryTreeEnd(tree))
    {
        status = 0;
        printf("BinaryTreeBegin didn't work!\n");
    }

    BinaryTreeDestroy(tree);
    return (status);
}

int TestSize(void)
{
    int status = 1;
    int values[3] = {6,3,8};
    int i = 0;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    for (i = 0; i < 3; ++i)
    {
        if(NULL == BinaryTreeInsert(tree,&values[i]))
        {
            status = 0;
            printf("BinaryTreeInsert didn't work!\n");
            break;
        }
    }
    if(3 != BinaryTreeSize(tree))
    {
        status = 0;
        printf("BinaryTreeSize didn't work!\n");
    }

    BinaryTreeDestroy(tree);
    return status;
}

int TestForEach(void)
{
    int status = 1;
    int values[3] = {6,3,8};
    int i = 0;
    int param = 2;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    
    for (i = 0; i < 3; ++i)
    {
        if(NULL == BinaryTreeInsert(tree,&values[i]))
        {
            status = 0;
            printf("BinaryTreeInsert didn't work!\n");
            break;
        }
    }
    BinaryTreeForEach(BinaryTreeBegin(tree), BinaryTreeNext(BinaryTreeBegin(tree)),AddTwo , (void *)&param);

    if(5 != *(int*)BinaryTreeGetData(BinaryTreeBegin(tree)))
    {
        status = 0;
        printf("BinaryTreeForEach didn't work!\n");
    }

    BinaryTreeDestroy(tree);
    return status;
}

int TestFind(void)
{   
    int status = 1;
    int values[3] = {6,3,8};
    int i = 0;
    binary_tree_t *tree = BinaryTreeCreate(CompareInts);
    for (i = 0; i < 3; ++i)
    {
        if(NULL == BinaryTreeInsert(tree,&values[i]))
        {
            status = 0;
            printf("BinaryTreeInsert didn't work!\n");
            break;
        }
    }

    if(6 != *(int*)BinaryTreeGetData(BinaryTreeFind(tree, (void *)&values[0])))
    {
        status = 0;
        printf("BinaryTreeFind didn't work!\n");
    }
    BinaryTreeDestroy(tree);
    return status;
}


int CompareInts(const void *data1, const void *data2)
{
    return (*(int *)data1 > *(int *)data2);
}

int AddTwo(void *data, void *param)
{
    *(int*)data += *(int*)param;
    return 0;
}