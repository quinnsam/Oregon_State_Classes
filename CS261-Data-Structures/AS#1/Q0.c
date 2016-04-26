/* CS 261 - Assignment 1 - Q0
 * Name: Sam Quinn
 * Date: 04/10/2013
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int *iptr) {
     /* Print the value pointed to by iptr */
     printf("The value of iptr = %d\n", *iptr);

     /* Print the address pointed to by iptr */
     printf("The address pointed by iptr = %p\n", iptr);

     /* Print the address of iptr itself */
     printf("The address of iptr = %x\n", iptr);
}

int main() {
    /* Declare an integer x */
    int x;

    /* Print the address of x */
    printf("X's addres is: %p\n", &x);

    /* Call fooA() with the address of x */
    fooA(&x);

    /* Print the value of x */
    printf("x = %d\n",x);

    return 0;
}

