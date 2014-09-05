/*
 * =====================================================================================
 *
 *       Filename:  Count.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月08日 19时43分47秒
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

#define LEN sizeof(Charactor)

typedef struct charactor
{
	char ch[3];
	int count;
	struct charactor *next;
}Charactor;

Charactor *find (char *ch, Charactor *head)
{
//	int flag = 1;
	Charactor *p = head->next;

	while (p != NULL )
	{
		if (strcmp(p->ch, ch) == 0)
		{
			p->count++;
			break;
		}
		else
		{
			p = p->next;
		}
	}

	if (p == NULL)
	{
		p = (Charactor *)malloc(sizeof(Charactor));

		strcpy(p->ch, ch);
		p->count = 1;

		p->next = head->next;
		head->next = p;
	}

	return head;
}

void Count(Charactor *head)
{
	Charactor *p;

	p = head->next;

	while (p != NULL)
	{
		printf("%s:%d\n", p->ch, p->count);
		p = p->next;
	}
}
//Charactor *
int main(int argc, char *argv[])
{
	Charactor *head;
	head = (Charactor *)malloc(sizeof(Charactor));
	head->next = NULL;

	int i;

	char data[1000] = {"我不认识你，你是谁啊，你好"};

	for (i = 0; i < strlen(data); i++)
	{
		printf("%c\t", data[i]);
	}
	
	head = find(data, head);
	Count(head);

	return EXIT_SUCCESS;
}

