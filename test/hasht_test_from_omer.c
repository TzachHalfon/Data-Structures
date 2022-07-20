#include <stdio.h> /* printf */
#include <ctype.h> /* tolower */
#include <string.h> /* strcmp, strcat */
#include <strings.h> /* strcasecmp */
#include <stdlib.h> /* malloc, free */
#include "hasht.h"

#define FAIL 1
#define SUCCESS 0
#define EXP_CAP 5
#define DICT_CAP 26
#define MAX_WORD_LEN 20
#define NUM_OF_WORDS 102401
#define TEST_SPELL_CHECKER 0

typedef struct student
{
	long class_id;
	char f_name[30];
	char l_name[30];
	int grade;
}student_t;

static size_t StudentHashByClassId(const void*);
static int StudentCompareByGrade(const void*, const void*);
static int StudentLowerGrade(void*, void*);

static void TestAllFuncs();
static void TestCreate();
static void TestDestroy();
static void TestInsert();
static void TestRemove();
static void TestSizeEmpty();
static void TestFind();
static void TestForEach();
static void TestLoad();
static void TestSD();

static void TestSpellChecker();
static char **DictCreate();
static void DictDestroy(char**);
static int DictFill(char**);
static void FillTable(hasht_t*, char**);
static void CheckInput(hasht_t*);
static size_t SCHashByFirstChar(const void*);
static int SCCompareStrings(const void*, const void*);

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestInsert();
	TestRemove();
	TestSizeEmpty();
	TestFind();
	TestForEach();
	TestLoad();
	TestSD();
	TestDestroy();
	if(TEST_SPELL_CHECKER)
	{
		printf("~Spell Checker~\n");
		TestSpellChecker();
	}
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	if(NULL != table)
	{
		printf("HashtCreate working!                                 V\n");
	}
	else
	{
		printf("HashtCreate NOT working!                             X\n");
	}
	
	HashtDestroy(table);
}

static void TestDestroy()
{
	printf("*Run vlg to test HashtDestroy*\n");
}

static void TestInsert()
{
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	int size_before = -1;
	int size_after = -1;
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	size_before = HashtSize(table);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	
	size_after = HashtSize(table);
	
	if(0 == size_before && 3 == size_after)
	{
		printf("HashtInsert working!                                 V\n");
	}
	else
	{
		printf("HashtInsert NOT working!                             X\n");
	}
	
	HashtDestroy(table);
}

static void TestRemove()
{
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {3, "stephen", "huntley", 75};
	student_t class = {3, " ", " ", 66};
	int size_before = -1;
	int size_after = -1;
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);

	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	size_before = HashtSize(table);
	
	HashtRemove(table, &class.grade);
	
	size_after = HashtSize(table);
	if(4 == size_before && 3 == size_after)
	{
		printf("HashtRemove working!                                 V\n");
	}
	else
	{
		printf("HashtRemove NOT working!                             X\n");
	}
	
	HashtDestroy(table);
}

static void TestSizeEmpty()
{	
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {3, "stephen", "huntley", 75};
	size_t size_before = 0, size_after = 0;
	int empty = -1, not_empty = -1;
	
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	size_before = HashtSize(table);
	empty = HashtIsEmpty(table);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	size_after = HashtSize(table);
	not_empty = HashtIsEmpty(table);
	
	if(0 == size_before && 4 == size_after)
	{
		printf("HashtSize working!                                   V\n");
	}
	else
	{
		printf("HashtSize NOT working!                               X\n");
	}
	
	if(1 == empty && 0 == not_empty)
	{
		printf("HashtIsEmpty working!                                V\n");
	}
	else
	{
		printf("HashtIsEmpty NOT working!                            X\n");
	}
	
	HashtDestroy(table);
}

static void TestFind()
{
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {3, "stephen", "huntley", 75};
	
	student_t to_find = {2, " ", " ", 99};
	student_t not_there = {3, " ", " ", 50};
	
	student_t *found;
	student_t *not_found;
	
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	found = (student_t*)HashtFind(table, &to_find);
	not_found = (student_t*)HashtFind(table, &not_there);
	
	if(99 == found->grade && NULL == not_found)
    {
    	printf("HashtFind working!                                   V\n");
	}
	else
	{
		printf("HashtFind NOT working!                               X\n");
	}
	
	HashtDestroy(table);
}

static void TestForEach()
{
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {3, "stephen", "huntley", 75};
	student_t to_find = {2, " ", " ", 89};
	
	student_t *found;
	student_t *not_found;
	int lower_grade_by = 10;
	
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	not_found = (student_t*)HashtFind(table, &to_find);

	HashtForEach(table, StudentLowerGrade, &lower_grade_by);

	found = (student_t*)HashtFind(table, &to_find);	
	
	if(89 == found->grade && NULL == not_found)
    {
    	printf("HashtForEach working!                                V\n");
	}
	else
	{
		printf("HashtForEach NOT working!                            X\n");
	}
	
	HashtDestroy(table);
}

