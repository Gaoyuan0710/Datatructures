/*
 * =====================================================================================
 *
 *       Filename:  Huffman.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 19时35分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 690892695@qq.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 30
#define M 2 * N - 1

typedef struct 
{
	int weight;
	int parent;
	int Lchild;
	int Rchild;
	int flag;
}HTNODE;


void Print(HTNODE * ht, int num)
{
	int i;

	printf("weight   parent  Lchild   Rchild    \n");

	for (i = 1; i <= num; i++)
	{
		printf("%d     %d        %d         %d  \n", (*(ht + i)).weight, (*(ht + i)).parent, (*(ht + i)).Lchild, (*(ht + i)).Rchild);
	}
}




void Select(HTNODE * ht, int n, int * min, int * sec, int *flag1, int *flag2)
{
	int i;

	* min = ht[*flag1].weight;
	* sec = ht[*flag2].weight;

	for (i = 1; i <= n; i++)
	{

		if ((*(ht + i)).flag == -1)
		{
			continue;
		}

		if ((*(ht + i)).weight <  *min && (*(ht + i)).flag != -1)
		{
			*flag2 = *flag1;

			*flag1 = i;

			*sec = *min;
			*min = (*(ht + i)).weight;
		}

		else if  ((*(ht + i)).weight > *min && (*(ht + i)).flag != -1)
		{
			if ((*(ht + i)).weight < *sec)
			{
				*flag2 = i;
				*sec = (*(ht + i)).weight;
			}
		}
	}
}

void Creat_Huffman (HTNODE * ht, int * w, int n)
{
	int m;
	int i, s1, s2;
	int flag1 = 1;
	int flag2 = 2;
	int m1, m2;

	m = 2 * n - 1;


	for (i = 1; i <= n; i++)
	{
		(*(ht + i)).weight = *(w + i);
		(*(ht + i)).parent = 0;
		(*(ht + i)).Rchild = 0;
		(*(ht + i)).Lchild = 0;
		(*(ht + i)).flag = 0;
	}

	for (i = n + 1; i <= m; i++)
	{
		(*(ht + i)).weight = 0;
		(*(ht + i)).parent = 0;
		(*(ht + i)).Rchild = 0;
		(*(ht + i)).Lchild = 0;
		(*(ht + i)).flag = 0;
	}

	Print(ht, m);
	
	for (i = n + 1; i <= m; i++)
	{
		Select(ht, i - 1, &s1,  &s2, &flag1, &flag2);


		ht[flag1].flag = -1;
		ht[flag2].flag = -1;
		ht[i].weight = (ht[flag1].weight + ht[flag2].weight);
		ht[i].Lchild = flag1;
		ht[i].Rchild = flag2;
		ht[flag1].parent = i;
		ht[flag2].parent = i;


		m1 = 1;
		m2 = 1;
		flag1 = m1;
		flag2 = m2;

		while (ht[m1].flag == -1)
		{
			m1++;
		}
		flag1 = m1;
		m2 = m1 + 1;
		while (ht[m2].flag == -1)
		{
			m2++;
		}

		flag2 = m2;
	}
}



int main(int argc, char *argv[])
{

	int w[] = {0, 1, 3, 6, 9};
	HTNODE ht[10];




	Creat_Huffman(ht, w, 4);

	Print(ht, 7);


	return EXIT_SUCCESS;
}

