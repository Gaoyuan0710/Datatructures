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
#define N   5
#define TRUE   1
#define FALSE  0


int i_i, j_j;
int tmp_p[N][N] = {0};
typedef struct chess
{
	int x;
	int y;
	int flag;                
}CHESS;

int map[N][N][8];   //存放下一步方向
int board[N][N];    //棋盘，可走时为0, 走后为1
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

int change_stack(SqStack *s, CHESS *p)   //待定
{
	if (s->top > s->base)
	{
		p->flag++;
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
/*
int setmap()                           //按照目前最优路径排序
{
	int i, j, k;
	int x1, x2;
	int y1, y2;
	int m, d1, d2, flag1, flag2;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < 8; k++)
			{
				map[i][j][k] = k;
			}

			for (k = 0; k < 7; k++)
			{
				for (m = k + 1; m < 8; m++)
				{
					d1 = map[i][j][k];
					x1 = i + choose[d1].x;
					y1 = j + choose[d1].y;

					d2 = map[i][j][k];
					x2 = i + choose[d2].x;
					y2 = j + choose[d2].y;

					flag1 = check(x1, y2);
					flag2 = check(x2, y2);

					if ((flag1 == 0 && flag2) || (flag1 && flag2 && (board[x1][y1] > board[x2][y2])))
					{
						map[i][j][k] = d2;
						map[i][j][m] = d1;
					}
				}
			}
		}
	}
}
*/

void setmap()
{
	int a[8];
	int i, j, k, m, min, s, h;
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
					a[h] = weight[n2.x][n2.y];
				}

				else
				{
					a[h] = 0;
				}

				for (m = 0; m < 8;m++)
				{
					min = 9;
					for (k = 0; k < 8; k++)
					{
						if (min > a[k])
						{
							min = a[k];
							map[i][j][k] = k;
							s = k;
						}
						a[s] = 9;
					}
				}
				
			}
		}
	}
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
/*
void output(SqStack *s)
{
	SqStack tmp;
	int c[N][N] = {0};
	int j, k = N * N, l = 1, x, y;
	CHESS e;

	init_Stack(&tmp);
	while (if_empty(s) != 1)
	{
		pop_stack(s, &e);
		c[e.x][e.y] = k;
		k--;
//printf("ssss%d   %d\n", e.x, e.y);
//sleep(2);
		push_stack(&tmp, &e);
	}

	top_stack(&tmp, &e);

	x = e.x;
	y = e.y;

	printf("起始坐标:%d, %d\n", x, y);
pop_stack(&tmp, &e);
top_stack(&tmp, &e);
//printf("xia  %d  %d\n", e.x, e.y);
sleep(2);
	while ( if_empty(&tmp) != 0)
	{
		pop_stack(&tmp, &e);
//		printf("test %d, %d\n", e.x, e.y);
		push_stack(s, &e);
	}

	printf("棋盘表示:       0   1   2   3   4   5   6   7\n");
	
	printf("              ┌─┬─┬─┬─┬─┬─┬─┬─┐\n");
	
	printf("             0");        
	
	for(j = 0;j < N; j++)
	{
		if(c[0][j]<10) 
		  printf("│ %d",c[0][j]);
		else
		  printf("│%d",c[0][j]);}printf("│\n");
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             1");
	
	for(j = 0;j < N ;j++)
	  
	{   
		if(c[1][j]<10) 
		  printf("│ %d",c[1][j]);
		else
		  printf("│%d",c[1][j]);}printf("│\n");
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             2");
	
	for(j=0;j< N;j++)
	  
	{ 
		if(c[2][j]<10) 
		  printf("│ %d",c[2][j]);
		else
		  printf("│%d",c[2][j]);}printf("│\n");
	
		printf("              ");
		
		printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
		printf("             3");
	
	for(j = 0;j <N;j++)
	  
	{   
		if(c[3][j]<10)
		  printf("│ %d",c[3][j]);
		else
		  printf("│%d",c[3][j]);}printf("│\n");
	
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             4");
	
	for(j = 0;j <N;j++)
	  
	{  
		if(c[4][j]<10) 
		  printf("│ %d",c[4][j]);
		else
		  printf("│%d",c[4][j]);}printf("│\n");
	
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             5");
	
	for(j = 0;j <N;j++)
	  
	{   
		if(c[5][j] < 10)
		  printf("│ %d",c[5][j]);
		else
		  printf("│%d",c[5][j]);}printf("│\n");
	
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             6");        
	
	for(j = 0;j <N;j++)
	  
	{
		if(c[6][j]<10)
		  printf("│ %d",c[6][j]);
		else
		  printf("│%d",c[6][j]);}printf("│\n");
	
	printf("              ");
	
	printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
	
	printf("             7");   
	
	for(j = 0;j <N;j++)
	  
	{
		if(c[7][j]<10)
		  printf("│ %d",c[7][j]);
		else
		  printf("│%d",c[7][j]);
	}
	printf("│\n");
	
	printf("              "); 
	
	printf("└─┴─┴─┴─┴─┴─┴─┴─┘\n");

}
*/
void path(int x, int y)
{
	int tmp_x, tmp_y, tmp_flag, flag;
	int a[N * N] = {0}, b[N * N] = {0};
	SqStack s;
	int num = 0;

	init_Stack(&s);
	
	CHESS local;
	CHESS next_step;

	local.x = x;
	local.y = y;
	local.flag = 0;

	printf("%d\n", board[x][y]);
	board[x][y] = 0;
	push_stack(&s, &local);
	while (1)
	{
			if (num == (N * N - 1))
			{
				printf("end\n");
	//			output(&s);
				break;
			}

			if (if_empty(&s) == TRUE)
			  {
				  break;
			  }

			top_stack(&s, &local);
			tmp_x = local.x;
			tmp_y = local.y;
			tmp_flag = local.flag;
			tmp_p[tmp_x][tmp_y] = num+1;
			show(tmp_p, N, N);
	//		getchar();
			if (tmp_flag >= weight[tmp_x][tmp_y])   //所有方向已经走完
			{
				board[tmp_x][tmp_y] = 0;
				tmp_p[tmp_x][tmp_y] = 0;
				pop_stack(&s, &local);
				top_stack(&s, &local);
				num--;
				change_stack(&s, &local);
				printf("flag2 %d\n", local.flag);
			}

			if (tmp_flag < weight[tmp_x][tmp_y])
			{
				flag = map[tmp_x][tmp_y][tmp_flag];
printf("flag = %d\n", flag);
				next_step.x = tmp_x + choose[flag].x;
				next_step.y = tmp_y + choose[flag].y;
					
				if (check(next_step.x, next_step.y) && board[next_step.x][next_step.y] == 0)
				{
				b[num] = num;
					board[tmp_x][tmp_y] = 1;

					num++;
					next_step.flag = 0;
					push_stack(&s, &next_step);
				}
				else
				{
					change_stack(&s, &local);
				}
				printf("num = %d  len = %d\n", num, s.len);
			}

	}
}

int main(int argc, char *argv[])
{
	int x, y;
	int i, j;
	SqStack *p;
	init_Stack(p);

	CHESS a1, a2;

	a1.x = a1.y = a1.flag =0;
	a2 = a1;

	push_stack(p, &a1);
	push_stack(p, &a2);


	for (i = 0; i < N; i++)
	{
	  for(j = 0; j < N; j++)
	  {
		  board[i][j] = 0;
	  }
	}

	

	while (1)
	{
		printf("请输入马起始的x坐标:");
		scanf("%d", &x);
		printf("请输入马起始的y坐标:");
		scanf("%d", &y);

		if (check(x, y) < 0)
		{
			printf("输入错误，请重新键入\n");
		}

		else
		{
			break;
		}
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
	getchar();
	getchar();


	setmap();


	path(x, y);







	return EXIT_SUCCESS;

}

