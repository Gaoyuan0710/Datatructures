/*
 * =====================================================================================
 *
 *       Filename:  Huffman.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 19时35分34秒
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

#define N 30       //定义最大值
#define M 2 * N - 1  

typedef char** DATA;   //定义编码存放类型

typedef struct         //哈夫曼编码结构成员
{
	int weight;        //出现的频率
	int parent;        //父节点序号
	int Lchild;        //左孩子序号
	int Rchild;        //右孩子序号
	int flag;          //标志是被处理，默认为0，未处理
}HTNODE;


/*
 * 打印哈夫曼表
 */

void Print(HTNODE * ht, int num)
{
	int i;

	printf("weight   parent  Lchild   Rchild    \n");

	for (i = 1; i <= num; i++)
	{
		printf("%d     %d        %d         %d  \n", ht[i].weight, ht[i].parent,                                                      ht[i].Lchild, ht[i].Rchild);
	}
}


/*
 * 选择权值中最小的两个节点，返回最小值下标
 */

void Select (HTNODE * ht, int n,int *flag1, int *flag2)
{

	int i;
	int min;
	int sec;
	
	            
	/*
	 * 初始化选择函数的初始位置
	 */

	*flag1 = 1; 
	*flag2 = 2;

	while (ht[*flag1].flag == -1)
	{
		(*flag1)++;
	}
    *flag2 = *flag1 + 1;

	while (ht[*flag2].flag == -1)
	{
		(*flag2)++;
	}


	min = ht[*flag1].weight;
	sec = ht[*flag2].weight;

	/*
	 * 开始比较，已经比较过的此次不再比较
	 */

	for (i = 1; i <= n; i++)
	{

		if ((*(ht + i)).flag == -1)
		{
			continue;
		}

		if ((*(ht + i)).weight < min && (*(ht + i )).flag != -1)
		{
			*flag2 = *flag1;
			*flag1 = i;
			sec = min;
			min = (*(ht + i)).weight;
		}
		else if  ((*(ht + i)).weight > min && (*(ht + i)).flag != -1)
		{
			{
				*flag2 = i;
				sec = (*(ht + i)).weight;
			}
		}
	}
}


/*
 * 建立哈夫曼树
 */

void Creat_Huffman (HTNODE * ht, int * data, int n)
{
	int m;                                     
	int i, s1, s2;
	int flag1 = 1;
	int flag2 = 1;

	m = 2 * n - 1;


	/*
	 * 初始化前n个元素为叶子节点
	 */

	for (i = 1; i <= n; i++)
	{
		ht[i].weight = *(data + i);         
		ht[i].parent = 0;                     
		ht[i].Rchild = 0;
		ht[i].Lchild = 0;
		ht[i].flag = 0;
	}

	/*
	 * 初始化后n-1个元素
	 */

	for (i = n + 1; i <= m; i++)
	{
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].Rchild = 0;
		ht[i].Lchild = 0;
		ht[i].flag = 0;
	}

	Print(ht, m);

	/*
	 * 从第n-1个结点开始构造新结点
	 */

	for (i = n + 1; i <= m; i++)
	{
		Select(ht, i -1, &flag1, &flag2);

		ht[flag1].flag = -1;
		ht[flag2].flag = -1;
		ht[i].weight = (ht[flag1].weight + ht[flag2].weight);
		ht[i].Lchild = flag1;
		ht[i].Rchild = flag2;
		ht[flag1].parent = i;
		ht[flag2].parent = i;


	}
}


void Get_Code (HTNODE * ht, char **hc, int n)
{
	char cd[N];                          //临时储存编码
	int start;
	int parent;
	int i;
	int child;

	cd[n - 1] = '\0';                      //设置结束符



	/*
	 * 从每个叶子开始求相应的哈夫曼编码
	 */

	for (i = 1; i <= n; i++)
	{
		start = n - 1;                           
		child = i;                                     //child为当前结点
		parent = ht[i].parent;                         //parent为其双亲

		while (parent != 0)
		{
			start--;

			if (ht[parent].Lchild == child)            //左分支得0
			{
				cd[start] = '0';
			}
			else
			{
				cd[start] = '1';                       //右分支得1
			}

			child = parent;                            //到上一层
			parent = ht[parent].parent;

		}

		hc[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(hc[i], &cd[start]);                      //复制到编码组
	} 
}

int main(int argc, char *argv[])
{

	int w[] = {0, 1, 3, 6, 9};
	HTNODE ht[10];
	char **data;
	int i;
	int j;




	Creat_Huffman(ht, w, 4);

	Print(ht, 7);

	Get_Code(ht, data, 4);

	for (i = 1; i <= 4; i++)
	{
		j = 0;

		while ((*(*(data + i) + j)) != '\0')
		{
			printf("%c", (*(*(data + i) + j)));
			j++;
		}

		printf("\n");
	}


	return EXIT_SUCCESS;
}

