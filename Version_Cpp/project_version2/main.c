/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月06日 22时42分15秒
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
#include <string.h>

#define MAX_NUM 40
#define MAX 40

typedef struct infomation
{
	int num;
	char name[50];
	char introduction[100];
}INFOMATION;

typedef struct ArcNode
{
	int adjvex;
	int lenght;
	struct ArcNode *next;
}ArcNode;

typedef struct
{
	int num;
	char name[50];
	ArcNode *head;
}VertexNode;

typedef struct
{
	VertexNode vertex[MAX_NUM];
	int vexnum;
	int arcnum;
}Graph;

Graph *insert(Graph *G, int begin, int end, int lenght)
{
	ArcNode *p = G->vertex[begin].head;
	ArcNode *q = p;

	if (p == NULL)
	{
		G->vertex[begin].head = (ArcNode *)malloc(sizeof(ArcNode));
		G->vertex[begin].head->adjvex = end;
		G->vertex[begin].head->lenght = lenght;
		G->vertex[begin].head->next = NULL;
	}
	else
	{
		while (p->adjvex < end)
		{
			q = p;
			p = p->next;

			if (p == NULL)
			{
				break;
			}
		}

		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = end;
		p->lenght = lenght;
		p->next = q->next;
		q->next = p;
	}

	return G;
}
Graph *init_Graph(INFOMATION *info)
{
	Graph *G;
	int i;
	int begin;
	int end;
	int lenght;

	G = (Graph *)malloc(sizeof(Graph));
	printf("请输入景点数目:\n");
	scanf("%d", &G->vexnum);
	printf("请输入道路数目:\n");
	scanf("%d", &G->arcnum);

	for (i = 1; i <= G->vexnum; i++)
	{
		printf("请输入%d个景点的信息\n", i);
		printf("编号：");
		scanf("%d", &(info + i)->num);
		printf("名称：");
		scanf("%s", (info + i)->name);
		printf("介绍：");
		scanf("%s", (info + i)->introduction);
		G->vertex[i].head = NULL;
		G->vertex[i].num = (info + i)->num;
		strcpy(G->vertex[i].name, (info + i)->name);
	}

	for (i = 1; i <= G->arcnum; i++)
	{
		printf("请输入%d条路径起点", i);
		scanf("%d", &begin);
		printf("请输入%d条路径终点", i);
		scanf("%d", &end);
		printf("请输入其长度");
		scanf("%d", &lenght);

		G = insert(G, begin, end, lenght);
	}

	return G;
}

void show (Graph *G, INFOMATION *info)
{
	int i;

	ArcNode *p;

	for (i = 1; i <= G->vexnum; i++)
	{
//		printf("%d", i, G->vertex[i].num);
		printf("%d, %d", i, G->vertex[i].num);
		p = G->vertex[i].head;

		while ( p != NULL)
		{
			printf("%d  ", p->adjvex);
			p = p->next;
		}
		printf("\n");
	}

	for (i = 1; i <= G->vexnum; i++)
	{
	//	printf("%d :", i);
		p = G->vertex[i].head;

		while ( p != NULL)
		{
			printf("%s ---->  %s   %d\n",(info + i)->name, (info + p->adjvex)->name, p->lenght);
			p = p->next;
		}
	}
}

void short_path(Graph *G)
{
	int begin;
	int end;

	printf("请输入出发点编号:");
	scanf("%d", &begin);
	printf("请输入目的地:");
	scanf("%d", &end);


}

/*
int main(int argc, char *argv[])
{
	Graph *G;
	INFOMATION info[MAX];

	G = init_Graph(info);
	show(G, info);

	return EXIT_SUCCESS;
}
*/
