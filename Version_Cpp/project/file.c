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







Graph *insert(Graph *G, int begin, int end, int lenght)
{
	ArcNode *p = G->vertex[begin].head;
	ArcNode *q = p;

	if (p == NULL)
	{
		G->vertex[begin].head = (ArcNode *)malloc(sizeof(ArcNode));
		G->vertex[begin].head->adj = end;
		G->vertex[begin].head->weight= lenght;
		G->vertex[begin].head->next = NULL;
	}
	else
	{
		while (p->adj < end)
		{
			q = p;
			p = p->next;

			if (p == NULL)
			{
				break;
			}
		}

		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adj = end;
		p->weight = lenght;
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
		printf("%d, %d", i, G->vertex[i].num);
		p = G->vertex[i].head;

		while ( p != NULL)
		{
			printf("%d  ", p->adj);
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
			printf("%s ---->  %s   %d\n",(info + i)->name, (info + p->adj)->name, p->weight);
			p = p->next;
		}
	}
}

AdjMatrix  *trans_file(Graph *p, AdjMatrix *G)
{
	int i;
	int j;
	ArcNode *q;

	G->arcnum = p->arcnum;
	G->vexnum = p->vexnum;

	for (i = 1; i <= G->vexnum; i++)
	{
	//`	G->vex[i] = p->vertex[i].name;

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
void write_file(AdjMatrix *G, INFOMATION *info, char *file)
{
	int i, j;


	FILE *fp;

	fp = fopen(file, "w");

	fprintf(fp, "%d\n", G->vexnum);
	fprintf(fp, "%d\n", G->arcnum);

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			fprintf(fp, "%d", G->arcs[i][j]);
			fputc('\t', fp);
		}
		fputc('\n', fp);
	}


	for (i = 1; i <= G->arcnum; i++)
	{
		fprintf(fp, "%d %s %s\n", (info + i)->num, (info + i)->name, (info + i)->introduction);
	}

	fclose(fp);
}
void read_file(AdjMatrix *G, INFOMATION *info, char *file)
{
	int i, j;

	FILE *fp;

	fp = fopen(file, "r");

	fscanf(fp, "%d", &G->vexnum);
	fgetc(fp);
	fscanf(fp, "%d", &G->arcnum);

	fgetc(fp);

	printf("vexnum = %d\narcnum = %d\n", G->vexnum, G->arcnum);

	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; j <= G->vexnum; j++)
		{
			fscanf(fp, "%d", &G->arcs[i][j]);
		//	fgetc(fp);
		}
		fgetc(fp);
	}

	for (i = 1; i <= G->arcnum; i++)
	{
		fscanf(fp, "%d %s %s\n", &(info + i)->num, (info + i)->name, (info + i)->introduction);
	}

	fclose(fp);
}
int main(int argc, char *argv[])
{

	int i, j;

	AdjMatrix *p;
	AdjMatrix *q;

	p = (AdjMatrix *)malloc(sizeof(AdjMatrix));
	q = (AdjMatrix *)malloc(sizeof(AdjMatrix));

	Graph *G;
	Graph *Y;

	INFOMATION info[MAX];
	INFOMATION test[MAX];


	read_file(q, info, "info.txt");

	for (i = 1; i <= q->vexnum; i++)
	{
		for (j = 1; j <= q->vexnum; j++)
		{
			printf("%d\t", q->arcs[i][j]);
		}
		printf("\n");
	}
	for (i = 1; i <= q->arcnum; i++)
	{
		printf("%d\t%s\t%s\n", (info + i)->num, (info + i)->name, (info + i)->introduction);
	}

	return EXIT_SUCCESS;
}

