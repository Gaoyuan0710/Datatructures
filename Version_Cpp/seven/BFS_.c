/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月04日 21时12分09秒
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
#include <limits.h>

#define MAX 20

int visit_ed[MAX];

/**
 * 节点类型
 */
typedef struct ArcNode 
{
	int adj;
	int weight;
	struct ArcNode *next;
}ArcNode;

/**
 * 邻接表元素类型
 */
typedef struct VertexNode
{
	char vaxdata;
	ArcNode *head;
}VertexNode;

/**
 * 邻接表
 */
typedef struct 
{
	VertexNode vertex[MAX];
	int vexnum;
	int arcnum;
}AdjList;

typedef struct 
{
	int arcs[MAX][MAX];
	char vex[MAX];
	int vexnum;
	int arcnum;
}AdjMatrix;

/**
 * 查找下标
 */
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
	return 0;
}

/**
 * 插入节点到与其有关系的顶点上
 */
AdjList *insert ( AdjList *p, int x, int y, int weight)
{
	ArcNode *q2 = p->vertex[x].head;
	ArcNode *q1 = q2;

	if (q2 == NULL)
	{
		p->vertex[x].head = ( ArcNode *)malloc(sizeof(ArcNode));

		p->vertex[x].head->adj = y;
		p->vertex[x].head->weight = weight;
		p->vertex[x].head->next = NULL;
	}

	else
	{
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
		q2->next = q1->next;
		q1->next = q2;
	}

	return p;
}

/**
 * 创建
 */
AdjList * Creat ( AdjList *p)
{
	int i;
	int x, y;
	char ch1, ch2;
	int weight;

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
		printf("%d :", i);

		ch1 = getchar();
		ch2 = getchar();
//		printf("请输入其权值\n");
//		scanf("%d", &weight);
		getchar();

		weight = 1;

		x = find(p, ch1);
		y = find(p, ch2);
		p = insert(p, x, y, weight);
		p = insert(p, y, x, weight);
	}

	return p;
}


AdjMatrix *init(AdjMatrix *G)
{
	G = (AdjMatrix *)malloc(sizeof(AdjMatrix));

	return G;
}

AdjMatrix *trans(AdjMatrix *G, AdjList *p)
{
	int i;
	int j;
	ArcNode *q;

	G->arcnum = p->arcnum;
	G->vexnum = p->vexnum;

	for (i = 1; i <= G->vexnum; i++)
	{
		G->vex[i] = p->vertex[i].vaxdata;

		for (j = 1; j <= G->vexnum; j++)
		{
			G->arcs[i][j] = INT_MAX;
		}
	}

	for (i = 1; i <= p->vexnum; i++)
	{
		q = p->vertex[i].head;

		while (q)
		{
			G->arcs[i][q->adj] = q->weight;
			G->arcs[q->adj][i] = q->weight;
			q = q->next;;
		}
	}

	return G;
}

void show_two(AdjMatrix *G)
{
	int i;
	int j;

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			if (G->arcs[i][j] == INT_MAX)
			{
				printf("~\t");
				continue;
			}
			printf("%d\t", G->arcs[i][j]);
		}
		printf("\n");
	}
}
/**
 * 展示邻接表
 */
void show(AdjList *p)
{
	int i;
	ArcNode *q;

	for (i = 1; i <= p->vexnum; i++)
	{
		printf("%d %c ", i, p->vertex[i].vaxdata);

		q = p->vertex[i].head;

		while (q != NULL)
		{
			printf("%d  ", q->adj);
			q = q->next;
		}
		printf("\n");
	}
}
int First(AdjList *p, int num)
{
	int tmp;
	ArcNode *q;
	
	q = p->vertex[num].head;


	while (q != NULL)
	{
		if (visit_ed[q->adj] != 1)
		{
			return q->adj;
		}

		q = q->next;
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

void visit(AdjList *p, int num)
{
	printf("%c\t", p->vertex[num].vaxdata);
}


void DFS (AdjList *p, int start, int end)
{
	int w;
	int tmp;

	visit (p, start);


	if (start == end)
	{
		getchar();
		getchar();
		return ;
	}


	visit_ed[start] = 1;

	w = First(p, start);
	
	printf("%d\t", w);

	if (w == -1)
	{
		return ;
	}

	while ( w != -1)
	{
		if (visit_ed[w] != 1)
		{
			DFS(p, w, end);
		}

		visit_ed[w] = 0;

		w =	Next(p, start, w);

		if ( w == -1)
		{
			return ;
		}

//		visit_ed[w] = 1;

//		printf("%d\t", w);
	}
}


int main(int argc, char *argv[])
{
	AdjList *G;

	G = (AdjList *)malloc(sizeof(AdjList));

	G = Creat(G);

	DFS(G, 1, 7);

	return EXIT_SUCCESS;
}

