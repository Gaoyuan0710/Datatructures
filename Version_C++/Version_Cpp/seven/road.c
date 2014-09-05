/*
 * =====================================================================================
 *
 *       Filename:  road.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月02日 20时03分19秒
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

#define MAX 100

int color[30] = {0};

typedef struct 
{
	char vexs[MAX];
	int arcs[MAX][MAX];
	int vnum, arcnum;
}Graph;

int Locate(char flag, Graph *G)
{
	int i;

	for (i = 1; i <= G->vnum; i++)
	{
		if (G->vexs[i] == flag)
		{
			return i;
		}
	}

	return 0;
}

Graph * Creat_Cross(Graph *G)
{
	int i;
	int j;
	int flag;
	int num;
	char tmp;

	G = (Graph *)malloc(sizeof(Graph));

	printf("请输入岔路口的道路数:");
	scanf("%d", &G->vnum);

	getchar();


	for (i = 1; i <= G->vnum; i++)
	{
		  for (j = 1; j <= G->vnum; j++)
		  {
			  if (i != j)
			  {
				  G->arcs[i][j] = 1;
			  }
			  else
			  {
				  G->arcs[i][j] = 0;
			  }
		  }
	  }

	printf("请输入个路口名称:");

	for (i = 1; i <= G->vnum; i++)
	{
		scanf("%c", &G->vexs[i]);
		getchar();
	}

	printf("请输入单向驶入的道路个数:");
	scanf("%d", &num);
	getchar();

	for (i = 1; i <= num; i++)
	{
		printf("请输入第%d条单向驶入道路", i);
		scanf("%c", &tmp);

		flag = Locate(tmp, G);

		printf("flag = %d\n", flag);

		for (j = 1; j <= G->vnum; j++)
		{
			G->arcs[flag][j] = 0;
		}
	}

	printf("请输入单向使出的道路个数:");
	scanf("%d", &num);
	getchar();


	for (i = 1; i <= num; i++)
	{
		printf("请输入第%d条单向驶出道路", i);
		scanf("%c", &tmp);

		flag = Locate(tmp, G);

		printf("flag = %d\n", flag);

		for (j = 1; j <= G->vnum; j++)
		{
			G->arcs[j][flag] = 0;
		}
	}

	return G;
}

void show(Graph *G)
{
	int i, j;

	for (i = 1; i <= G->vnum; i++)
	{
		for (j = 1; j <= G->vnum; j++)
		{
			printf("%5d", G->arcs[i][j]);
		}

		printf("\n");
	}
}

int main(int argc, char *argv[])
{

	Graph *G;

	G = Creat_Cross(G);

	show(G);


	return EXIT_SUCCESS;
}

