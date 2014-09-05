/*
 * =====================================================================================
 *
 *       Filename:  link.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月28日 21时43分33秒
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

STU * STU_creat()
{
	STU * head, *q, *p;

	head = (STU *)malloc(sizeof(STU));
	head->next == NULL;

	do
	{
		p = (STU *)malloc(sizeof(STU));

		scanf("%d", &p->num);

		if (p->num == 0)
		{
			free(p);
			break;
		}
		p->next = head->next;
		head->next = p;
	}while(1);

	return head;
}
/*STU * STU_creat_test()
{
	STU * head;

	head = (STU * )malloc(sizeof(STU));
	head->next = NULL;

}
*/

void reverse_link(STU * head)
{
	STU  *p, *q;

	p = head->next;
	head->next = NULL;

	while(p)
	{
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
}
void pur_link(STU * head)
{
	STU *p, *q, *r;

	p = head->next;
	if (p != NULL)
	{
		while (p->next)
		{
			q = p;
			while (q->next)
			{
				if (q->next->num == p->num)
				{
					r = q->next;
					q->next = r->next;
					free(r);
				}
				else
				{
					q = q->next;
				}
			}
			p = p->next;
		}
	}
}


void differ_link(STU * head1, STU * head2)
{
	STU *pre, *p, *r, *q;

	pre = head1;
	p = head1->next;

	while (p != NULL)
	{
		q = head2->next;
		while (q != NULL && q->num != p->num)
		{
		//	printf("\np->num = %d\tq->num = %d\n", p->num, q->num);
			q = q->next;			
		}
		if (q != NULL)
		{
			r = p;
			pre->next = p->next;
//			pre = p;
			p = p->next;
		//	printf("这里p->num1 = %d\n", p->num);
			free(r);
		}
		else  
		{
			pre = p;
			p = p->next;
		//	printf("这里p->num2 = %d\n", p->num);
		}
	}
}
void STU_show(STU * head)
{
	STU *p;

	p = head->next;

	for (;p;p = p->next)
	{
		printf("%d\t", p->num);
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	STU * head1, *head2;

	printf("创造第一个链表\n");
	head1 = STU_creat();
	printf("创造第二个链表\n");
	head2 = STU_creat();
	STU_show(head1);
	STU_show(head2);

//	reverse_link(head);
	differ_link(head1, head2);
	STU_show(head1);
	STU_show(head2);

	return EXIT_SUCCESS;
}

