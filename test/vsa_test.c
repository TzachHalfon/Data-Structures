#include "vsa.h"
#include <stdlib.h>
#include <stdio.h>


#define MIN(x,y) (((x) < (y)? (x) : (y)))

void TestAllFuncs();
int TestInit();
int TestAlloc();
int TestFree();

int main()
{
	TestAllFuncs();
	return 0;
}


void TestAllFuncs()
{
	int status = 1;
	int returned = 1;
	
	printf("       ~~STARTED TESTING~~\n");
	returned = TestInit();
	status = MIN(status, returned);
	returned = TestAlloc();
	status = MIN(status, returned);
	returned = TestFree();
	status = MIN(status, returned);
	
	if(status == 1)
	{
		printf("~~ALL TESTS FINSIHED SUCCESSFULLY~~\n");
	}
	printf("       ~~FINISHED TESTING~~\n");
}

int TestInit()
{
	void *pool = malloc(32);
    int size_left = 0;
    vsa_t *vsa = NULL;
    
    vsa = VsaInit(pool, 32);
    
    size_left = VsaLargestChunkAvailable(vsa);
    
    if(!(0 == size_left))
    {
        printf("       VsaInit NOT working!\n");
        return 0;
    }

    free(pool);
    return 1;
}

int TestAlloc()
{
    size_t addresses[10] = {0};
    int i = 0;
    int is_working = 1;
    vsa_t *vsa = NULL;
    
    void *pool = malloc(300);
    
    vsa = VsaInit(pool, 300);
    
    for(i = 0; i < 10; ++i)
    {
        addresses[i] = (size_t)VsaAllocate(vsa, 30);
    }
    
    for(i = 0; i < 9; ++i)
    {
        if(i < 5 && 0 == addresses[i] && (addresses[i+1] - addresses[i]) != 48)
        {
            is_working = 0;
            break;
        }
        
        if(i >= 5 && 0 != addresses[i])
        {
            is_working = 0;
            break;
        }
    }
    
    if(28 != VsaLargestChunkAvailable(vsa))
    {
        is_working = 0;
        printf("%ld\n",VsaLargestChunkAvailable(vsa));
    }
    
    if(!(1 == is_working))
    {
        printf("       VsaAlloc NOT working!\n");
        return 0;
    }
    
    free(pool);
    return 1;
}

int TestFree()
{
	vsa_t *vsa = NULL;
    void *addresses[10];
    int i = 0;
    void *pool = malloc(240);
    
    vsa = VsaInit(pool, 240);
    
    for(i = 0; i < 10; ++i)
    {
       addresses[i] = VsaAllocate(vsa, 8);
    }
   
    VsaFree(addresses[1]);
    VsaFree(addresses[2]);
    
	
	
    if(!(32 == VsaLargestChunkAvailable(vsa)))
    {
        printf("       VsaFree NOT working!\n");
        return 0;
    }
    
    free(pool);
    return 1; 
}
