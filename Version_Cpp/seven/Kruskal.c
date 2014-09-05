/*
 * =====================================================================================
 *
 *       Filename:  Kruskal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月23日 22时15分01秒
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
#define M 20


typedef struct
{
	int begin;
	int end;
	int weight;
}edge;
typedef struct 
{
	int adj;
	int weight;
 }AdjMatrix[MAX][MAX];
typedef struct
{
	AdjMatrix arc;
	int vexnum,arcnum;
}MGraph;
 //函数声明
void CreatGraph (MGraph *);
void sort(edge *, MGraph *);
void MiniSpanTree(MGraph *);
int  Find(int *, int );
void Swapn(edge*,int,int);


void CreatGraph(MGraph *G)
{
	int i, j, n, m;
	printf("请输入顶点数及边数:");
	scanf("%d%d",&G->vexnum, &G->arcnum);
	for (i = 1; i <= G->vexnum; i++)
	{
		for(j = 1;j <= G->vexnum; j++)
		{
			G->arc[i][j].adj = G->arc[j][i].adj = 0;
		}
	}
	printf("请输入两点编号以及权值\n");
	for (i = 1; i <= G->arcnum; i++)
	{
		scanf("%d%d",&n,&m);
		G->arc[n][m].adj = G->arc[m][n].adj = 1;
		scanf("%d", &G->arc[n][m].weight);
		G->arc[m][n].weight = G->arc[n][m].weight;
	}

	printf("邻接矩阵为:\n");
	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1;j <= G->vexnum; j++)
		{
			if(G->arc[i][j].adj == 1)
			{
				printf("%d",G->arc[i][j].weight);
			}
			else
			{
				printf("%d",G->arc[i][j].adj);
			}
			printf("\n");
		}
	}
}
void sort(edge edges[], MGraph * G)
	{
		int i,j;
		
		for (i = 1; i < G->arcnum; i++)
		{
			for(j = i+1;j <= G->arcnum;j++)
			{
				if (edges[i].weight > edges[j].weight)
				{
					Swapn(edges,i,j);
				}
			}
		}
		printf("按权值排序之后的边顺序为:\n");
		for(i = 1; i <= G->arcnum; i++)
		{
			printf("%d. <%d,%d> %d\n", i, edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
	void Swapn (edge * edges,int i,int j)
	{
		int temp;
		temp = edges[i].begin;
		edges[i].begin = edges[j].begin;
		edges[j].begin = temp;
		temp = edges[i].end;
		edges[i].end = edges[j].end;
		edges[j].end = temp;
		temp = edges[i].weight;
		edges[i].weight = edges[j].weight;
		edges[j].weight = temp;
	}
void MiniSpanTree( MGraph *G)
{
	int i, j, n, m, Mincost = 0;
		int k = 1;
		int parent[M];
		edge edges[M];
		
		for (i = 1; i < G->vexnum; i++)
		{
			for (j = i + 1; j <= G->vexnum; j++)
			{
				if (G->arc[i][j].adj == 1)
				{
					edges[k].begin = i;
					edges[k].end = j;
					edges[k].weight = G->arc[i][j].weight;
					k++;
				}
			}
		}
		
		sort(edges, G);

		for (i = 1; i <= G->arcnum; i++)
		{
			parent[i] = 0;
		}
		
		printf("最小生成树为:\n");
		
		for(i=1;i<=G->arcnum;i++)
		{
			n = Find(parent, edges[i].begin);
			m = Find(parent, edges[i].end);
			if (n != m)
			{
				parent[n] = m;
				printf(" <%d,%d> %d\n", edges[i].begin, edges[i].end, edges[i].weight);
				Mincost += edges[i].weight;
			}
		}
		printf("最小生成树权值之和为：Mincost = %d\n", Mincost);
	}

int Find(int * parent, int f)
{
		while(parent[f] > 0)
		{
			f = parent[f];
		}
		return f;
	}
	void main()
	{
		MGraph *G;
		G = (MGraph *)malloc(sizeof(MGraph));
		CreatGraph(G);
		MiniSpanTree(G);
	}
