#include<stdio.h>/*2009.9.25晚 写于白鹿原*/
#include <malloc.h>

typedef int DataType; 
typedef struct Node {
	DataType data;
 	struct Node *LChild;
 	struct Node *RChild;
}BitNode,*BitTree;

void CreatBiTree(BitNode * BT) {
	char ch;
 	ch = getchar();
	
	if(ch == '#') {
		BT = NULL;
	}
	else {
		BT = (BitNode *)malloc(sizeof(BitNode));
  		BT->data = ch;
  		CreatBiTree((BT->LChild));
  		CreatBiTree((BT->RChild));
	}
}
void Visit(char ch) {
 printf("%c  ",ch);
}

void  PreOrder(BitNode * root) {
	if (root!=NULL) {
		Visit(root ->data);  /*访问根结点*/
  		PreOrder(root ->LChild);  /*先序遍历左子树*/
 		PreOrder(root ->RChild);  /*先序遍历右子树*/
 }
}

void main()
{
 BitNode * T;
 int h;
 int layer;
 int treeleaf;
 layer=0;
 printf("请输入二叉树中的元素(以扩展先序遍历序列输入,其中.代表空子树):\n");
    CreatBiTree(T);
 printf("先序遍历序列为:");
 PreOrder(T);
}
