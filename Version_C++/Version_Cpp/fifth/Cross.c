/*
 * =====================================================================================
 *
 *       Filename:  Cross.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 08时58分24秒
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

typedef struct node
{
	int row;
	int col;
	int value;
	struct node *right, *down;
}NODE;

typedef struct 
{
	NODE *rowhead, *colhead;
	int rows;
	int cols;
	int num;
}CROSS_LINK;
 
int init_CROSS (CROSS_LINK *cl, int *data, int m, int n)
{
	int i, j;
	NODE *p, *q;

	cl = (CROSS_LINK *)malloc(sizeof(CROSS_LINK));

	if (cl->rowhead == NULL)
	{
		printf("无法生成十字链表\n");
		return 0;
	}

	cl->rows = m;
	cl->cols = n;
	cl->num = 0;

	cl->rowhead = (NODE *)malloc(m * sizeof(NODE));
	cl->colhead = (NODE* )malloc(n * sizeof(NODE));

	for (i = 0; i < m; i++)
	{
		cl->rowhead[i] = NULL;
	}

	for (i = 0; i < n; i++)
	{
		cl->colhead[i] = NULL;
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (data[i * n + j] != 0)
			{
				p = (NODE *)malloc(sizeof(NODE));
				p->row = i + 1;
				p->col = j + 1;
				p->value = data[i * n + j];
				p->right = NULL;
				p->down = NULL;

				cl->num++;
				

				if(cl->colhead[i] != NULL)
				{
					q = cl->rowhead[i];


				}
				else
				{
					cl->rowhead[i] = p;

				
					
				}
			}
		}
	}

}

int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

