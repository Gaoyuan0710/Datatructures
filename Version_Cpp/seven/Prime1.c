/*
 * =====================================================================================
 *
 *       Filename:  Prime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月21日 21时20分01秒
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
#define INFINITY 32768

typedef struct 
{
	int arcs[MAX][MAX];
	char vex[MAX];
	int vexnum;
	int arcnum;
}AdjMatrix;

AdjMatrix *init (AdjMatrix *G)
{
	G = (AdjMatrix *)malloc(sizeof(AdjMatrix));

	return G;
}

int find_num(AdjMatrix *G, char ch)
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

void Creat(AdjMatrix *G)
{
	int i, j;
	int tmp1, tmp2;
	char tmp[2];
	int weight;

	printf("请输入无向网中的顶点:");
	scanf("%d", &G->vexnum);

	printf("请输入无向网中的边数：");
	scanf("%d", &G->arcnum);
	getchar();

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			G->arcs[i][j] = INFINITY;
		}
	}

	printf("请输入图中%d个顶点\n", G->vexnum);

	for (i = 1; i <= G->vexnum; i++)
	{
		printf("No.%d:", i);
		scanf("%c", &G->vex[i]);
		getchar();
	}

	printf("请输入图中%d个边\n", G->arcnum);

	for (i = 1; i <= G->arcnum; i++)
	{
		printf("No,%d\n", i);

//		printf("弧头;");
//		scanf("%d", &tmp1);
//		printf("弧尾");
//		scanf("%d", &tmp2);

		scanf("%s", tmp);
		tmp1 = find_num(G, tmp[0]);
		tmp2 = find_num(G, tmp[1]);

//		printf("%d, %d\n", tmp1, tmp2);

		printf("权值\n");
		scanf("%d", &weight);

		G->arcs[tmp1][tmp2] = weight;
		G->arcs[tmp2][tmp1] = weight;
	}

	printf("创建完成\n");

}
void show(AdjMatrix *G)
{
	int i, j;

	for (i = 1; i <=  G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			if (G->arcs[i][j] == INFINITY)
			{
				printf("~\t");
				continue;
			}
			printf("%d\t", G->arcs[i][j]);
		}

		printf("\n");
	}
	printf("\n");
}

void Prime(AdjMatrix *G, int start)
{
	int min;
	int i, j;
	int flag;
	struct
	{
		int adjvex;
		int lowcost;
	}closedge[MAX];

	closedge[start].lowcost = 0;

	for (i = 1; i <= G->vexnum; i++)
	{
		if ( i != start)
		{
			closedge[i].adjvex = start;
			closedge[i].lowcost = G->arcs[start][i];
		}
	}

	for (i = 1; i <= G->vexnum - 1; i++)
	{
		min = INFINITY;

		for (j = 1; j <= G->vexnum; j++)
		{
			if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)
			{
				flag = j;
				min = closedge[j].lowcost;
			}
		}
		closedge[flag].lowcost = 0;

		printf("加入%c\n", G->vex[flag]);

		for (j = 1; j <= G->vexnum; j++)
		{
			if ( j != flag && G->arcs[flag][i] < closedge[j].lowcost)
			{
				closedge[j].lowcost = G->arcs[flag][j];
				closedge[j].adjvex = min;
			}
		}
	}

}
int main(int argc, char *argv[])
{
	AdjMatrix *G;

	G = init(G);
	Creat(G);
	show(G);
	Prime(G, 1);

	return EXIT_SUCCESS;
}

