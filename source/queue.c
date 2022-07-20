#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "../include/slist.h" 
/*SListCreate,SListDestroy,SListInsertBefore,SListEnd,SListBegin,SListAppend */
#include "../include/queue.h"


typedef struct queue
{
    slist_ptr_t slist;
    size_t size;

}q_t;
 

queue_ptr_t QCreate(void)
{
    queue_ptr_t q = (queue_ptr_t)malloc(sizeof(q_t));
    if(NULL == q)
    {
        return (NULL);
    }

    q->slist = SListCreate();
    if(NULL == q->slist)
    {
        free(q);
        return (NULL);
    }

    q->size = 0;

    return (q);
}


void QDestroy(queue_ptr_t queue)
{
    assert(NULL != queue);

    SListDestroy(queue->slist);
    free(queue);
}


q_status_t QEnQueue(queue_ptr_t queue, const void *element)
{
    slist_iter end;

    assert(NULL != queue);

    end = SListInsertBefore(SListEnd(queue->slist), element);
    if(NULL == end)
    {
        return (FAIL);
    }
    ++queue->size;
    return (SUCCESS);
}


void QDeQueue(queue_ptr_t queue)
{
    assert(NULL != queue);
    SListRemove(SListBegin(queue->slist));
    --queue->size;

}


void *QPeek(const queue_ptr_t queue)
{
    assert(NULL != queue);
    return ((void*)SListGetData(SListBegin(queue->slist)));
}


void QAppend(queue_ptr_t qdest, queue_ptr_t qsrc)
{
    assert(NULL != qdest);
    assert(NULL != qsrc);
    qdest->size += qsrc->size;
    qsrc->size = 0;
    SListAppend(qdest->slist , qsrc->slist);

}


size_t QGetSize(const queue_ptr_t queue)
{
    assert(NULL != queue);
    return (queue->size);
}


int QIsEmpty(const queue_ptr_t queue)
{
    assert(NULL != queue);
    return (queue->size == 0);
}