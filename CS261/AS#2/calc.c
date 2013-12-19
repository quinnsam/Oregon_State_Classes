#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
 */
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	returnNum = strtod(s, &end);

	/* If there's anything in end, it's not a number */
	if(strcmp(end, "") == 0) {
		//printf("Num=%lf\n",returnNum);
		*num = returnNum;
		return 1;
	} else {
		return 0;
	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
 */
void add (struct DynArr *stack)
{
	TYPE q1, q2;
	/* FIXME: You will write this function */
		//printf("Hey bro\n"); 
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		q2=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, q1+q2);
		//printf("Hey bro\n"); 

	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
 */
void subtract(struct DynArr *stack)
{
	TYPE q1, q2;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		q2=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, q2-q1);

	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
 */
void divide(struct DynArr *stack)
{
	TYPE q1, q2;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		q2=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, q2/q1);

	}
}
void multi(struct DynArr *stack)
{
	TYPE q1, q2;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		q2=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, q1*q2);

	}

}
void power(struct DynArr *stack)
{
	TYPE q1, q2;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		q2=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(q1,q2));

	}
}
void square(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(q1,2));

	}

}
void cube(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(q1,3));

	}

}
void abso(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		if(q1<0){
			q1=q1*(-1);
		}
		pushDynArr(stack, q1);

	}
}
void sqroot(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, sqrt(q1));

	}
}
void exps(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, exp(q1));

	}
}
void lns(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, log(q1));

	}
}
void logs(struct DynArr *stack)
{
	TYPE q1;
	/* FIXME: You will write this function */
	if(isEmptyDynArr(stack)==0){
		q1=topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, log10(q1));

	}
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	double d;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++)
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0){
			if(sizeDynArr(stack)<=2){
				add(stack);
			}
			else{
				printf("You have entered too many arguments for this operand you.\n");
				return 0;
			}
		}

		else if(strcmp(s,"-") == 0){
			if(sizeDynArr(stack)<=2){
				subtract(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		}

		else if(strcmp(s, "/") == 0){
			if(sizeDynArr(stack)<=2){
				divide(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		}

		else if(strcmp(s, "x") == 0){
			if(sizeDynArr(stack)<=2){
				multi(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Multiplying\n");
		}

		else if(strcmp(s, "^") == 0){
			if(sizeDynArr(stack)<=2){
				power(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Power\n");
		}

		else if(strcmp(s, "^2") == 0)
		{
			if(sizeDynArr(stack)<=1){
				square(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Squaring\n");
		}

		else if(strcmp(s, "^3") == 0){
			if(sizeDynArr(stack)<=1){
				cube(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Cubing\n");
		}

		else if(strcmp(s, "abs") == 0){
			if(sizeDynArr(stack)<=2){
				abso(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Absolute value\n");
		}

		else if(strcmp(s, "sqrt") == 0){
			if(sizeDynArr(stack)<=1){
				sqroot(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Square root\n");
		}

		else if(strcmp(s, "exp") == 0){
			if(sizeDynArr(stack)<=2){
				exps(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Exponential\n");
		}

		else if(strcmp(s, "ln") == 0){
			if(sizeDynArr(stack)<=1){
				lns(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Natural Log\n");
		}

		else if(strcmp(s, "log") == 0)
		{
			if(sizeDynArr(stack)<=2){
				logs(stack);
			}
			else{
				printf("You have entered too many arguments for this operand.\n");
				return 0;
			}
		/* FIXME: replace printf with your own function */
		printf("Log\n");
		}

		else
		{
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")
			
			if(strcmp(s,"e")==0){
				pushDynArr(stack, 2.7182818);
			}
			if(strcmp(s,"pi")==0){
				pushDynArr(stack, 3.14159265);
			}

			if(strcmp(s," ")!=0){
				if(isNumber(s,&d)==1){
				//printf("yay\n");
				pushDynArr(stack,d);
				}
			}
			else {
				printf("I am sorry but you have entered something I can not compute\n");
				return 0;
			}
			/*if(strcmp(s," ")!=0){
			if(isNumber(s,&d)==1){
				printf("yay %lf\n",d);
				
				pushDynArr(stack,d);
			}
			}*/
			//printf("yay %lf\n",d);
		}
	}	//end for

	/* FIXME: You will write this part of the function (2 steps below)
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	if(sizeDynArr(stack)==1){
	result=topDynArr(stack);
	popDynArr(stack);
	printf("The Answer is: %lf\n",result);
	return result;
	}
	else{
		printf("Something went wrong, perhaps try again..\n");
		printf("The Size of the array is %d\n", sizeDynArr(stack));
		int i;
		for(i=0; i<sizeDynArr(stack);++i){
		printf("The contents are %lf\n",getDynArr(stack,i));
		}
		return 0;
	}
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}

