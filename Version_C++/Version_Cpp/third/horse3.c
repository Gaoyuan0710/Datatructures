/*
 * =====================================================================================
 *
 *       Filename:  horse2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月13日 22时39分47秒
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

#define MAXSIZE 100
#define STACKINCREASE 10
#define N   6
#define TRUE   1
#define FALSE  0


int i_i, j_j;
int tmp_p[N][N] = {0};
typedef struct chess
{
	int x;
	int y;
	int dir_choose;
	int flag;
//	int dir[8];
}CHESS;

int map[N][N][8];   //存放下一步方向
int board[N][N][8];  
int weight[N][N];
CHESS choose[8] = {{-2, 1, 0}, {-1, 2, 0}, {1, 2, 0}, {2, 1, 0}, {2, -1, 0}, {1, -2, 0}, {-1, -2, 0}, {-2, -1, 0}};

typedef struct SeqStack
{
	CHESS *base;
	CHESS *top;
	int size;      //已用空间
	int len;
}SqStack;

void init_Stack(SqStack *s)
{
	s->base = (CHESS *)malloc(MAXSIZE * sizeof(CHESS));

	if (!s->base)
	{
		printf("失败\n");
		exit (0);
	}
	s->top = s->base;
	s->size = MAXSIZE;
	s->len = 0;
}

int if_empty(SqStack *s)
{
	if (s->len == 0)
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}

int top_stack(SqStack *s, CHESS *p)
{
	if (s->top > s->base)    //如果栈非空
	{
		*p = *(s->top - 1);
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}

int change_stack(SqStack *s, CHESS *p, int x, int y, int z)   //待定
{
	int k;

	if (s->top > s->base)
	{
		p->dir_choose = board[x][y][z + 1];
		p->flag = z + 1;
		*(s->top - 1) = *p;
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}

int push_stack(SqStack *s, CHESS *p)
{
	if (s->top - s->base == s->size)
	{
		s->base = (CHESS *)realloc(s->base, (s->size + STACKINCREASE) * sizeof(CHESS));
		s->top = s->base + s->size;
		s->size += STACKINCREASE;
	}

	*s->top = *p;
	s->top++;
	s->len++;
	

	return TRUE;
}

int pop_stack(SqStack *s, CHESS *p)
{
	if ((*s).base == (*s).top)
	{
		return FALSE;
	}

	*p = *(s->top - 1);
	s->top--;
	s->len--;
}

void setweight()
{
	int i, j, k;
	int x, y;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			weight[i][j] = 0;
			for (k = 0; k < 8; k++)
			{
				x = choose[k].x + i;
				y = choose[k].y + j;

				if (x >= 0 && x < N && y >= 0 && y < N)
				{
					weight[i][j]++;     //当前位置有多少方向可以移动

				}
			}
		}
	}
}

int check(int x, int y)
{
	if (x < 0 || x >= N || y < 0 || y >= N)
	{
		return 0;
	}

	return 1;
}

void setmap()
{
	int a[8];
	int i, j, k, m, min, s, h;
	int b;

	CHESS n1, n2;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (h = 0; h < 8; h++)
			{
				n1.x = i;
				n1.y = j;

				n2.x = i + choose[h].x;
				n2.y = j + choose[h].y;

				if (check(n2.x, n2.y) != 0)
				{
					map[i][j][h] = weight[n2.x][n2.y];
					board[i][j][h] = h;
				}

				else
				{
					map[i][j][h] = 9;
					board[i][j][h] = 9;
				}
			}
				for (m = 0; m < 7;m++)
				{
					
					for (k = m + 1; k < 8; k++)
					{
						if (map[i][j][m] > map[i][j][k])
						{
							min = map[i][j][m];
							map[i][j][m] = map[i][j][k];
							map[i][j][k] = min;
							min = board[i][j][m];
							board[i][j][m] = board[i][j][k];
							board[i][j][k] = min;
						}
					}
		//			printf("%d\t", map[i][j][m]);
				}
				printf("\n");
			}
		}

	getchar();
}

void show(int a[][N], int x, int y)
{
	int i, j;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
}
void path(int x, int y)
{
	int tmp_x, tmp_y, tmp_flag, flag;
	int a[N * N] = {0}, b[N * N] = {0};
	SqStack s;
	int num = 0;
	int i = 0;

	init_Stack(&s);
	
	CHESS local;
	CHESS next_step;

	local.x = x;
	local.y = y;
	local.dir_choose = board[x][y][0];
	local.flag = 0;

	tmp_p[x][y] = num + 1;
	push_stack(&s, &local);
	while (1)
	{
	if (if_empty(&s) == TRUE)
		{
			break;
		}
		top_stack(&s, &local);
		tmp_x = local.x;
		tmp_y = local.y;
		tmp_p[tmp_x][tmp_y] = num+1;
		tmp_flag = local.dir_choose;
		flag = local.flag;
	if (num == (N * N - 1))
		{
			printf("%d   end\n", if_empty(&s));
			break;
		}
		
		show(tmp_p, N, N);
		sleep(0.5);
		system("clear");
	//	getchar();
		if (flag >= weight[tmp_x][tmp_y])   //所有方向已经走完
		{
			tmp_p[tmp_x][tmp_y] = 0;
			pop_stack(&s, &local);
			top_stack(&s, &local);
			flag = local.flag ;
			num--;
			change_stack(&s, &local, local.x, local.y, flag);
		}
		else if (flag < weight[tmp_x][tmp_y])
		{
			next_step.x = tmp_x + choose[tmp_flag].x;
			next_step.y = tmp_y + choose[tmp_flag].y;
			if (check(next_step.x, next_step.y) && tmp_p[next_step.x][next_step.y] == 0)
			{
				num++;
				flag = 0;
				next_step.dir_choose = board[next_step.x][next_step.y][flag];
				next_step.flag = 0;
				push_stack(&s, &next_step);
			}
			else
			{
				change_stack(&s, &local, tmp_x, tmp_y, flag);
				flag++;
			}
		}
	}
	show(tmp_p, N, N);
}

int main(int argc, char *argv[])
{
	int x, y;
	int i, j, m;
	SqStack p;
	init_Stack(&p);


	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			weight[i][j] = 0;
			for (m = 0;m < N; m++)
		  	board[i][j][m] = 0;
	  	}
	}
	
	printf("请输入马起始的x坐标:");
	scanf("%d", &x);
	printf("请输入马起始的y坐标:");
	scanf("%d", &y);

	if (check(x, y) < 0)
	{
		printf("输入错误，请重新键入\n");
		return 0;
	}

	setweight();

	for (i = 0;i < N; i++)
	{
		for (j = 0;j < N; j++)
		{
			printf("%5d", weight[i][j]);
		}
		printf("\n");
	}
//	getchar();
//	getchar();


	setmap();


	path(x, y);







	return EXIT_SUCCESS;

}

