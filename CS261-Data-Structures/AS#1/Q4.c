/* CS 261 - Assignment 1 - Q4
 * Name:Sam Quinn
 * Date:04/11/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

struct student {
	int id;
	int score;
};

void sort(struct student *students, int n) {
	/* Sort the n students based on their score */
	/* Remember, each student must be matched with their original score after sorting */
	int i,t,ti,p;
	do{
		p=0;
		for(i=0; i<n-1; ++i){
			if(students[i].score>students[i+1].score){
				t=students[i].score;
				ti=students[i].id;
				students[i].score=students[i+1].score;
				students[i].id=students[i+1].id;
				students[i+1].score=t;
				students[i+1].id=ti;
				p=1;
			}
		}

	}while(p!=0);

}

int main() {
	/* Declare an integer n and assign it a value */
	int n=12;

	/* Allocate memory for n students using malloc */
	struct student *s = malloc(n*(sizeof(struct student)));
	assert(s != 0);

	/* Generate random IDs and scores for the n students, using rand() */
	int uni[10];
	int i, id, num, ok=0;
	for(num=0; num<11; ++num){
		i=0;

		do{
			id=rand()%20 +1;
			if(id != uni[i]){
				ok=1;
			}
			++i;
		}while(ok!=1 && i>10);
		s[num].id=id;
		uni[num]=id;

		s[num].score=rand()%100;
	}



		/* Print the contents of the array of n students */
		int x,y,z;
		for(x=1; x<11; ++x){
			y=s[x].id;
			z=s[x].score;
			printf("Student #%d\nId:%d\nScore:%d\n",x,y,z);

		}



		/* Pass this array along with n to the sort() function */
		sort(s,n);

		/* Print the contents of the array of n students */
		printf("Students in ascending order\n");
		for(x=1; x<11; ++x){
			y=s[x].id;
			z=s[x].score;
			printf("Student #%d\nId:%d\nScore:%d\n",x,y,z);

		}

		return 0;
	}


