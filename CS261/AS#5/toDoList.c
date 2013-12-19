/*
####################################
File Name: toDoList.c		   #
Created By: Oregon State University#
Edited By: Sam Quinn		   #
Finished: Wednesday May 22 20:31   #
####################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
Task* createTask (int priority, char *desc)
{
	struct Task *new_task = malloc(sizeof(struct Task));
	new_task->priority = priority;
	strcpy(new_task->description, desc);
	return new_task;


}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the
			task priority, followed by a tab character (\t), and
			the task description.

			The tasks are not necessarily stored in the file in
			priority order.

*/
void saveList(DynArr *heap, FILE *filePtr)
{
	int i;
	Task* task;
	assert(sizeDynArr(heap) > 0);
	for(i = 0; i < sizeDynArr(heap); i++)
	{
		task = getDynArr(heap, i);
		fprintf(filePtr, "%d\t%s\n", task->priority, task->description);
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	Task* task;
	char line[100];  /* Assume lines < 100 */
	char desc[TASK_DESC_SIZE], *nlptr;
	int priority;

	/* Read the priority first, then the description.
	 * fgets() is used to read string with spaces
	 */
#ifdef NOTDEF
	while (fscanf(filePtr, "%d\t", &priority) != EOF)
	{
	  /* fgets() stops reading at \n character */
		fgets(desc, sizeof(desc), filePtr);
		/* remove trailing newline character */
		nlptr = strchr(desc, '\n');
		if (nlptr)
		  *nlptr = '\0';

	   	task = createTask(priority, desc);
		addHeap(heap, task);
	}
#endif

	while(fgets(line, sizeof(line), filePtr) != 0)
	{
	  sscanf(line, "%d\t%[^\n]", &priority, desc);
	  task = createTask(priority, desc);
	  addHeap(heap, task);
	} /* should use feof to make sure it found eof and not error*/

}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
   int i;
   struct Task *temp;
   for(i=0; i < sizeDynArr(heap); ++i){
	   temp = (struct Task*)getDynArr(heap, i);
	   printf("Description:%s Priority:%d\n", temp->description, temp->priority);
   }
}

/*  Delete the list

    param:  heap    pointer to the list
    post:   The tasks from the list are removed and their occupied memories are freed

*/
void deleteList(DynArr *heap)
{

	Task* task;
	while(sizeDynArr(heap) > 0)
	{
	  	/* get the task */
		task = getMinHeap(heap);
		/* remove the task */
		removeMinHeap(heap);
		/* free the task */
		free(task);
	}
	/* free the heap */
	deleteDynArr(heap);
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
/*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in dynamicArray.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct Task*), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
	struct Task *lef = (struct Task*)left;
		struct Task *righ = (struct Task*)right;

		if(lef->priority == righ->priority){
			return 0;
		}
		if(lef->priority < righ->priority){
			return -1;
		}
		if(lef->priority > righ->priority){
			return 1;
		}
		return 0;
}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
	struct Task *temp;
		assert (curval != NULL);
		temp = (struct Task *) curval;
		printf("Priority:%d Description: %s\n",temp->priority, temp->description);
}

