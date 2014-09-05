/*
 * =====================================================================================
 *
 *       Filename:  horse.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月11日 21时28分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define N 8
#define MAXSIZE 100

typedef struct position
{
	int x;
	int y;
}POST;

typedef struct elem
{
	int order;
	POST seat;
	int next;
}ELEM;

typedef struct 
{
	POST *bottom;
	POST *top;
	int size;
}SeqStack;

int init_stack(SeqStack s)
{
	s->bottom = (ELEM *)malloc(MAXSIZE * sizeof(ELEM));
	
	s->top = s->bottom;
	
	s->size = MAXSIZE;
	
	return 0;
}

ELEM *top_SeqStack(SeqStack s)
{
	if (s->bottom == s->top)
	{
		printf("栈为空\n");
		exit 0;
	}
	
	return (*(s->top - 1));
}

void push_SeqStack(SeqStack s, ELEM *p)
{
	s->top = p;
	*s->top++;
}

int pop_SeqStack(SeqStack s, ELEM *p)
{
	if (s->bottom == s->top)
	{
		printf("栈为空\n");
		return 0;
	}
	
	*p = *(s->top - 1);
	*s->top--;
	
	return 1;
	
}

int if_empty(SeqStack s)
{
	if (s->bottom == s->top)
	{
		return 1;
	}
	
	return 0;
}

void show_path(SeqStack s)
{
	SeqStack tmp;
	int path[N][N];
	int i;
	
	tmp = s;
	
	i = 0;
	
	while (tmp->bottom != tmp->top)
	{
		path[(*(s->bottom)).seat.x][(*(s->bottom)).seat.y] = i+1;
		s->bottom++;
	}
	for (j = 0; j < N; j++)
	{
		for (i = j; i < N; i++)
		{	
			printf("%d\t", path[j][i]):
		}
		printf("\n");
	}
	
}

POST *next_stap(POST s, int choose)
{
	stwich(choose)
	{
		case 1:
			s.x+=1;
			s.y-=2;
			break;
		case 2:
			s.x+=2;
			s.y-=1;
			break;
			
		case 3:
			s.x+=2;
			s.y+=1;
			break;
			
		case 4:
			s.x+=1;
			s.y+=2;
			break;
			
		case 5:
			s.x-=1;
			s.y+=2;
			break;
			
		case 6:
			s.x-=2;
			s.y+=1;
			break;
			
		case 7:
			s.x-=2;
			s.y-=1;
			break;
			
		case 8:
			s.x-=1;
			s.y-=2;
			break;		
			
	}
	return s;
}


int main()
{
	;
}
