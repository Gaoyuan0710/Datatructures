/*
 * =====================================================================================
 *
 *       Filename:  class_second.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月03日 19时37分39秒
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
#define INFIITY 32767

/*
 * 定义结构类型
 */

typedef struct 
{
	int arcs[MAX][MAX];
	char vex[MAX];
	int vexnum;
	int arcnum;
}AdjMatrix;

/*
 * 初始化
 */
AdjMatrix *init (AdjMatrix *G)
{
	G = (AdjMatrix *)malloc(sizeof(AdjMatrix));

	return G;
}

/*
 * 查找顶点对应的下标
 */
int find_num (AdjMatrix *G, char ch)
{
	int i;

	for (i = 1; i <= G->vexnum; i++)
	{
		if (G->vex[i] == ch)
		{
			return i;
		}
	}

	return 0;
}

/*
 * 创建
 */
void Creat(AdjMatrix *G)
{
	int i, j;
	int temp1, temp2;
	char tmp[2];

	printf("请输入有向图中的顶点数:");
	scanf("%d", &G->vexnum);

	printf("请输入有向图中的边数:");
	scanf("%d", &G->arcnum);

	getchar();

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			G->arcs[i][j] = INFIITY;
		}
	}

	printf("请输入顶点名称:\n");

	for (i = 1; i <= G->vexnum; i++)
	{
		printf("No.%d:", i);
		scanf("%c", &G->vex[i]);
		getchar();
	}

	printf("请输入图中%d个边\n", G->arcnum);
	for (i = 1; i <= G->arcnum; i++)
	{
		printf("No.%d:", i);
		scanf("%s", tmp);

		temp1 = find_num(G, tmp[0]);
		temp2 = find_num(G, tmp[1]);

		G->arcs[temp1][temp2] = 1;
	}

	printf("创建完成\n");
}

void show(AdjMatrix *G)
{
	int i, j;

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			if (G->arcs[i][j] == INFIITY)
			{
				printf("~\t");
				continue;
			}
			printf("%d\t", G->arcs[i][j]);
		}

		printf("\n");
	}
}

void find_ID (AdjMatrix *G, int *indegree, int *outdegree)
{
	int i, j;

	for (i = 0; i <= G->vexnum; i++)
	{
		indegree[i] = 0;
		outdegree[i] = 0;
	}

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			if (G->arcs[i][j] == 1)
			{
				indegree[j]++;
				outdegree[i]++;
			}
		}
	}
}

void show_result(AdjMatrix *G)
{
	int i, j;
	int indegree[MAX], outdegree[MAX];


	find_ID(G, indegree, outdegree);

	printf("顶点\t入度\t出度\t度\n");

	for (i = 1; i <= G->vexnum; i++)
	{
		printf("%c\t%d\t%d\t%d\n", G->vex[i], indegree[i], outdegree[i], indegree[i] + outdegree[i]);
	}
}

int main(int argc, char *argv[])
{
	AdjMatrix *G;

	G = init(G);
	Creat(G);
	show(G);
	show_result(G);

	return EXIT_SUCCESS;
}

