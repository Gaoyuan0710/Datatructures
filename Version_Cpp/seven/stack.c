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
#define MAXSIZE 10000

typedef struct stack
{
	int data[MAXSIZE];
	int top;
}Stack;



#define MAX 20

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

/*
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
*/
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
int visit_ed[MAX] = {0};

void All_path(AdjMatrix *G, Stack *s, int start, int end)
{
	int i, j;
	int tmp;
	int flag = 0;

	visit_ed[start] = 1;

	push_stack(s, start);
	
	for (i = 1; i <= G->vexnum; i++)
	{
		if (G->arcs[start][i] != INT_MAX && visit_ed[i] != 1)
		{
	//			printf("from %d to %d\n", start, i);
	//			getchar();
	//		flag = 1;
		//	printf("访问的%d\n", i);

			if (i == end)
			{
				for (j = 0; j <=s->top; j++)
				{
					printf("%-5d", s->data[j]);
				}
				printf("%-5d\n", end);
				visit_ed[end] = 0;
			//	pop_stack(s, &tmp);
	//			return ;
			}
			else
			{
		//		printf(" i = %dstart = %d\n", i, start);
		
			All_path(G, s, i, end);
				pop_stack(s, &tmp);
				visit_ed[tmp] = 0;
			}
		}
	}
//	if (flag == 0)
//	{
//		printf("从%d推出:\n", start);
//	}
}
int main(int argc, char *argv[])
{
	Stack *s;
	AdjList *G;
	AdjMatrix *p;
	int num;

	G = (AdjList *)malloc(sizeof(AdjList));

	s = init_stack();

	G = Creat(G);

	p = init(p);

	p = trans(p, G);

//	push_stack(s, 1);

//	stack[0] = 1;

	All_path(p, s, 1, 7);

	
	return EXIT_SUCCESS;
}

