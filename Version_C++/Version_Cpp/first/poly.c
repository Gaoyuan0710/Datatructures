/*
 * =====================================================================================
 *
 *       Filename:  poly.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月02日 21时20分19秒
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

typedef struct poly
{
	int coef;
	int expn;
	struct poly *next;
}POLY;

int len(POLY *la);

POLY * creat ()
{
	POLY * head, *p, *q;
	int i = 1;

	head = (POLY *)malloc(sizeof(POLY));
	head->next = NULL;

	q = head;

	while(1) 
	{
		p = (POLY *)malloc(sizeof(POLY));

		printf("请输入第%d项系数:", i);
		scanf("%d", &p->coef);
		printf("请输入第%d项指数:", i++);
		scanf("%d", &p->expn);

		if (p->expn == 0 && p->coef == 0)
		{
			break;
		}

		q->next = p;
	//	p->next = NULL;
		q = p;

	}
	q->next = NULL;

	return head;
}

void show(POLY * head)
{
	POLY * p;
	int flag = 0;

	p = head->next;

	for (;p;p = p->next)
	{
		if (p->coef == 0)
		{
			continue;
		}

		if (flag != 0 && p->coef > 0)
		{
			printf("+");
		}

		
		printf("%d", p->coef);
		if (p->expn == 1)
		{
			printf("x");
		}
		else if (p->expn > 1)
		{
			printf("x^%d", p->expn);
		}
		flag++;
	}
	printf("\n");

}
POLY * add(POLY * la, POLY * lb)
{
	POLY *p, *q ,*tmp;

	tmp = la;
	p = la->next;
	q = lb->next;
	la->next = NULL;

	while (p && q)
	{
		if (p->expn < q->expn)
		{
			tmp->next = p;
			tmp = p;
			p = p->next;
		}
		else if (p->expn > q->expn)
		{
			tmp->next = q;
			tmp = q;
			q = q->next;
		}
		else if (p ->expn == q->expn)
		{
			p->coef += q->coef;
			tmp->next = p;
			tmp = p;
			p = p->next;
			q = q->next;
		}
	}

	if (p)
	{
		tmp ->next = p;
	}

	else if (q)
	{
		tmp->next = q;
	}

	free (lb);

	return la;
}

int len(POLY *la)
{
	POLY * p;
	int num = 1;

	p = la->next;

	while (p)
	{
		num++;
		p = p->next;
	}

	return num;
}

POLY * multiply(POLY * la, POLY * lb)
{
	POLY *a, *b;
	POLY * lc, *c, *ld, *d;
	POLY * tmp;
	int length;
	int i;

	a = la->next;

	length = len(lb);

	lc = (POLY *)malloc(sizeof(POLY));
	lc->next = NULL;
	ld = (POLY *)malloc(sizeof(POLY));
	ld->next = NULL;


	for (i = 0; i < length; i++)
	{
		c = (POLY *)malloc(sizeof(POLY));
		d = (POLY *)malloc(sizeof(POLY));

		c->coef = 0;
		c->expn = 0;
		d->coef = 0;
		c->expn = 0;

		c->next = lc->next;
		lc->next = c;
		d->next = ld->next;
		ld->next = d;
	}

	while (a)
	{
		b = la->next;

		while (b)
		{
			lc->coef = a->coef * b->coef;
			lc->expn = a->expn + b->expn;
		}
		add (lc, ld);
		tmp = lc;
		lc = ld;
		ld = tmp;
	}

	return lc;

}
int main(int argc, char *argv[])
{

	POLY *la, *lb, *lc;

	la = creat();
	lb = creat();

	show(la);
	show(lb);

	la = add(la, lb);
	show(la);

	lc = multiply(la, lb);
	show(lc);

	return EXIT_SUCCESS;
}

