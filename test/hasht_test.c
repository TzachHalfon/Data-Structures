#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "hasht.h"

#define SUCCESS 0
#define FAIL 1
#define CAP 20
#define ABC 26
#define MAX_WORD_LEN 30
#define NUM_OF_WORDS 102401
#define TEST_SPELL_CHECKER 0

typedef struct Person
{
	size_t id;
	int age;
}person_t;


static size_t Hash(const void *key);
static int Compare(const void *key1, const void *key2);

static void TestAllFuncs(void);
static void TestCreate(void);
static void TestInsert(void);
static void TestRemove(void);
static void TestIsEmpty(void);

/*spell checker*/
static void TestCheckSpelling(void);
static size_t HashLetters(const void *key);
static int CompareStrings(const void *key1, const void *key2);
static int FillDictionary(char **lines);
static char **CreateDictionary(void);
static void DestroyDictionary(char **lines);

int main(void)
{
	TestAllFuncs();
	return 0;
}


static void TestAllFuncs(void)
{
	printf("~~STARTING TESTING!~~\n");
	TestCreate();
	TestInsert();
	TestRemove();
	TestIsEmpty();
	if(TEST_SPELL_CHECKER)
    {
        printf("~Spell Checker~\n");
        SpellChecker();
    }
	printf("~~~END OF TESTING~~~\n");
	printf("~~~RUN VALGRIND!~~~\n");
}

static void TestCreate(void)
{
	hasht_t *hash = HashtCreate(CAP, Compare, Hash);
	if(hash == NULL)
	{
		printf("HashtCreate not working!\n");
	}
	else
	{
		printf("HashtCreate working!\n");
	}
	HashtDestroy(hash);
}

static void TestInsert(void)
{
	person_t persons[20];
	int i = 0;
	hasht_t *hash = HashtCreate(CAP, Compare, Hash);
	if(hash == NULL)
	{
		printf("HashtCreate not working!\n");
	}
	for (i = 0; i < 20; i++)
	{
		persons[i].age = i;
		persons[i].id = i * 1000;
		HashtInsert(hash, &persons[i]);
	}

	if(HashtSize(hash) == 20)
	{
		printf("HashtInsert working!\n");
	}
	else
	{
		printf("HashtInsert not working!\n");
	}

	HashtDestroy(hash);
}

static void TestRemove(void)
{
	person_t tzach = {315080416, 22};
	person_t tzach2 = {111111111, 23};
	person_t tzach3 = {2222222222, 24};
	hasht_t *hash = HashtCreate(CAP, Compare, Hash);
	if(hash == NULL)
	{
		printf("HashtCreate not working!\n");
	}

	HashtInsert(hash, &tzach);
	HashtInsert(hash, &tzach2);
	HashtInsert(hash, &tzach3);

	HashtRemove(hash, &tzach3);
	if(HashtSize(hash) == 2)
	{
		printf("HashtRemove working!\n");
	}
	else
	{
		printf("HashtRemove not working!\n");
	}
	HashtDestroy(hash);
}

static void TestIsEmpty(void)
{
	hasht_t *hash = HashtCreate(CAP, Compare, Hash);

	if(HashtIsEmpty(hash) != 1)
	{
		printf("TestIsEmpty not working!\n");
	}
	else
	{
		printf("TestIsEmpty working!\n");
	}
	HashtDestroy(hash);
}


static size_t Hash(const void *key)
{
	person_t *person = (person_t*)key;
	return (person->age % CAP);
}

static int Compare(const void *key1, const void *key2)
{
	return ((person_t*)key1)->age == ((person_t*)key2)->age;
}

/*===========================  spell checker =============================*/
static void TestCheckSpelling(void)
{
	int i = 0;
	hasht_t *spell_checker = HashtCreate(ABC, CompareStrings, HashLetters);
	char word[MAX_WORD_LEN]= "";
    char **lines = CreateDictionary();
	if (lines == NULL)
	{
		HashtDestroy(spell_checker);
		return;
	}

	if(FillDictionary(lines) != 0)
	{
		DestroyDictionary(lines);
		HashtDestroy(spell_checker);
		return;
	}

	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		HashtInsert(spell_checker, lines[i]);
	}

	while(1)
	{
		printf("enter a word\n");
		scanf("%s", word);
		if(strcmp(word, "-quit") == 0)
		{
			break;
		}
		strcat(word, "\n");
		if(NULL != HashtFind(spell_checker, word))
		{
			printf("exist\n");
			continue;
		}
		printf("not exist\n");
	}

	DestroyDictionary(lines);
	HashtDestroy(spell_checker);
}

static char **CreateDictionary(void)
{
	int i = 0;
	char **lines = (char**)malloc(sizeof(char *) * NUM_OF_WORDS);
	
	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		lines[i] = (char*)malloc(MAX_WORD_LEN);
		if(lines[i] == NULL)
		{
			break;
		}
	}

	if(i != NUM_OF_WORDS)
	{
		for (i -= 1; i >= 0; ++i)
		{
			free(lines[i]);
		}
		free(lines);
		return (NULL);
	}

	return (lines);
}

static void DestroyDictionary(char **lines)
{
	int i = 0;
	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		free(lines[i]);
	}
	free(lines);
}


static int FillDictionary(char **lines)
{
	FILE *fp = NULL;
	int i = 0;
	fp = fopen("./test/american-english.txt","r");
	
	if(fp == NULL)
	{
		return (FAIL);
	}
    for(i = 0; i < NUM_OF_WORDS;++i) 
	{
		fgets(lines[i],MAX_WORD_LEN,fp);
    }
    
	if(fclose(fp) != 0)
	{
		printf("problem with the dictionary file\n");
		return (FAIL);
	}

	return (SUCCESS);
}

static size_t HashLetters(const void *key)
{
	return (*(char*)key % ABC);
}

static int CompareStrings(const void *key1, const void *key2)
{
	return (0 == strcasecmp((char*)key1, (char*)key2));
}