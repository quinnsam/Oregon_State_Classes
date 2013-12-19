/*
 * sieve.c
 *
 *  Created on: Oct 6, 2013
 *      Author: sam
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int n;
int *prime;
int i, k;
printf("To what number would you like to see prime numbers to? \n");
scanf("%d", &n);
prime = (int*)malloc( (n+1) * sizeof(int));
 
for ( i = 2; i < n; i++ ){ //Fills array but skips numbers 0 and 1 becasue they are special.
	prime[i] = i;
}
   
for ( i = 2; i <= sqrt(n); i++ ){ //loops until sqrt(n) is reached.
	for ( k = i + i; k <= n; k += i ){
		prime[k] = 0;
	}
}
printf("The prime numbers up to the number %d are : \n", n);  
for ( i = 2; i <= n; i++ ){
	if ( prime[i] != 0 ){
		printf("%d\n", prime[i]); // Prints only the values not marked with a 0.
	}
}
   
free(prime);
return 0;
}


 
 
