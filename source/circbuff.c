#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free, abs*/
#include <math.h>

#include "../include/circbuff.h"

#define FAIL -1
#define ELEM_NUM_OFFSET 8
#define OFFSETOF(TYPE, ELEMENT) (&(((TYPE *)0)->ELEMENT))

typedef struct circbuff
{
    size_t read_index;
    size_t write_index;
    size_t capacity;
    size_t buff[1];

}cb_t;


circbuff_ptr_t CircBuffCreate(size_t capacity)
{
    circbuff_ptr_t circbuff = (circbuff_ptr_t)malloc(sizeof(cb_t) + capacity);
    
    if(NULL == circbuff)
    {
        return (NULL);
    }

    circbuff->capacity = capacity;
    circbuff->read_index  = ELEM_NUM_OFFSET;
    circbuff->write_index = ELEM_NUM_OFFSET;
    circbuff->buff[0] = 0;
    
    return (circbuff);
}


void CircBuffDestroy(circbuff_ptr_t buffer)
{
    assert(NULL != buffer);
    free(buffer);
}



ssize_t CircBuffWrite(circbuff_ptr_t buffer, const void *to_read_from, size_t num_of_bytes)
{
    size_t counter = num_of_bytes;
    char *read_from;
    char *runner;

    if(NULL == buffer || NULL == to_read_from)
    {
        return (FAIL);
    }

    read_from = (char *)to_read_from;
    runner = (char *)buffer->buff;

    while(0 != num_of_bytes)
    {
        runner[buffer->write_index] = *read_from;
        ++read_from;
        ++buffer->write_index;
        --num_of_bytes;

        if(buffer->capacity == buffer->write_index - ELEM_NUM_OFFSET)
        {
            buffer->write_index = ELEM_NUM_OFFSET;
        }

        if(buffer->buff[0] < buffer->capacity)
        {
            ++buffer->buff[0];
        }
    }

    return (counter);
}


ssize_t CircBuffRead(circbuff_ptr_t buffer, void *to_write_to, size_t num_of_bytes)
{
    size_t counter = num_of_bytes;
    char *write_to;
    char *runner;

    if(NULL == buffer || NULL == to_write_to)
    {
        return (FAIL);
    }

    write_to = (char *)to_write_to;
    runner = (char *)buffer->buff;

    while(0 != num_of_bytes && 0 == CircBuffIsEmpty(buffer))
    {
        *write_to = runner[buffer->read_index];
        ++write_to;
        ++buffer->read_index;
        --num_of_bytes;
        ++counter;
        --buffer->buff[0];
        
        if(buffer->capacity == buffer->read_index - ELEM_NUM_OFFSET)
        {
            buffer->read_index = ELEM_NUM_OFFSET;
        }
    }
    
    return (counter);
}

size_t CircBuffFreeSpace(const circbuff_ptr_t buffer)
{
    assert(NULL != buffer);
    return (buffer->capacity - CircBuffSize(buffer));
}


int CircBuffIsEmpty(const circbuff_ptr_t buffer)
{
    assert(NULL != buffer);
    return(0 == CircBuffSize(buffer));
}


size_t CircBuffSize(const circbuff_ptr_t buffer)
{  
    assert(NULL != buffer);
    return (buffer->buff[0]);
}
