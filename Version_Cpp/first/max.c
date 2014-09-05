/*
 * =====================================================================================
 *
 *       Filename:  max.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月28日 15时49分55秒
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

void show (int a, int b)
{
	printf("最大值是%d\n次最大值是%d\n", a, b);
}

int find (int * a, int start, int end)
{
	int i;
	int max;
	int tmp;

	max = *(a + start);
	tmp = start;

	for (i = start; i <= end; i++)
	{
		if (*(a + i) > max)
		{
			max = *(a+i);
			tmp = i;
		}
	}

	* (a + end) = * (a + end) ^ * (a + tmp);
	* (a + tmp) = * (a + end) ^ * (a + tmp);
	* (a + end) = * (a + end) ^ * (a + tmp);


	return max;
}

void max (int * a, int num)
{
	int max1, max2;

	if (num == 1)
	{
		show(*a, *a);
		return ;
	}
	else
	{
		max1 = find(a, 0, num - 1);
		max2 = find(a, 0, num - 2);
	}

	show (max1, max2);
}
int main(int argc, char *argv[])
{
	int a[10] = {11, 1, 5, 4, 2, 6, 7, 9, 8};

	max(a, 10);

	return EXIT_SUCCESS;
}

