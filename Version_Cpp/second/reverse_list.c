/*
 * =====================================================================================
 *
 *       Filename:  reverse_link.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月03日 22时15分51秒
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

#define MAXSIZE 10

typedef struct elemtype
{
	int elem[MAXSIZE];
	int length;
}Seqlist;

void init_Seqlist(Seqlist * L)
{
	L->length = 0;
}

void creat_Seqlist(Seqlist * L)
{
	int i = 0;

	printf("请输入元素个数:");
	scanf("%d", &L->length);

	for (i = 0; i < L->length; i++)
	{
		printf("请输入第%d个元素:", i + 1);
		scanf("%d", &L->elem[i]);
	}

	printf("完成建立\n");
}

void show_Seqlist(Seqlist * L)
{
	int i;

	for (i = 0; i < L->length; i++)
	{
		printf("%d\t", L->elem[i]);
	}
	printf("\n");
}

void reserve_Seqlist(Seqlist * L)
{
	int i;

	for (i = 0; i < L->length/2; i++)
	{
		L->elem[i] = L->elem[i] ^ L->elem[L->length - 1 - i];
		L->elem[L->length - 1 - i] = L->elem[i] ^ L->elem[L->length - 1 - i];
		L->elem[i] = L->elem[i] ^ L->elem[L->length - 1 - i];
	}
}

void delet_Seqlist(Seqlist * L)
{
	int num;
	int i;
	int j;

	num = L->length;

	printf("请输入要删除的x的值:");
	scanf("%d", &num);

	for (i = 0; i < L->length; i++)
	{
		if (L->elem[i] == num)
		{
			for (j = i; j < L->length; j++)
			{
				L->elem[j] = L->elem[j + 1];
			}
			L->length--;
		}
	}
	

}
int main(int argc, char *argv[])
{
	Seqlist L;

	creat_Seqlist(&L);
	show_Seqlist(&L);
	reserve_Seqlist(&L);
	show_Seqlist(&L);
	delet_Seqlist(&L);
	show_Seqlist(&L);

	


	return EXIT_SUCCESS;
}

