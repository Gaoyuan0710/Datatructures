/*
 * =====================================================================================
 *
 *       Filename:  95_6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月29日 17时27分40秒
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
#include <string.h>

void get_Next (char * string, int next[], int strlen)
{
	int  j = 1, k = 0;

	next[1] = 0;

	while (j <= strlen)
	{
		if (k == 0 || string[j] == string[k])
		{
			j++;
			k++;
			next[j] = next[j - 1] + 1;
		}
		else
		{
			k = next[k];
		}
	}

}

int main(int argc, char *argv[])
{
	char string[100] = {"abaabcac"};
	int next[100] = {0};
	int i;

	get_Next(string, next, strlen(string));

	for (i = 1; i <= strlen(string); i++)
	{
		printf("%5d", next[i]);
	}

	printf("\n");

	


	return EXIT_SUCCESS;
}

