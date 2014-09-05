/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月04日 21时12分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct stack
{
	int data[MAXSIZE];
	int top;
}Stack;

Stack * init_stack()
{
	Stack * s;

	s = malloc(sizeof(Stack));
	s->top = -1;

	return s;
}

int empty_stack(Stack * s)
{
	if (s->top == -1)
	{
		return 1;
	}

	return 0;

}

int push_stack(Stack * s, int x)
{
	if (s->top == MAXSIZE - 1)
	{
		return 0;
	}

	else
	{
		s->top++;
		s->data[s->top] = x;
		return 1;
	}
}

int pop_stack(Stack * s, int * data)
{
	if (empty_stack(s) == 1)
	{
		return 0;
	}

	else
	{
		*data = s->data[s->top];
		s->top--;
		return 1;
	}
}

int top_stack(Stack * s, int * data)
{
	if (empty_stack(s) == 1)
	{
		return 0;
	}

	else 
	{
		*data = s->data[s->top];
		return 1;
	}
}

int main(int argc, char *argv[])
{
	Stack *s;
	int num;

	s = init_stack();

	push_stack(s, 5);
	push_stack(s, 4);
	push_stack(s, 3);
	push_stack(s, 2);
	push_stack(s, 1);

	pop_stack(s, &num);

	printf("num = %d\n", num);

	top_stack(s, &num);

	printf("num = %d\n", num);

	top_stack(s, &num);

	printf("num = %d\n", num);


	return EXIT_SUCCESS;
}

