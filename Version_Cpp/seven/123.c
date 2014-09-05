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
#define MAXSIZE 100

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

	s = malloc(sizeof(Stack));
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
/*
//邻接矩阵的遍历
typedef struct{
	int amount;
	int *vex;
	int **matrix;
}Graph;
*/
//打印从i到j的所有回路
void PrintAllPath(AdjMatrix *G, int i, int j)
{
	int tmp;

	if( i > G->vexnum || j > G->vexnum || i < 0 || j < 0)
		return;

	//初始化访问标识
//	bool *IsVisted = (bool *)malloc(sizeof(bool) * G.amount);
//	for(int k = 0; k < G.amount; k++)
//		IsVisted[k] = false;

	int x;
	int visit[MAX];

	printf("ooo\n");
	for (x = 0; x <= G->vexnum; x++)
	{
		visit[x] = 0;
	}

//	std::stack<int> s_Gnode;
//	s_Gnode.push(G.vex[i]);
//	IsVisted[i] = true;

	Stack *s;
	s = init_stack();

	push_stack(s, i);
	visit[i] = 1;

	//程序的关键是设置了pop_node和top_node; 
	//因为图是按照序号的从小到大访问，所以一旦有pop_node,必须从pop_node+1开始访问
	int top_node;
	int pop_node = -1;//最开始pop_node从0开始遍历

//	while( !s_Gnode.empty()){
while (empty_stack(s) != 1) {
//	top_node = s_Gnode.top();

	top_stack(s, &top_node);

		int k;
		for( k = top_node+1; k <= G->vexnum; k++ ){
//			if(G.matrix[top_node][k] == 1 && IsVisted[k] == false){

			if (G->arcs[top_node][k] != INT_MAX && visit[k])
//如果当前节点是j节点，则打印栈中的所有元素
				if(G->vex[k] == G->vex[j]){
			//		s_Gnode.push(G.vex[k]);
			
					push_stack(s, k);

			//		PrintStack(s_Gnode);
			//		pop_node = s_Gnode.top();
			
					pop_stack(s, &top_node);
				//	s_Gnode.pop();
					break;
				}
				else{
					pop_node = -1; //注意每次pop之后有新的节点进栈，需要将pop_node归零
				//	IsVisted[k] = true;
				
					visit[k] = 1;
	//				s_Gnode.push(G.vex[k]);
	
					push_stack(s, k);

					break;
				}
			}
		//for

		//如果所有邻接的节点都被访问了
		if(k == G->vexnum){
	//		pop_node = s_Gnode.top();
	
			pop_stack(s, &pop_node);

	//将之前的所有邻接节点置为未访问
	int c;
			for(c = 0; c <= G->vexnum; c++)
				//注意避免出现访问环，需要判断邻接点是否包含起始节点
				if(G->arcs[pop_node][c] != INT_MAX && (c != i) )
				  visit[c] = 0;
				  //	IsVisted[c] = false;
//			s_Gnode.pop();

			pop_stack(s, &tmp);
		}
	}
}
void PinntAStack(Stack *s)
{
	int tmp;

	while (!empty_stack(s))
	{
		pop_stack(s, &tmp);

		printf("%d\t", tmp);


	}

	printf("\n");
}
/*
void PrintStack(std::stack<int> s_Gnode){
	while( !s_Gnode.empty() ){
		printf("%d\t", s_Gnode.top());
		s_Gnode.pop();
	}
	printf("\n");
}
*/




/*
void path(int start, int end, AdjList *G)
{
	int visit[MAX];
	Stack *s;
	ArcNode *p;
	int i;
	int tmp;

	s = init_stack();

	for (i = 0; i <= G->vexnum; i++)
	{
		visit[i] = 0;
	}

	visit[start] = 1;
	push_stack(s, start);

	p = G->vertex[start].head;

	do
	{
		if (p && visit[p->adj] == 0)
		{
			if (visit[p->adj] == 0)
			{
				push_stack(s, p->adj);
			}

			if (p->adj == end)
			{
				for (i = 1; i <= s->top; i++)
				{
					printf("%d", s->data[i]);
				}
				printf("\n");
				visit[end] = 0;
				pop_stack(s, &tmp);
			}
			else
			{
				top_stack(s, &tmp);
				p = G->vertex[tmp].head;
			}
		}
		else
		{

		}
	}
}
*/
/*
void DFS (int p, int path[][MAX])
{
	int i, j;void dfs(int p)
	{
	    int i, j;
	
	    for(i=1; i<=n; i++)
		      {
			          if(graph[p][i]==1)
						        {
								            if(i == y)///如果深搜到了终点，就输出刚才经过的路径
											              {
														                  for(j=0; j<m; j++)
																			                {
																							                    printf("%-5d", stack[j]);
																												                }
																		                  printf("%-5d\n", y);
																						              }
											            else///如果该点不是终点
														              {
																	                  graph[p][i] = 0;
																	                  stack[m] = i;///将该点存起来
																	                  m++;
																	                  dfs(i);///接着深搜
																					                  graph[p][i] = 1;
																									                  m--;
																													              }
														        }
					      }
	}
}

*/




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

	PrintAllPath(p, 1, 7);


	
	return EXIT_SUCCESS;
}

