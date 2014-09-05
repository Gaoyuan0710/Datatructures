/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月28日 21时19分00秒
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

#define MAX_LEN 10
#define TRUE    1
#define ERROR   0

typedef struct list
{
	int elem[MAX_LEN];
	int length;
}SeqList;

void seqList_init(SeqList * L)
{
	L->length = 0;
}
int seqList_insert(SeqList * L, int i, int x)
{
	int j;

	if (L->length == MAX_LEN)
	{
		printf("表空间已满\n");
		return ERROR;
	}

	if (i < 1 || i > L->length + 1)
	{
		printf("位置错\n");
		return ERROR;
	}

	for (j = L->length; j >= i; j--)
	{
		L->elem[j + 1] = L->elem[j];
	}

	L->elem = x;
	L->length++;

	return TRUE;
}
int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

