/*
 * =====================================================================================
 *
 *       Filename:  OLNode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 21时48分30秒
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

typedef int Elemtype

typedef struct OLNode
{
	int row, col;
	Elemtype value;
	struct OLNode *right, *down;
}OLNode , *OLink;

typedef struct 
{
	OLink *rowhead, *colhead;
	int rows, cols, nums;
}*CrossList;

int Init_CrossList(CrossList *CL, Elemtype *A, int m, int n)
{
	int i, j;
	OLNode *p, *q;

	(*CL) = (CrossList)malloc(sizeof(CrossList));

	if (!(*CL)->rowhead)
	{
		printf("无法生成十字表\n");
		return 0;
	}

	(*CL)->rows = m;
	(*CL)->cols = n;
	(*CL)->nums = 0;
	(*CL)->rowhead = (OLink *)malloc(m * sizeof(OLink));

	if (!(*CL)->rowhead)
	{
		printf("无法生成行指针数组\n");
		return 0;
	}

	for (i = 0; i < m; i++)
	{
		(*CL)->rowhead[i] = NULL;
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (A[i * n + j] != 0)
			{
				p = (OLNode *)malloc(sizeof(OLNode));
				p->row = i + 1;
				p->col = j + 1;
				p->value = A[ i * n + j];
				p->right = NULL;
				p->down = NULL;

				(*CL)->nums++;

				if ((*CL)->rowhead[i] != NULL)
				{
					q = (*CL)->rowhead[i];

					while (q->right != NULL && q->col < j + 1)
					{
						q = q->right;
					}

					p->right = q->right;
					q->right = p;
				}
				else
				{
					(*CL)->colhead[i] = p;
				}

				if ((*CL)->colhead[j] != NULL)
				{
					  q = (*CL)->colhead[j];

					  while (q->down != NULL && q->row < i + 1)
					  {
						  q = q->down;
					  }
					  p->down = q->down;
					  q->down = p;
				}

				else 
				{
					(*CL)->colhead[j] = p;
				}
			}

			return 1;
		}
	}

}

int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

