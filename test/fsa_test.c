#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "fsa.h"

#define MIN(a,b) ((a < b)? a : b)

static void TestAllFuncs();
static int TestSuggestSize();
static int TestInit();
static int TestAlloc();
static int TestFree();
static int TestCountFree();

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	int status = 1;
	printf("     ~START OF TEST FUNCTION~ \n");
	
	status = MIN(TestSuggestSize(), status);
	status = MIN(TestInit(), status);
	status = MIN(TestAlloc(), status);
	status = MIN(TestFree(), status);
	status = MIN(TestCountFree(), status);
	status = MIN(TestSuggestSize(), status);
	
	if(status == 1)
	{
		printf("    ~ALL FINISHED SUCCESSFULLY~ \n");
	}
	    printf("      ~END OF TEST FUNCTION~ \n");
}

static int TestSuggestSize()
{
	size_t block_size1 = 15;
	size_t block_size2 = 16;
	size_t block_size3 = 17;
	size_t num_of_blocks = 4;
	size_t should_suggest1 = 80;
	size_t should_suggest2 = 112;
	size_t suggested1 = FSASuggestSize( block_size1 ,num_of_blocks);
	size_t suggested2 = FSASuggestSize(block_size2 ,num_of_blocks);
	size_t suggested3 = FSASuggestSize(block_size3 ,num_of_blocks);
	int status = 1;
	
	if(!(suggested1 == should_suggest1 && suggested2 == should_suggest1 && suggested3 == should_suggest2))
	{
		printf("FSASuggestSize NOT working!                          X\n");
		printf("suggested : %ld should_suggest :%ld\n",suggested1,should_suggest1);
		printf("suggested : %ld should_suggest :%ld\n",suggested2, should_suggest1);
		printf("suggested : %ld should_suggest :%ld\n",suggested3, should_suggest2);
		status = 0;
	}
	
	return (status);
}

static int TestInit()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FSASuggestSize(block_size, num_of_blocks);
	size_t counter = 0;
	int  status = 1;
	fsa_t *fsa = NULL;
	
	void* pool = malloc(pool_size);
	
	fsa = FSAInit(pool, pool_size, block_size);
	
	while(NULL != FSAAllocate(fsa))
	{
		++counter;
	}
	
	if(!(num_of_blocks == counter))
	{
		printf("FSAInit NOT working!\n");
		status = 0;
	}
	
	free(pool);
	
	return (status);
}

static int TestAlloc()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FSASuggestSize(block_size, num_of_blocks);
	size_t addresses[4] = {0};
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	
	void* pool = malloc(pool_size);
	
	fsa = FSAInit(pool, pool_size, block_size);
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		addresses[i] = (size_t)FSAAllocate(fsa);
	}
	
	if(NULL != FSAAllocate(fsa))
	{
		is_working = 0;
	}
	
	for(i = 0; i < (num_of_blocks - 1) && is_working == 1; ++i)
	{
		if(block_size != addresses[i+1] - addresses[i])
		{
			is_working = 0;
			break;
		}
	}
	
	if(0 == is_working)
	{
		printf("FSAAllocate NOT working!\n");
	}
	
	free(pool);
	return is_working;
}

static int TestFree()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FSASuggestSize(block_size, num_of_blocks);
	void* allocated[4];
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	
	void* pool = malloc(pool_size);
	
	fsa = FSAInit(pool, pool_size, block_size);
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		allocated[i] = FSAAllocate(fsa);
	}
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		FSAFree(fsa, allocated[i]);
	}
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		if(NULL == FSAAllocate(fsa))
		{
			is_working = 0;
		}
	}
	
	if(0 == is_working)
	{
		printf("FSAFree NOT working!\n");
	}
	
	free(pool);
	return is_working;
}

static int TestCountFree()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FSASuggestSize(block_size, num_of_blocks);
	size_t counters[5] = {0};
	void* not_important = NULL;
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	size_t tester = 5;
	
	void* pool = malloc(pool_size);
	
	fsa = FSAInit(pool, pool_size, block_size);
	
	for(; i < (num_of_blocks + 1); ++i)
	{
		counters[i] = FSACountFree(fsa);
		not_important = FSAAllocate(fsa);
		(void) not_important;
	}
	
	for(i = 0; i < 5; ++i)
	{
		--tester;
		if(tester != counters[i])
		{
			is_working = 0;
			break;
		}
	}
	
	if(0 == is_working)
	{
		printf("FSACountFree NOT working!\n");
	}
	
	free(pool);
	return is_working;
}



