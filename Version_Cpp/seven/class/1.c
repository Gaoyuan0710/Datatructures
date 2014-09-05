 /*
 * =====================================================================================
 *
 *       Filename:  class_fist
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

/**
 * 节点类型
 */
typedef struct ArcNode 
{
	int adj;
//	int weight;
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
AdjList *insert ( AdjList *p, int x, int y)
{
	ArcNode *q2 = p->vertex[x].head;
	ArcNode *q1 = q2;

	if (q2 == NULL)
	{
		p->vertex[x].head = ( ArcNode *)malloc(sizeof(ArcNode));

		p->vertex[x].head->adj = y;
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
		getchar();

		x = find(p, ch1);
		y = find(p, ch2);
		p = insert(p, x, y);
	}

	return p;
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

/**
 * 查找入度
 */
void find_in_ID (AdjList *G, int *indegree)
{
	int i;
	ArcNode *p;

	for (i = 0; i <= G->vexnum; i++)
	{
		indegree[i] = 0;
	}

	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vertex[i].head;

		while  (p)
		{
			indegree[p->adj]++;
			p = p->next;
		}
	}
}

/**
 * 查找出度
 */
void find_out_ID (AdjList *G, int *outdegree)
{
	int i;
	ArcNode *p;

	for (i = 0; i <= G->vexnum; i++)
	{
		outdegree[i] = 0;
	}

	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vertex[i].head;

		while  (p)
		{
			outdegree[i]++;
			p = p->next;
		}
	}
}


/**
 * 最终结果的展示
 */
void show_result(AdjList *p)
{
	int indegree[MAX], outdegree[MAX];
	int i;

	find_in_ID(p, indegree);
	find_out_ID(p, outdegree);

	printf("顶点\t入度\t出度\t度\n");

	for (i = 1; i <= p->vexnum; i++)
	{
		printf("%c\t%d\t%d\t%d\n",p->vertex[i].vaxdata, indegree[i], outdegree[i], indegree[i] + outdegree[i]);
	}


}

int main(int argc, char *argv[])
{
	AdjList *p;

	p = (AdjList *)malloc(sizeof(AdjList));

	p = Creat(p);          ///创建邻接表

	show(p);               ///展示

	show_result(p);        ///展示最终结果


	return EXIT_SUCCESS;
}

