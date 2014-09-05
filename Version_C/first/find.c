/*
 * =====================================================================================
 *
 *       Filename:  find.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月28日 15时38分34秒
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
void find_num (int * array, int num, int k)
{
	int i;
	int flag = 0;

	for (i = 0; i < num; i++)
	{
		if (*(array + i) == k)
		{
			printf("%d\t", i + 1);
			flag++;
		}
	}

	printf("\n");

	if (flag == 0)
	{
		printf("0\n");
	}

}
int main(int argc, char *argv[])
{
	int a[10] = {9,8,7,6,5,4,3,2,1};

	find_num(a, 9, 8);

	return EXIT_SUCCESS;
}

