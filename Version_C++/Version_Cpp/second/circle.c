/*
 * =====================================================================================
 *
 *       Filename:  circle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 23时19分56秒
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
	struct student *next;
}STU;

STU * creat_circle()
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

	q->next = head->next;
	printf("链表建立完成\n");

	return head;
}

void show_circle(STU * head)
{
	STU *p;

	p = head->next;

	do
	{
		printf("%d\t", p->num);
		p = p->next;
	}while (p != head->next);
	printf("\n");
}
void delet_circle(STU * s)
{
	STU *q, *p;

	q = s->next;

	while (1)
	{
		if (s == q->next->next)
		{
			p = q->next;
			break;
		}
		q = q->next;
	}

	q->next = s;

}
int main(int argc, char *argv[])
{
	STU * head, *p;

	head = creat_circle();
	show_circle(head);

	p = head->next->next->next;
	show_circle(p);

	delet_circle(p);
	show_circle(p);

	return EXIT_SUCCESS;
}

