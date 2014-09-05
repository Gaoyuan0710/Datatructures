/*
 * =====================================================================================
 *
 *       Filename:  joseph.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月02日 16时43分37秒
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

typedef struct NodeType
{
	int id;
	int password;
	struct NodeType * next;
}JOSEPH;

JOSEPH * creat()
{
	JOSEPH *head, *p, *q;
	char flag = 'y';
	int i = 1;

	head = (JOSEPH *)malloc(sizeof(JOSEPH));
	head->next = NULL;
	p = head;

	do
	{
		q = (JOSEPH *)malloc(sizeof(JOSEPH));
		printf("请输入该人密码:");
		scanf("%d", &q->password);
		q->id = i++;
		p->next = q;
		q->next = head->next;
		p = q;
		getchar();
		printf("是否继续输入？Y/N？");
		scanf("%c", &flag);
	}while(flag == 'y' || flag == 'Y');

	return head;
}

void show(struct NodeType *head)
{
	JOSEPH *p;

	p = head->next;

	do
	//while (p != head )
	{
		printf("id = %d\t password = %d\n", p->id, p->password);
		p = p->next;
	}while (p != head->next);
//	printf("id = %d\t password = %d\n", p->id, p->password);
	printf("\n");
}

int if_empty(JOSEPH * head)
{
	JOSEPH *p;

	p = head->next;

	if (p == head->next)
	{
		return 0;
	}

	return 1;
}

void deal(JOSEPH * head, int num)
{
	JOSEPH *p, *pcur, *q0, *q1, *prv;
	int flag = 1;
	int choose = 1;

	p = head->next;
	q0 = p;
	q1 = p;//->next;

	while (choose)
	{
		for (flag = 1; flag < num; flag++)
		{
			q0 = q1;
			q1 = q1->next;
		}

		if (q1 == q0)
		{
			choose = 0;
		}
		printf("%d 第%d个人出列，密码是%d\n", flag, q1->id, q1->password);

		num = q1->password;
		q0->next = q1->next;
		free(q1);

		q1 = q0->next;
	}
}

int main(int argc, char *argv[])
{
	JOSEPH *head;
	int num = 20;

	head = creat();
	show(head);
	deal(head, num);


	return EXIT_SUCCESS;
}

