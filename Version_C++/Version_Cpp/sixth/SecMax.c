/*
 * =====================================================================================
 *
 *       Filename:  SecMax.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 19时51分34秒
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

void Select(int * arr, int n, int * min, int * sec)
{
	int i;
	int flag1 = 0;
	int flag2 = 0;

	* min = *(arr + 0);
	* sec = *(arr + 1);

	for (i = 0; i < n; i++)
	{
		if (arr[i] < *min)
		{
			*sec = *min;
			*min = arr[i];
			flag1 = i;

		}

		else if (arr[i] > *min)
		{
			if (arr[i] < *sec)
			{
				*sec = arr[i];
				flag2 = i;
			}
		}
	}


	printf("%d, %d\n", flag1, flag2);
}
int main(int argc, char *argv[])
{
	int a[10] = {2, 1, 3, 4, 5, 6, 7, 8, 9, 10};

	int max, sec;

	Select(a, 10, &max, &sec);

	printf("\n最小数字是%d, 次小数字是%d\n", max, sec);


	return EXIT_SUCCESS;
}

