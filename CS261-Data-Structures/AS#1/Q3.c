/* CS 261 - Assignment 1 - Q3
 * Name: Sam Quinn
 * Date: 04/12/2013
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h> 

void sort(int *numbers, int n) {
     /* Sort the array numbers, of length n */
	int i,t,p;
	do{
		p=0;
		for(i=0; i<n-1; ++i){
			if(numbers[i]>numbers[i+1]){
				t=numbers[i];
				numbers[i]=numbers[i+1];
				numbers[i+1]=t;
				p=1;
			}
		}

	}while(p!=0);

}

int main() {
	srand(time(NULL));
    /* Declare an integer n and assign it a value of 20 */
    int n=20;
    /* Allocate memory for an array of n integers using malloc */
    int* num = malloc(n*(sizeof(int)));
    /* Fill this array with random numbers, using rand() */
    int i;
    for(i=0; i<n; ++i){
    	num[i]=rand()%100;
    }

    /* Print the contents of the array */
    printf("Unorganized Numbers\n");
    for(i=0; i<n; ++i){
    	printf("%d ", num[i]);
       }
    printf("\n");

    /* Pass this array along with n to the sort() function of part a */
    sort(num, n);

    /* Print the contents of the array */
    printf("Organized Numbers\n");
    for(i=0; i<n; ++i){
    	printf("%d ", num[i]);
       }
    printf("\n");

    return 0;
}

