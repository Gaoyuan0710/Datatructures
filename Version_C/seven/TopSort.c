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

#define MAXSIZE 100
#define MAX 100

typedef struct stack
{
	int data[MAXSIZE];
	int top;
}Stack;

typedef struct ArcNode 
{
	int adj;
	int weight;
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

#define MAX 100

typedef struct 
{
	int data[MAX];
	int rear, front;
}SeQueue;

SeQueue *initSeQueue ( SeQueue *p)
{
	p = malloc(sizeof(SeQueue));
	p ->front = p->rear = MAX;

	return p;
}

int in_SeQuque(SeQueue *q, int data)
{
	if ((q->rear + 1) % MAX == q->front)
	{
		return -1;
	}

	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear] = data;
		return 0;
	}
}

int out_SeQueue(SeQueue *q, int *data)
{
	if (q->front == q->rear)
	{
		return -1;
	}
	else
	{
		q->front = (q->front + 1) % MAX;
		*data = q->data[q->front];
		return 0;
	}
}

int empty_SeQueue(SeQueue *q)
{
	if (q->front == q->rear)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

Stack * init_stack()
{
	Stack * s;

	s = malloc(sizeof(int) * MAXSIZE);
	s->top = -1;

	return s;
}

int empty_stack(Stack * s)
{
	if (s->top == -1)
	{
		return 1;
	}

	return 0;

}

int push_stack(Stack * s, int x)
{
	if (s->top == MAXSIZE - 1)
	{
		return 0;
	}

	else
	{
		s->top++;
		s->data[s->top] = x;
		return 1;
	}
}

int pop_stack(Stack * s, int * data)
{
	if (empty_stack(s) == 1)
	{
		return 0;
	}

	else
	{
		*data = s->data[s->top];
		s->top--;
		return 1;
	}
}

int top_stack(Stack * s, int * data)
{
	if (empty_stack(s) == 1)
	{
		return 0;
	}

	else 
	{
		*data = s->data[s->top];
		return 1;
	}
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

AdjList * add ( AdjList *p, int x, int y, int weight)
{
	ArcNode *q2 = p->vertex[x].head;

//	printf("%p\n", q2);

	ArcNode *q1 = q2;

	if (q2 == NULL)
	{
		p->vertex[x].head = ( ArcNode *)malloc(sizeof(ArcNode));

		p->vertex[x].head->adj = y;
		p->vertex[x].head->weight = weight;
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
		q2->weight = weight;
//		q1->next = q2->next;
		q2->next = q1->next;
		q1->next = q2;
	}

	return p;
}

AdjList * Creat ( AdjList *p)
{
	int weight;
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

		printf("请输入权值:\n");
		scanf("%d", &weight);
		getchar();

//		printf("x = %d, y = %d\n", x, y);

		p = add(p, x, y, weight);
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

void find_ID (AdjList *G, int *indegree)
{
	int i;
	ArcNode *p;

	for (i = 0; i < G->vexnum; i++)
	{
		indegree[i] = 0;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		p = G->vertex[i].head;

		while  (p)
		{
			indegree[p->adj]++;
			p = p->next;
		}
	}
}

int vex[MAX];

int TopoSort(AdjList *G)
{
	SeQueue *Q;
	ArcNode *p;
	int indegree[MAX];
//	int vex[MAX];
	int i, count, k;

	Q = initSeQueue(Q);

	find_ID(G, indegree);

	for (i = 0; i < G->vexnum; i++)
	{
		if (indegree[i] == 0)
		{
			in_SeQuque(Q, i);
		}
	}
	count = 0;

	for (i = 0; i < G->vexnum; i++)
	{
		vex[i] = 0;
	}

	while (empty_SeQueue(Q) != 1)
	{
		out_SeQueue(Q, &i);
		printf("%c", G->vertex[i].vaxdata);
		count++;
		p = G->vertex[i].head;

		while (p)
		{
			k = p->adj;
			indegree[k]--;
			if (indegree[k] == 0)
			{
				in_SeQuque(Q, k);
			}

			if (vex[k] + p->weight > vex[k])
			{
				vex[k] = vex[k] + p->weight;
			}
			p = p->next;
		}

	}
	if (count < G->vexnum)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Criticalpath(AdjList *G)
{
	ArcNode *p;
	int i, j, k ,a, ei, li, flag = 0;
	int vl[MAX];
	Stack *S;

	if (!TopoSort(G))
	{
		return 0;
	}
	for (i = 0; i < G->vexnum; i++)
	{
		vl[i] = vex[G->vexnum - 1];
	}

	while ( empty_stack(S) != 1)
	{
		pop_stack(S, &j);
		p = G->vertex[j].head;
		while (p)
		{
			k = p->adj;
			a = p->weight;

			if ((vl[k] - a) < vl[j])
			{
				vl[j] = vl[k] - a;
			}
			p = p->next;
		}
	}
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->vertex[i].head;
		while (p)
		{
			k = p->adj;
			a = p->weight;
			ei = vex[j];
			li = vl[k] - a;

			if (ei == li)
			{
				flag = 1;
			}
			p = p->next;
		}
	}
}

int main(int argc, char *argv[])
{
	AdjList *p;

	p = (AdjList *)malloc(sizeof(AdjList));

	p = Creat(p);

	show(p);

	Criticalpath(p);

	return EXIT_SUCCESS;
}

