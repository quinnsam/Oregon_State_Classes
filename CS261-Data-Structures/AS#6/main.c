#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"


char* getWord(FILE *file)
{
	//printf("Entered Get word!\n");

	int length = 0;
	int maxLength = 16;
	char character;

	char* word = malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			//printf("length+1 > maxLength\n");
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
				(character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
				(character >= 'a' && character <= 'z') || /*or a lowercase letter*/
				character == 39) /*or is an apostrophe*/
		{
			//printf("Character Pass\n");
			word[length] = character;
			length++;
		}
		else if(length > 0){
			//printf("length > 0\n");
			break;
		}
	}

	if(length == 0)
	{
		//printf("length==> 0\n");
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}


int main (int argc, const char * argv[]){
	char *word;
	int *value = 0;
	const char* filename;
	struct hashMap *hashTable;
	int tableSize = 10;
	clock_t timer;
	FILE *fileptr;


	if(argc == 2)
		filename = argv[1];
	else
		filename = "input1.txt"; /*specify your input text file here*/
	printf("opening file: %s\n", filename);
	fileptr = fopen(filename, "r");
	if(fileptr != 0){
		printf("Open Successfull!\n\n");
	}
	else{
		printf("Failed to open!\n");
	}
	timer = clock();
	hashTable = createMap(tableSize);
	//printf("Good!\n");
	/*... concordance code goes here ...*/
	while(!feof(fileptr)){
			//printf("In While\n");

			word = getWord(fileptr);
			//printf("After get\n");
			if(!word){
				//printf("Word = NULL\n");
				break;
			}
			value = (int *)atMap(hashTable, word);
			//printf("After Value set\n");
			if(value != 0){
				//printf("Value != NULL!\n");
				(*value)++;
			}
			else{
				//printf("ELse!\n");
				value = (int*) malloc(sizeof(int));
				*value = 1;
				insertMap(hashTable, word, value);

			}

			//printf("%s:%d\n", word, *value);

		}
		//printf("Out Of While \n");
		fclose(fileptr);
	/*... concordance code ends here ...*/

	printMap(hashTable);
	timer = clock() - timer;
	printf("\n\nconcordance ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	printf("Table emptyBuckets = %d\n", emptyBuckets(hashTable));
	printf("Table count = %d\n", size(hashTable));
	printf("Table capacity = %d\n", capacity(hashTable));
	printf("Table load = %f\n", tableLoad(hashTable));

	printf("Deleting keys\n\n");
	//removeKey(hashTable, "hey");
	removeKey(hashTable, "and");
	removeKey(hashTable, "me");
	removeKey(hashTable, "the");
	printMap(hashTable);

	//deleteMap(hashTable);
	printf("\n\nDeleted the table\n");
	return 0;
}

void printValue(ValueType v) {
	printf("Value:%d", *(int *)v);
}


