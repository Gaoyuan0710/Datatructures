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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 1000       //定义最大值
#define M 2 * N - 1  

int num = 0;

typedef char** DATA;   //定义编码存放类型
typedef struct Node
{
	char temp;
	int count;
//	int num;
	struct Node *next;
}Charactor;

typedef struct 
{
	char temp;
	int weight;
}Member;

typedef struct         //哈夫曼编码结构成员
{
	Member ch;        //出现的频率
	int parent;        //父节点序号
	int Lchild;        //左孩子序号
	int Rchild;        //右孩子序号
	int flag;          //标志是被处理，默认为0，未处理
}HTNODE;


Charactor *Count(char data, Charactor *head)
{
	Charactor *p = head->next;
	Charactor *q;

	while (p != NULL)
	{
		if (data == p->temp)
		{
			p->count++;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (p == NULL)
	{
		p = (Charactor *)malloc(sizeof(Charactor));

		p->temp = data;
		p->count = 1;
		num++;

		p->next = head->next;
		head->next = p;
	//	q->num = p->num++;
	//	p->next = q;
	//	q->next = NULL;
	}

	return head;
}

Charactor * read_file (Charactor *head)
{
	int fd;
	int ret;
	char tmp;

	int i = 0;

	fd = open("a.png", O_RDONLY);
	
	while (1)
	{
		i++;
		ret = read(fd, &tmp, 1);

		printf("ret = %d, tmp = %c\n", ret, tmp);
		head = Count(tmp, head);

		printf("i = %d\n", i);
		if (ret <= 0)
		{
	//		printf("tuichu");
			break;
		}

	}
	close(fd);

	return head;
}


/*
 * 打印哈夫曼表
 */

void Print(HTNODE * ht, int num)
{
	int i;

	printf("weight   parent  Lchild   Rchild    \n");

	for (i = 1; i <= num; i++)
	{
		printf("%d     %d        %d         %d  \n", ht[i].ch.weight, ht[i].parent,                                                      ht[i].Lchild, ht[i].Rchild);
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


	min = ht[*flag1].ch.weight;
	sec = ht[*flag2].ch.weight;

	/*
	 * 开始比较，已经比较过的此次不再比较
	 */

	for (i = 1; i <= n; i++)
	{

		if ((*(ht + i)).flag == -1)
		{
			continue;
		}

		if ((*(ht + i)).ch.weight < min && (*(ht + i )).flag != -1)
		{
			*flag2 = *flag1;
			*flag1 = i;
			sec = min;
			min = (*(ht + i)).ch.weight;
		}
		else if  ((*(ht + i)).ch.weight > min && (*(ht + i)).flag != -1)
		{
			if ( (*(ht + i)).ch.weight < sec)
			{
				*flag2 = i;
				sec = (*(ht + i)).ch.weight;
			}
		}
	}
}


/*
 * 建立哈夫曼树
 */

void Creat_Huffman (HTNODE * ht, Charactor *p, int n)
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
		ht[i].ch.weight = p->count;
		ht[i].ch.temp = p->temp;
		ht[i].parent = 0;                     
		ht[i].Rchild = 0;
		ht[i].Lchild = 0;
		ht[i].flag = 0;
		p = p->next;
	}

	/*
	 * 初始化后n-1个元素
	 */

	for (i = n + 1; i <= m; i++)
	{
		ht[i].ch.weight = 0;
		ht[i].ch.temp, p->temp;
		ht[i].parent = 0;
		ht[i].Rchild = 0;
		ht[i].Lchild = 0;
		ht[i].flag = 0;
	}

//Print(ht, m);

	/*
	 * 从第n-1个结点开始构造新结点
	 */

	for (i = n + 1; i <= m; i++)
	{
		Select(ht, i -1, &flag1, &flag2);

		ht[flag1].flag = -1;
		ht[flag2].flag = -1;
		ht[i].ch.weight = (ht[flag1].ch.weight + ht[flag2].ch.weight);
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

void Get_Language(HTNODE *ht, char ch[][N], int num)
{
	int i;
	int start;
	HTNODE child, parent;


	for (i = 1; i <= num; i++)
	{
		start = 0;
		parent = ht[num * 2 - 1];

		while (ch[i][start] != '\0')
		{
			if (ch[i][start] == '0')
			{
				child = ht[parent.Lchild];
			}
			else
			{
				child = ht[parent.Rchild];
			}
			parent = child;

			start++;
		}

		printf("%d\n", child.ch.weight);
	}
}
//void write_to_file ()
int main(int argc, char *argv[])
{

	Charactor *head;
	head = (Charactor *)malloc(sizeof(Charactor));
	head->next = NULL;
//	head->num = 0;

	int w[N] ;// {0, 1, 3, 6, 9};
	HTNODE ht[N];
	char **data;
	//	char code[N][N] = {{"\0"}, {"100\0"}, {"101\0"}, {"11\0"}, {"0\0"}};
	int i;
	int j;
//	char **p;


//	p = code;


	head = read_file(head);

	Charactor *p;
	p = head->next;

	Creat_Huffman(ht, p, num);


	Print(ht, num * 2 - 1);

	Get_Code(ht, data, num);
	printf("%d\n", num);
	getchar();

	for (i = 1; i <= num; i++)
	{
		j = 0;

		while ((*(*(data + i) + j)) != '\0')
		{
			printf("%c", (*(*(data + i) + j)));
			j++;
		}

		printf("\n");
	}

	p = head->next;

	while (p)
	{
		printf("%c", p->temp);
		p = p->next;
	}

//	Get_Language(ht, code, num);

	return EXIT_SUCCESS;
}

