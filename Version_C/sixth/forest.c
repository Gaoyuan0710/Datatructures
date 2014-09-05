/*
 * =====================================================================================
 *
 *       Filename:  forest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月28日 16时54分10秒
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

#define MAXSiZE 100

typedef struct CSNode
{
	char data;
	struct CSNode * Fistchild;
	struct CSNode * NextSibing;
}CSNODE;

CSNODE * built (CSNODE * root)
{
	char ch;

	ch = getchar();

	if (ch == '#')
	{
		return NULL;
	}

	root = (CSNODE *)malloc(sizeof(CSNODE));

	root->data = ch;
	root->Fistchild = built(root->Fistchild);
	root->NextSibing = built(root->NextSibing);

	return root;
}

void visit (CSNODE * root)
{
	CSNODE * p;

	if (root != NULL)
	{
		printf("%c ", root->data);
		p = root->Fistchild;

		while (p != NULL)
		{
			visit (p);
			p = p->NextSibing;
		}
	}

}

void count (CSNODE * root, int * num)
{
	CSNODE * p;

	if (root != NULL)
	{
		p = root->Fistchild;

		while (p != NULL)
		{
			if (p->Fistchild == NULL)
			{
				(*num)++;
			}

			count(p, num);

			p = p->NextSibing;
		}
	}
}

void height (CSNODE * root, int * max, int * tmp)
{
	CSNODE * p;

//	int flag = 0;

	if (root != NULL)
	{
		p = root->Fistchild;
		(*tmp)++;
//		flag++;

		printf("%d\n",*tmp);

		
		while (p != NULL)
		{
			height (p, max, tmp);

			if (*tmp > * max)
			{
				*max = *tmp;
			}

			p = p->NextSibing;
			(*tmp)--;
		}
	}

//	return flag;
}

int main(int argc, char *argv[])
{
	CSNODE * root;
	int num = 0;
	int tmp = 0;

	root = built(root);

	printf("进入\n");

	visit(root);

	printf("\n");

	height(root, &num, &tmp);

	printf("%d\n", num);

	return EXIT_SUCCESS;
}

