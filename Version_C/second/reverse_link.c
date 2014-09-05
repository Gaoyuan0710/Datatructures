/*
 * =====================================================================================
 *
 *       Filename:  reverse_link.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 22时34分11秒
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

typedef struct student
{
	int num;
	struct student * next;
}STU;

STU * creat_link()
{
	STU * head, *p, *q;
	int i = 1;

	q = head = (STU *)malloc(sizeof(STU));
	head->next = NULL;

	printf("建立链表，0退出\n");
	do
	{
		p = (STU *)malloc(sizeof(STU));

		printf("请输入第%d个数字:", i++);
		scanf("%d", &p->num);

		if (p->num == 0)
		{
			break;
		}

		q->next = p;
		q = p;
	}while (1);

	q->next = NULL;
	printf("链表建立完成\n");

	return head;
}

void show_link(STU * head)
{
	STU * p;

	p = head->next;

	for (;p;p = p->next)
	{
		printf("%d\t", p->num);
	}
	printf("\n");
}

void reverse_link(STU * head)
{
	STU *p, *q;

	p = head->next;
	head->next = NULL;

	while (p)
	{
		q = p;
		p = p->next;
	//	q->next = p->next;
		q->next = head->next;
		head->next = q;
	}
}

void delet_link(STU * head)
{
	STU *p, *q;

	p = head->next;

	while (p)
	{
		;
	}
}
int main(int argc, char *argv[])
{
	STU * head;

	head = creat_link();
	show_link(head);
	reverse_link(head);
	show_link(head);


	return EXIT_SUCCESS;
}

