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

#define MAXSIZE 100

int count = 0;

typedef char Datatype; 

typedef struct Node
{
	Datatype data;
	struct Node * Lchild;
	struct Node * Rchild;
}BiTree;

void 	FindWay( BiTree *root, int Level, char *temp )
{
	int 	i;

	if (root) 
	{
		temp[Level] = root->data;

		if ( (root->Lchild == NULL) && (root->Rchild == NULL) )
		{
			for (i = 0; i < Level; i ++)
			  	printf("%c ", temp[i]);
			printf("\n");
		}

		FindWay( root->Lchild, Level + 1, temp );
		FindWay( root->Rchild, Level + 1, temp );

	}
}

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
void InOrder (BiTree * root)
{
	if (root)
	{
		InOrder (root->Lchild);

		if (root->Lchild == NULL && root->Rchild == NULL)
		  {
			  printf("%c\t", root->data);
		  }

		InOrder (root->Rchild);
	}

}
void CountParent (BiTree * root, int *num)
{
//	int static count = 0;

	if (root->Lchild != NULL && root->Rchild != NULL)
	{
		(*num)++;
		CountParent(root->Lchild, num);
		CountParent(root->Rchild, num);
	}

	//return count;
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

int PostTreeDepth (BiTree  * root)
{
	int hl ,hr, h;

	if (root == NULL)
	{
		return 0;
	}

	else
	{
		hl = PostTreeDepth(root->Lchild);
		hr = PostTreeDepth(root->Rchild);

		h = (hl > hr ? hl : hr) + 1;
		return h;
	}
}
int like (BiTree  * t1, BiTree * t2)
{
	int like1;
	int like2;

	if (t1 == NULL && t2 == NULL)
	{
		return 1;
	}

	else if (t1 == NULL || t2 == NULL)
	{
		return 0;
	}

	else 
	{
		like1 = like(t1->Lchild, t2->Lchild);
		like2 = like(t1->Rchild, t2->Rchild);

		return (like1 && like2);
	}
}
BiTree * parent (BiTree * root, BiTree * child)
{
	BiTree *p;

	if (root == NULL)
	{
		return NULL;
	}

	if (root->Lchild == child || root->Rchild == child)
	{
		return root;
	}

	p = parent(root->Lchild, child);

	if (p != NULL)
	{
		return p;
	}

	else
	{
		return (parent(root->Rchild, child));
	}

}

BiTree * find_child (BiTree * root, char ch)
{
	BiTree *p1, *p2;

	if (root == NULL)
	{
		return NULL;
	}


	if (root->data == ch)
	{
		return root;
	}


	p1 = find_child(root->Lchild, ch);

	if (p1 != NULL)
	{
		return p1;
	}
	else
	{
		return (find_child(root->Rchild, ch));
	}


}
void PrintTree (BiTree * root, int h)
{
	int i;

	if (root == NULL)
	{
		return ;
	}
	
	PrintTree(root->Rchild, h + 1);
	
	for (i = 0;i < h; i++)
	{
		printf("   ");
	}

	printf("%c\n", root->data);

	PrintTree(root->Lchild, h + 1);
}

void Print (BiTree * root, int deep)
{
	if (root == NULL)
	{
		return ;
	}

	printf("(%c, %d) ", root->data, deep);

	Print(root->Lchild, deep + 1);

	Print(root->Rchild, deep + 1);


}
BiTree * change (BiTree * root)
{
	BiTree * tmp;
	BiTree * p, * q;

	if (root->Lchild == NULL && root->Rchild == NULL)
	{
		return root;
	}

	else if (root->Lchild != NULL && root->Rchild != NULL)
	{
		p = root->Lchild;
		q = root->Rchild;

		root->Rchild = p;
		root->Lchild = q;

		root->Lchild = change (root->Lchild);
		root->Rchild = change (root->Rchild);

//		return root;
	}

	else if (root->Lchild == NULL)
	{

//		root->Lchild = (BiTree *)malloc(sizeof(BiTree));
		root->Lchild =  change(root->Rchild);
		root->Rchild = NULL;
//		return root;
	}

	else if (root->Rchild == NULL)
	{
//		root->Rchild = (BiTree *)malloc(sizeof(BiTree));
		root->Rchild = change(root->Lchild);
		root->Lchild = NULL;
//		return root;
	}

	return root;
}


BiTree * changes(BiTree * root)
{
	BiTree * tmp;
	BiTree * p, * q;

	if (root->Lchild == NULL && root->Rchild == NULL)
	{
		return ;
	}
	p = root->Lchild;
	q = root->Rchild;

	root->Rchild = p;
	root->Lchild = q;

	root->Lchild = change (root->Lchild);
	root->Rchild = change (root->Rchild);

	return root;
}






int main(int argc, char *argv[])
{
	BiTree *root1, *root2;
	BiTree *tmp;
	char 	temp[20];
	int flag = 0;

	printf("请输入第一棵书\n");
	root1 = CreatTree_char(root1);
	printf("创建成功\n");

	PrintTree(root1, 1);
	changes(root1);

	printf("\n\n\n");

	PrintTree (root1, 1);
  //  Print(root1, 1);

	//CountParent(root1, &flag);


//	printf("个数为%d\n", flag);
	return EXIT_SUCCESS;
}

