/* CS 261 - Assignment 1 - Q2
 * Name: Sam Quinn
 * Date: 04/12/2013
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int *a, int *b, int c) {
    /* Set a to double its original value */
	*a=2*(*a);

    /* Set b to half its original value */
    *b=(*b)/2;
    /* Assign a+b to c */
    c=*a+*b;
    /* Return c */
    return c;
}

int main() {
    /* Declare three integers x, y, z and initialize them to 5, 6, 7 respectively */
    int x=5;
    int y=6;
    int z=7;
    int u;
    /* Print the values of x, y, z */
    printf("The value of X is:%d\n",x);
    printf("The value of Y is:%d\n",y);
    printf("The value of Z is:%d\n",z);
    /* Call foo() appropriately, passing x, y, z as parameters */
    u=foo(&x,&y,z);
    /* Print the value returned by foo */

    printf("the value returned by foo is:%d\n",u);
    /* Print the values of x, y, z again */
    printf("The New value of X is:%d\n",x);
    printf("The New value of Y is:%d\n",y);
    printf("The New value of Z is:%d\n",z);
    /* Is the return value different than the value of z?  Why? */
    printf("The value of z hasn't changed because I only passed it by\nvalue not by reference.");

  return 0;
}

