/* CS 261 - Assignment 1 - Q1
 * Name: Sam Quinn
 * Date: 04/12/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>



struct student {
	int id;
	int score;
};

struct student* allocate() {
	/* Allocate memory for ten students */
	struct student *s = malloc(10*(sizeof(struct student)));
	assert(s != 0);

	/* Return the pointer */
	return s;

}

void generate(struct student *students) {
	int uni[10];
	/* Generate random IDs and scores for 10 students */
	/* The ID should be between 1 and 20, scores between 0 and 100 */
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
		students[num].id=id;
		uni[num]=id;



	students[num].score=rand()%100;
}
}

void output(struct student *students) {
	/* Output information about the ten students in the format:
              ID1 score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10 */
	int x,y,z;
	for(x=1; x<11; ++x){
		y=students[x].id;
		z=students[x].score;
		printf("Student #%d\nId:%d\nScore:%d\n",x,y,z);

	}
}

void summary(struct student *students) {
	/* Compute and print the minimum, maximum, and average scores of the ten students */
	int w=100,e=0,r=0,i,c;
	for(i=0; i<10; ++i){
		c=students[i].score;
		if(c<w){
			w=c;
		}
		if(c>e){
			e=c;
		}
		r=r+c;

	}

	printf("The Minimum is:%d\n", w);
	printf("The Maximum is:%d\n", e);
	printf("The Average is:%d\n", r/10);

}

void deallocate(struct student *stud) {
	/* Deallocate memory from stud */
	free(stud);

}

int main(){
	srand(time(NULL));
	struct student *stud = NULL;
	int i;

	/* Call allocate */
	stud=allocate();

	/* Call generate */
	for(i=0; i<10; ++i){
		generate(stud);
	}

	/* Call output */
	output(stud);


	/* Call summary */
	summary(stud);

	/* Call deallocate */
	deallocate(stud);

	return 0;
}

