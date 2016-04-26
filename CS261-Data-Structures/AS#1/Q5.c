/* CS 261 - Assignment 1 - Q5
 * Name: Sam Quinn
 * Date: 04/12/2013
 */

#include <stdio.h>
#include <stdlib.h>
int i, lenght;
/* Converts a lower case letter to upper case */
char toUpperCase(char ch) {
     return ch - 'a' + 'A';
}

/* Converts an upper case letter to lower case */
char toLowerCase(char ch) {
     return ch - 'A' + 'a';
}

void sticky(char *word) {
     /* Convert to sticky caps */
	char c;
	lenght=sizeof(word);
	for(i=0; i<lenght; ++i){
		c=word[i];
		if(i%2==0){
			if(c<'a'){
			word[i]=toLowerCase(c);
			}
		}
		else if(c>='a'){
			word[i]=toUpperCase(c);
		}


	}


}

int main() {
	char str[256];
    /* Read word from the keyboard using scanf */
	printf("Please enter your favorite word and I will mess the letters up for you!");
	scanf("%s",str);

    /* Call sticky */
	sticky(str);

    /* Print the new word */
	printf("Your new word is %s", str);




    return 0;
}

