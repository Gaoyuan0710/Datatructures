/*
 * =====================================================================================
 *
 *       Filename:  Adj.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月11日 18时26分38秒
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

#define MAX 20

int visit_ed[MAX] = {0};

typedef struct ArcNode 
{
	int adj;
//	int weight;
	struct ArcNode *next;
}ArcNode;

typedef struct VertexNode
{
	char vaxdata;
	ArcNode *head;
}VertexNode;

typedef struct 
{
	VertexNode vertex[MAX];
	int vexnum;
	int arcnum;
}AdjList;

void visit (AdjList *p, int num)
{
	printf("%c\t", p->vertex[num].vaxdata);

}

int First(AdjList *p, int num)
{
	int tmp;
	ArcNode *q;
	
	q = p->vertex[num].head;

//	printf("\n%d\n", q->adj);

	while (q != NULL)
	{
//		printf("\n%d\n", q->adj);

//		if (q->adj == 2)
//		{
//			printf("daole%d\n", q->next->adj);
//		}
		if (visit_ed[q->adj] != 1)
		{
			return q->adj;
		}

		q = q->next;

//		printf("\n%d\n", q->adj);
	}

	return -1;

}

int Next(AdjList *p, int num, int v0)
{
	int tmp;
	ArcNode *q;

	q = p->vertex[num].head;

	while (q)
	{
		if (q->adj != v0 && visit_ed[q->adj] != 1)
		{
			return q->adj;
		}
		q = q->next;
	}

	return -1;


}
void DFS (AdjList *p, int v0)
{
	int w;
	int tmp;

	visit (p, v0);

//	printf("test %c\n", p->vertex[v0].vaxdata);

	visit_ed[v0] = 1;

	w = First(p, v0);
//	tmp = w;

//	printf("第一个%d\n", w);
	
	printf("%d\t", w);

	if (w == -1)
	{
		return ;
	}

	while ( w != -1)
	{
		if (visit_ed[w] != 1)
		{
			DFS(p, w);
		}

	//	printf("dd %d\n", w);
		w =	Next(p, v0, w);

		if ( w == -1)
		{
			return ;
		}

		printf("%d\t", w);
	//	printf("下一个%d\n", w);
	}

//	w = First(p, tmp);

//	printf("d = %d\n", w);


}

int find (AdjList *p, char ch)
{
	int i;

	for (i = 1; i <= p->vexnum; i++)
	{
		if (p->vertex[i].vaxdata == ch)
		{
			return i;
		}
	}

	return ;
}

AdjList * add ( AdjList *p, int x, int y)
{
	ArcNode *q2 = p->vertex[x].head;

//	printf("%p\n", q2);

	ArcNode *q1 = q2;

	if (q2 == NULL)
	{
		p->vertex[x].head = ( ArcNode *)malloc(sizeof(ArcNode));

		p->vertex[x].head->adj = y;
		p->vertex[x].head->next = NULL;

//		printf("  q2 %d  \n", q2->adj);
	//	p->vertex[x].head = q2;
	}

	else
	{
//	printf("q2->adj %d\n", q2->adj);
		while (q2->adj < y)
		{
			q1 = q2;
			q2 = q2->next;

			if (q2 == NULL)
			{
				break;
			}
		}

		q2 = (ArcNode *)malloc(sizeof(ArcNode));
		q2->adj = y;
//		q1->next = q2->next;
		q2->next = q1->next;
		q1->next = q2;
	}

	return p;
}

AdjList * Creat ( AdjList *p)
{
	int i;
	int x, y;
	char ch1, ch2;

	printf("请输入顶点的个数：");
	scanf("%d", &p->vexnum);
	printf("请输入边的个数 ：");
	scanf("%d", &p->arcnum);
	getchar();
	
	printf("请输入各个顶点:");

	for (i = 1; i <= p->vexnum; i++)
	{

		scanf("%c", &p->vertex[i].vaxdata);
		p->vertex[i].head = NULL;
	}
	getchar();
	printf("请输入各条边\n");

	for (i = 1; i <= p->arcnum; i++)
	{
	//	fflush(stdin);


		printf("%d :", i);

		ch1 = getchar();
		ch2 = getchar();
		getchar();

		x = find(p, ch1);
		y = find(p, ch2);

//		printf("x = %d, y = %d\n", x, y);

		p = add(p, x, y);
	}

	return p;
}

void show(AdjList *p)
{
	int i;
	ArcNode *q;

	for (i = 1; i <= p->vexnum; i++)
	{
		printf("%d %c ", i, p->vertex[i].vaxdata);

		q = p->vertex[i].head;

//		printf("test %p", q);

		while (q != NULL)
		{
			printf("%d  ", q->adj);
			q = q->next;
		}
		printf("\n");
	}

	printf("\n\nok\n");
}
int main(int argc, char *argv[])
{
	AdjList *p;

	p = (AdjList *)malloc(sizeof(AdjList));

	p = Creat(p);

	show(p);

	DFS(p, 1);

	return EXIT_SUCCESS;
}