static void TestLoad()
{	
	student_t student1 = {2, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {3, "stephen", "huntley", 75};
	double load_before = 0, load_after = 0;
	
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	load_before = HashtLoad(table);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	load_after = HashtLoad(table);
	
	if(0 == load_before && 0.8 == load_after)
	{
		printf("HashtLoad working!                                   V\n");
	}
	else
	{
		printf("HashtLoad NOT working!                               X\n");
	}
	HashtDestroy(table);
}

static void TestSD()
{	
	student_t student1 = {1, "omer", "des", 99};
	student_t student2 = {2, "johnny", "bravo", 77};
	student_t student3 = {3, "donald", "trump", 66};
	student_t student4 = {4, "stephen", "huntley", 75};
	double sd_before = 0, sd_after = 0;
	
	hasht_t *table = HashtCreate(EXP_CAP, StudentCompareByGrade, StudentHashByClassId);
	
	sd_before = HashtStandardDeviation(table);
	
	HashtInsert(table, &student1);
	HashtInsert(table, &student2);
	HashtInsert(table, &student3);
	HashtInsert(table, &student4);
	
	sd_after = HashtStandardDeviation(table);
	
	if(0 == sd_before && 0.0001 > sd_after - 0.4)
	{
		printf("HashtStandardDeviation working!                      V\n");
	}
	else
	{
		printf("HashtStandardDeviation NOT working!                  X\n");
	}
	
	HashtDestroy(table);
}

static void TestSpellChecker()
{
	hasht_t *table = HashtCreate(DICT_CAP, SCCompareStrings, SCHashByFirstChar);  
	char **dict = DictCreate();

	if(NULL == dict)
	{
		HashtDestroy(table);
		return;
	}

	if(SUCCESS != DictFill(dict))
	{
		DictDestroy(dict);
		HashtDestroy(table);
		return;
	}

	FillTable(table, dict);
	CheckInput(table);
	
	DictDestroy(dict);
	HashtDestroy(table);
}

static void CheckInput(hasht_t *table)
{
	char input[MAX_WORD_LEN]= "";
	while(1)
	{
		printf("Enter a word (or '-quit' to quit):\n");
		scanf("%s", input);
		if(strcmp(input, "-quit") == 0)
		{
		    break;
		}
		strcat(input, "\n");
		if(NULL != HashtFind(table, input))
		{
		    printf("This word exists\n");
		    continue;
		}
		printf("This word doesn't exist\n");
	}
}

static void FillTable(hasht_t *table, char **dict)
{
	int i = 0;
	for (; i < NUM_OF_WORDS; ++i)
	{
		HashtInsert(table, dict[i]);
	}
}

static char **DictCreate()
{
    int i = 0;
    char **dict = (char**)malloc(sizeof(char*) * NUM_OF_WORDS);
    
    for (i = 0; i < NUM_OF_WORDS; ++i)
    {
        dict[i] = (char*)malloc(MAX_WORD_LEN);
        if(NULL == dict[i])
        {
            break;
        }
    }
    if(i != NUM_OF_WORDS)
    {
        for (i -= 1; i >= 0; --i)
        {
            free(dict[i]);
        }
        free(dict);
        return (NULL);
    }
    return (dict);
}

static void DictDestroy(char **dict)
{
    int i = 0;
    for (; i < NUM_OF_WORDS; ++i)
    {
        free(dict[i]);
    }
    free(dict);
}

static int DictFill(char **dict)
{
    int i = 0;
    FILE *fp = fopen("./test/american-english.txt","r");
    
    if(NULL == fp)
    {
        return (FAIL);
    }
    for(; i < NUM_OF_WORDS; ++i) 
    {
        fgets(dict[i],MAX_WORD_LEN,fp);
    }
    
    if(0 != fclose(fp))
    {
        return (FAIL);
    }
    return (SUCCESS);
}

static size_t StudentHashByClassId(const void *data)
{
	return (((student_t*)data)->class_id % EXP_CAP);
}

static int StudentCompareByGrade(const void *data1, const void *data2)
{
	return (((student_t*)data1)->grade == ((student_t*)data2)->grade);
}

static int StudentLowerGrade(void *data, void *param)
{
	((student_t*)data)->grade -= *(int*)param;
	return (0);
}

static size_t SCHashByFirstChar(const void *data)
{
    return (*(char*)data % DICT_CAP);
}

static int SCCompareStrings(const void *data1, const void *data2)
{
    return (0 == strcasecmp((char*)data1, (char*)data2));
}


