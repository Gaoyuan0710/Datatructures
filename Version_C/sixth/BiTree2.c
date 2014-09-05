/*
 * =====================================================================================
 *
 *       Filename:  BiTree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月17日 15时14分07秒
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

typedef char Datatype; 

typedef struct Node
{
	Datatype data;
	struct Node * Lchild;
	struct Node * Rchild;
}BiTree;

int count = 0;

BiTree * CreatTree_char (BiTree * root)
{
	char ch;
	BiTree *p;

	ch = getchar();

	if (ch == '#')
	{
		root = NULL;
	}
	else 
	{
		root = (BiTree *)malloc(sizeof(BiTree));
		root->data = ch;

		root->Lchild = CreatTree_char(root->Lchild);
		root->Rchild = CreatTree_char(root->Rchild);
	}

	return root;
}

void PreOrder (BiTree * root)
{
	if (root != NULL)
	{
		printf("%c \n", root->data);
		PreOrder(root->Lchild);
		PreOrder(root->Rchild);
	}
}

void CountOrder (BiTree * root)
{
//	int static count = 0;

	if (root)
	{
		count++;
		CountOrder(root->Lchild);
		CountOrder(root->Rchild);
	}

	//return count;
}

int main(int argc, char *argv[])
{
	BiTree *root;
	
	root = CreatTree_char(root);

	PreOrder(root);

	CountOrder(root);

	printf("节点数目为%d\n", count);

	return EXIT_SUCCESS;
}

