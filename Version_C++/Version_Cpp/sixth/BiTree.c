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

void CreatTree_char (BiTree * root)
{
	char ch;
	BiTree p;

	scanf("%c", &ch);

	if (ch == '#')
	{
		root = NULL;
	}
	else
	{
		root = (BiTree *)malloc(sizeof(BiTree));
		root->data = ch;
		root->Lchild = NULL;
		root->Rchild = NULL;

		CreatTree_char(root->Lchild);
		CreatTree_char(root->Rchild);
	}
}

void PreOrder (BiTree * root)
{
	if (root != NULL)
	{
	//	printf("%c \n", root->data);
		PreOrder(root->Lchild);
		PreOrder(root->Rchild);
	}
}

int main(int argc, char *argv[])
{
	BiTree root;

	CreatTree_char(&root);
	PreOrder(&root);

	return EXIT_SUCCESS;
}

