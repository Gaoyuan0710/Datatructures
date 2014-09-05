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
/*
typedef struct stack
{
	char ch[MAXSIZE];
	int top;
}SeqStack;

SeqStack * init_stack ()
{
	SeqStack *p;

	p = (SeqStack *)malloc(sizeof(SeqStack));

	p->top = -1;
}

void push_stack (SeqStack * p, char data)
{
	if (p->top == MAXSIZE)
	{
		printf("栈满\n");
		exit;
	}

	printf("压入%c\n", data);

	p->top++;
	p->ch[p->top] = data;
}

void pop_stack(SeqStack * p, char * data)
{
	if (p->top == -1)
	{
		printf("栈为空\n");
		exit;
	}

	printf("弹出%c\n", p->ch[p->top]);

	*data = p->ch[p->top];
	p->top--;
}

void get_stack(SeqStack * p, char * data)
{
	if (p->top == -1)
	{
		printf("栈为空\n");
		exit ;
	}

	*data = p->ch[p->top];
}
*/
void find_way(SeqStack * p, BiTree * root)
{
	char tmp;

	if (root->Lchild == NULL && root->Rchild == NULL)
	{
		pop_stack (p, &tmp);
		printf("%c\t", tmp);
	}

	push_stack(p, root->data);

	find_way(p, root->Lchild);
	find_way(p, root->Rchild);

}
void count_parent (BiTree * root, int * num)
{
	int flag1, flag2;

	if (root->Lchild == NULL || root->Rchild == NULL)
	{
		return ;
	}

	if (root->Lchild != NULL && root->Rchild != NULL)
	{
		(*num) += 1;
	}

	count_parent(root->Lchild, num);
	count_parent(root->Rchild, num);

}

void change_tree (BiTree * root)
{
	BiTree * tmp;

	tmp = (BiTree *)malloc(sizeof(BiTree));

	if (root == NULL)
	{
		return ;
	}

	if (root != NULL)
	{
		tmp = root->Lchild;
		root->Lchild = root->Rchild;
		root->Rchild = tmp;
	}

	change_tree(root->Lchild);
	change_tree(root->Rchild);
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
int main(int argc, char *argv[])
{
	BiTree *root1, *root2;
	BiTree *tmp;
//	SeqStack *p;
	int flag = 0;

	printf("请输入第一棵书\n");
	root1 = CreatTree_char(root1);
	printf("创建成功\n");
/*
	printf("请输入第二棵树\n");

	getchar();

	root2 = CreatTree_char(root2);
	printf("创建成功\n");

	printf("相似度为%d\n", like(root1, root2));

	PrintTree(root1, PostTreeDepth(root1));

	tmp = find_child(root1, 'f');

	printf("当前节点%c\n", tmp->data);
	printf("双亲是%c\n", parent(root1,tmp)->data);

	count_parent(root1, &flag);

	printf("度为二的节点的数目为%d\n", flag);

	PrintTree (root1, 1);

	change_tree(root1);

	PrintTree(root1, 1);
*/

//	p = init_stack();

	find_way(p, root1);

	return EXIT_SUCCESS;
}

