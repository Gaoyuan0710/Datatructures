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
		printf("请输入其权值\n");
		scanf("%d", &weight);
		getchar();

		x = find(p, ch1);
		y = find(p, ch2);
		p = insert(p, x, y, weight);
		p = insert(p, y, x, weight);
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

void test(int *a, int num)
{

	int i;

	for (i = 1; i <=num; i++)
	{
		printf("%d\t", *(a + i));
	}
	printf("\n\n\n");
}

void test_(int a[][MAX], int m, int n)
{
	int i, j;

	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
}
void short_path(AdjMatrix *G)
{
	int begin;
	int end;
	int i;
	int j;
	int k;
	int tmp;
	int distance[MAX];
	int path[MAX][MAX] = {{0}};
	int mindistance;

	printf("请输入起始点编号\n");
	scanf("%d", &begin);
	printf("请输入目的地编号\n");
	scanf("%d", &end);


	for (i = 1; i <= G->vexnum; i++)
	{
		distance[i] = G->arcs[begin][i]; //到各点距离

		if (G->arcs[begin][i] != INT_MAX)
		{
			path[i][1] = begin;          //若可以到达，计入path
		}
	}

	path[begin][0] = 1;

	for (i = 2; i <= G->vexnum; i++)
	{
		mindistance = INT_MAX;

		for (j = 1; j <= G->vexnum; j++)
		{
			if (!path[j][0] && (distance[j] < mindistance))
			{
				k = j;
				mindistance = distance[j];
			}
		}
		

		test(distance, G->vexnum);


			if (mindistance == INT_MAX)
			{
				return ;
			}
			path[k][0] = 1;

			for (j = 1; j <= G->vexnum; j++)
			{
				if (!path[j][0] && G->arcs[k][j] < INT_MAX && (distance[k] + G->arcs[k][j] < distance[j]))
				{
					distance[j] = distance[k] + G->arcs[k][j];
					tmp = 1;
					while (path[k][tmp] != 0)
					{
						path[j][tmp] = path[k][tmp];
						tmp++;
					}
					path[j][tmp] = k;
					path[j][tmp + 1] = 0;

					test_(path, G->vexnum, G->vexnum);
				}
			}
		}
	printf("%c ----> %c最短路线为:", G->vex[begin], G->vex[end]);
//	for (i = 1; i <= G->vexnum; i++)
//	{
//		for (j = G->vexnum; path[j][0] == 0; j--)
//		{
//			;
//		}
//		j--;


	for (k = 1; path[end][k] != 0; k++)
//		for (k = 1; path[j][k] != 0; k++)
		{
//			printf("j = %d, k = %d\n", j , k);
//			printf("%5d ", path[j][k]);
//			printf("%c->", G->vex[path[j][k]]);

			printf("%c->", G->vex[path[end][k]]);
		}
		
//		if (i == end)
//		{
			printf("%c, 距离为%d\n", G->vex[end], distance[end]);
//			break;
//		}
//	}
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

/*
int main(int argc, char *argv[])
{
	AdjList *p;
	AdjMatrix *G;

	p = (AdjList *)malloc(sizeof(AdjList));

	p = Creat(p);

	show(p);

	G = init (G);

	G = trans(G, p);

	show_two(G);
//	show_result(p);

	short_path(G);

	return EXIT_SUCCESS;
}
*/
