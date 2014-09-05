/*
 * =====================================================================================
 *
 *       Filename:  72_2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月24日 18时57分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 690892695@qq.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct 
{
	char string[MAXSIZE];
	int top;
}Seqstack;

Seqstack * init_Seqstack ()
{
	Seqstack * s;
	s = malloc (sizeof (Seqstack));
	s->top = -1;
	return s;
};

int empty_Seqstack (Seqstack * s)
{
	if (s->top == -1)
	{
		return 1;
	}

	return 0;
}

int push_Seqstack(Seqstack * s, char ch)
{
	if (s->top == MAXSIZE - 1)
	{
		return 0;
	}

	s->top++;
	s->string[s->top] = ch;
	return 1;
}

int pop_Seqstack (Seqstack * s, char * ch)
{
	if (s->top == -1)
	{
		return 0;
	}

	* ch = s->string[s->top];
	s->top--;
	return 1;
}

int get_Seqstack (Seqstack * s, char * ch)
{
	if (s->top == -1)
	{
		return 0;
	}

	* ch = s->string[s->top];
	return 1;
}

int main(int argc, char *argv[])
{
	Seqstack * s1, * s2;
	char string[MAXSIZE];
	char ch1, ch2;
	int i;
	int flag = 1;


	s1 = init_Seqstack();
	s2 = init_Seqstack();

	printf("请输入字符串;");
	scanf("%s", string);

	for (i = 0; i < strlen(string); i++)
	{
		push_Seqstack(s1, string[i]);
		push_Seqstack(s2, string[strlen(string) - i - 1]);
	}

	while (empty_Seqstack(s1) != 1)
	{
		pop_Seqstack(s1, &ch1);
		pop_Seqstack(s2, &ch2);

		if (ch1 != ch2)
		{
			flag = 0;
			break;
		}
	}

	if (flag == 1)
	{
		printf("是回文字符串\n");
	}
	else
	{
		printf("不是回文字符串\n");
	}

	return EXIT_SUCCESS;
}

