/*
 * =====================================================================================
 *
 *       Filename:  merge.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 23时54分29秒
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

int length(STU *la)
{
	STU * p;
	int num = 1;

	p = la->next;

	while (p)
	{
		num++;
		p = p->next;
	}

	return num;
}

STU * merge_link(STU *la, STU *lb)
{
	STU *p, *q, *tmp, *p1, *q1;

	p = la->next;
	q = lb->next;

	la->next = NULL;
	tmp = la;

	while (p)
	{
		q1 = q->next;
		p1 = p->next;
		tmp->next = p;
		q->next = p->next;
		p->next = q;
		tmp = q;
		q = q1;
		p = p1;
	}

	tmp->next = q;

	return la;
}
int main(int argc, char *argv[])
{
	STU *la, *lb;
	int m, n;

	la = creat_link();
	lb = creat_link();

	show_link(la);
	show_link(lb);

	m = length(la);
	n = length(lb);

	if (m < n)
	{
		la = merge_link(la, lb);
		show_link(la);
	}
	else
	{
		lb = merge_link(lb, la);
		show_link(lb);
	}

	return EXIT_SUCCESS;
}

