/*=============================== LIBRARIES ==================================*/
#include <assert.h>  /*assert*/
#include <stdio.h>  /*assert*/
#include <stddef.h>/*size_t*/

/*============================== DECLARATIONS ================================*/
#define MIN(a,b) (a>b)? a : b
typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef node_t* node_ptr_t;


node_ptr_t Flip(node_ptr_t head);
int HasLoop(const node_ptr_t head);
node_ptr_t FindIntersection(node_ptr_t head_1, node_ptr_t head_2);
static node_ptr_t FindTail(size_t *count, node_ptr_t runner);
static int FlipCheck();
static int FindInterCheck();
static int HasLoopCheck();

/*========================== FUNCTION DEFINITIONS ============================*/

int main(void)
{
    int status = 0;

    status = FlipCheck();
    status = MIN(status, FindInterCheck());
    status = MIN(status, HasLoopCheck());

    if(status == 0)
    {
        printf("All functions worked\n");
    }

    return (status);
}

static int FlipCheck()
{
	int nums[7] = {1-7};
	int i = 0;
	node_t nodes[7];
    node_ptr_t head;
	
	for(i = 0;i < 7; ++i)
	{
		nodes[i].data = (void*)&nums[i];
		nodes[i].next = &nodes[i + 1];
	}
	
	nodes[4].next = NULL;
	nodes[6].next = NULL;
    head = &nodes[0];

	head = Flip(head);
    
    if(!((*(int*)head->data == *(int*)nodes[3].data) && 
    (*(int*)head->next->data == *(int*)nodes[2].data)))
    {
        printf("Flip NOT Working!\n");
        return (1);
    }
    else
    {
        return (0);
    }
}

static int FindInterCheck()
{
    size_t i = 0;
    size_t j = 0;
    int data_array1[5] = {1, 2, 3, 4, 5};
    int data_array2[10] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int inter = 5;
    node_t node_array1[5];
    node_t node_array2[10];

    node_t *head1= NULL;
    node_t *head2 = NULL;
    node_t *mutual_node = NULL;
	
    for (i = 0, j = 5; j < 10; ++i, ++j)
    {
        node_array1[i].data = &data_array1[i];
        node_array1[i].next = &node_array1[i+1];
        node_array2[i].data = &data_array2[i];
        node_array2[i].next = &node_array2[i+1];
        node_array2[j].data = &data_array2[j];
        node_array2[j].next = &node_array2[j+1];
    }
    
    node_array1[4].next = &node_array2[inter];
    node_array2[9].next = NULL;

    head1 = node_array1;
    head2 = node_array2;

    mutual_node = FindIntersection(head1, head2);

    if(!((&node_array2[inter] == mutual_node)))
    {
        printf("FindIntersection NOT Working!\n");
        return (1);
    }
    else
    {
        return (0);
    }
}

static int HasLoopCheck()
{
    size_t i = 0;
    int data_array1[5] = {1, 2, 3, 4, 5};
    node_t node_array1[5];
    node_t *head = NULL;

    for (i = 0; i < 5; ++i)
    {
        node_array1[i].data = &data_array1[i];
        node_array1[i].next = &node_array1[i+1];
    }
    
    node_array1[4].next = &node_array1[2];
    head = node_array1;

    if(!(1 == HasLoop(head)))
    {
        printf("HasLoop NOT Working!\n");
        return (1);
    }
    else
    {
        return (0);
    }
}


node_ptr_t Flip(node_ptr_t head)
{
    node_ptr_t next;
    node_ptr_t after;
    node_ptr_t curr = NULL;

    assert(NULL != head);

    next = head;
    after = head->next;
    
    next->next = NULL;
    
    while(NULL != after)
    {
        curr = next;
        next = after;
        after = next->next;
        next->next = curr;
    }
    
    return (next);
}


int HasLoop(const node_ptr_t head)
{
    node_ptr_t two_jumps_ptr;
    node_ptr_t one_jumps_ptr;

    assert(NULL != head);

	two_jumps_ptr = head;
    one_jumps_ptr = head;

    while(NULL != two_jumps_ptr && NULL != two_jumps_ptr->next)
    {
        one_jumps_ptr = one_jumps_ptr->next;
        two_jumps_ptr = two_jumps_ptr->next->next;
        
        if(two_jumps_ptr == one_jumps_ptr)
        {
            return (1);
        }
    }

    return (0);
}



node_ptr_t FindIntersection(node_ptr_t head_1, node_ptr_t head_2)
{
	node_ptr_t node_runner_1;
    node_ptr_t node_runner_2;
    size_t count_list_1 = 0;
    size_t count_list_2 = 0;

    assert(NULL != head_1);
    assert(NULL != head_2);

    node_runner_1 = head_1;
    node_runner_2 = head_2;


    if(FindTail(&count_list_1, head_1) != FindTail(&count_list_2, head_2))
    {
        return (NULL);
    }

    while(count_list_1 != count_list_2)
    {
        if(count_list_1 > count_list_2)
        {
            --count_list_1;
            node_runner_1 = node_runner_1->next;
        }
        else
        {
            --count_list_2;
            node_runner_2 = node_runner_2->next;
        }
    }

    while(node_runner_1 != node_runner_2)
    {
        node_runner_1 = node_runner_1->next;
        node_runner_2 = node_runner_2->next;
    }

    return (node_runner_1);
}

static node_ptr_t FindTail(size_t *count,node_ptr_t runner)
{
    assert(NULL != count);
    assert(NULL != runner);
    
    *count = 0;

    while(runner->next != NULL)
    {
        runner = runner->next;
        ++*count;
    }

    return (runner);
}
