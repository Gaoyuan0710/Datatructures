/*
 * =====================================================================================
 *
 *       Filename:  home_work.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月16日 21时18分15秒
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
//#include "Huffman_test.c"
//#include "code.c"


#define MAX 256
#define N 30       //定义最大值
#define M 2 * N - 1  
#define LEN sizeof(Char_code)
typedef struct code
{
	char ch;
	int count;
	char tmp[256];
	struct code *next;
}CODE;

//#define MAX 1000
typedef char** DATA;   //定义编码存放类型

typedef struct  charactor
{
	char ch;
	int count;
	struct charactor *next;
}Char_code;

typedef struct         //哈夫曼编码结构成员
{
	Char_code code;        //出现的频率
	int parent;        //父节点序号
	int Lchild;        //左孩子序号
	int Rchild;        //右孩子序号
	int flag;          //标志是被处理，默认为0，未处理
//	int find;
}HTNODE;



Char_code *Count (char ch, Char_code *head);
void write_file(Char_code *head);
void show(Char_code *head);
void read_words(Char_code *head);
void trans_to_code(Char_code *head);
void read_file(Char_code *head);
void Print(HTNODE * ht, int num);
void Select (HTNODE * ht, int n,int *flag1, int *flag2);
void Creat_Huffman (HTNODE * ht, Char_code *head, int n);
void Get_Code (HTNODE * ht, char hc[][MAX], int n);
void write_import(HTNODE *ht, char ch[][MAX], int num, int flag);










/*
#define N 30       //定义最大值
#define M 2 * N - 1  
#define LEN sizeof(Char_code)
typedef struct code
{
	char ch;
	int count;
	char tmp[256];
	struct code *next;
}CODE;

//#define MAX 1000
typedef char** DATA;   //定义编码存放类型

typedef struct  charactor
{
	char ch;
	int count;
	struct charactor *next;
}Char_code;

typedef struct         //哈夫曼编码结构成员
{
	Char_code code;        //出现的频率
	int parent;        //父节点序号
	int Lchild;        //左孩子序号
	int Rchild;        //右孩子序号
	int flag;          //标志是被处理，默认为0，未处理
//	int find;
}HTNODE;*/


/*
 * 打印哈夫曼表
 */

void Print(HTNODE * ht, int num)
{
	int i;

	printf("weight   parent  Lchild   Rchild    \n");

	for (i = 1; i <= num; i++)
	{
		printf("%d     %d        %d         %d  \n", ht[i].code.count, ht[i].parent,                                                      ht[i].Lchild, ht[i].Rchild);
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


	min = ht[*flag1].code.count;
	sec = ht[*flag2].code.count;

	/*
	 * 开始比较，已经比较过的此次不再比较
	 */

	for (i = 1; i <= n; i++)
	{

		if ((*(ht + i)).flag == -1)
		{
			continue;
		}

		if ((*(ht + i)).code.count < min && (*(ht + i )).flag != -1)
		{
			*flag2 = *flag1;
			*flag1 = i;
			sec = min;
			min = (*(ht + i)).code.count;
		}
		else if  ((*(ht + i)).code.count > min && (*(ht + i)).flag != -1)
		{
			if ( (*(ht + i)).code.count < sec)
			{
				*flag2 = i;
				sec = (*(ht + i)).code.count;
			}
		}
	}
}


/*
 * 建立哈夫曼树
 */

void Creat_Huffman (HTNODE * ht, Char_code *head, int n)
{

	int m;     
	int i, s1, ls2;
	int flag1 = 1;
	int flag2 = 1;
	Char_code *p = head->next;

	m = 2 * n - 1;


	/*
	 * 初始化前n个元素为叶子节点
	 */

	for (i = 1; i <= n; i++)
	{
		ht[i].code.count = p->count;
		ht[i].code.ch = p->ch;
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
		ht[i].code.count = 0;
		ht[i].code.ch = '\0';
		ht[i].parent = 0;
		ht[i].Rchild = 0;
		ht[i].Lchild = 0;
		ht[i].flag = 0;
	}

//	Print(ht, m);

	/*
	 * 从第n-1个结点开始构造新结点
	 */

	for (i = n + 1; i <= m; i++)
	{
		Select(ht, i -1, &flag1, &flag2);

		ht[flag1].flag = -1;
		ht[flag2].flag = -1;
		ht[i].code.count= (ht[flag1].code.count + ht[flag2].code.count);
		ht[i].Lchild = flag1;
		ht[i].Rchild = flag2;
		ht[flag1].parent = i;
		ht[flag2].parent = i;


	}
}


void Get_Code (HTNODE * ht, char hc[][MAX], int n)
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

		printf("i = %d\n", i);
	//	hc[i] = (char *)malloc((n - start + 1) * sizeof(char));
		strcpy(hc[i], &cd[start]);                      //复制到编码组
	} 
}
void write_import(HTNODE *ht, char data[][256], int num, int age)
{
	int i;
	int fd;
	int flag;
	char tmp[1024];
	char count[1024];

	fd = open("code.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);

	if (fd == -1)
	{
		printf("打开文件失败\n");
	}

	for (i = 1; i <= num; i++)
	{
		memset(tmp, '\0', sizeof(tmp));

		strcpy(tmp, &ht[i].code.ch);
		strcat(tmp, ":");
		strcat(tmp, data[i]);
		strcat(tmp, ":");
//		write(fd, tmp, strlen(tmp));

		memset(count, '\0', sizeof(tmp));
		sprintf(count, "%d", ht[i].code.count);
		strcat(tmp, count);
		strcat(tmp, "#");
		strcat(tmp, "\n");

	//	printf("sss%s\n", tmp);
		flag = write(fd, tmp, strlen(tmp));

	//	printf("flag = %d\n", flag);
		
	}

	printf("写完了\n");

	close(fd);
}
//void get_tree()
Char_code * get_tree(Char_code *head)
{
	int fd;
	int i;
	int ret;
	int flag;
	char tmp[1024];
	char ch;
	char count[MAX];
	int data;
	Char_code *p;
	Char_code *q;


	q = head = (Char_code *)malloc(sizeof(Char_code));
	head->next = NULL;

	fd = open("code.txt", O_RDONLY);

	while (1)
	{
		i = 0;

		memset(tmp, '\0', sizeof(tmp));

		while (1)
		{
			read(fd, &tmp[i++], 1);

			if (tmp[i - 1] == '#')
			{
				break;
			}
		}
//		ret = read(fd, tmp, 256);
		p = (Char_code *)malloc(sizeof(Char_code));

		printf("%s\n", tmp);

		ch = tmp[0];
		flag = 0;
		for (i = 0; i < strlen(tmp); i++)
		{
			if (tmp[i] == ':')
			{
			//	printf(" %d  %c\n", i, tmp[i + 1]);
				flag++;
			}
			if (tmp[i] == ':' && flag == 2)
			{
				strcpy(count, &tmp[i + 1]);
				data = atoi(count);
	//			printf("count %s %d\n", count, data);
				break;
			}

		}
		ret = read(fd, &tmp[i], 1);
		if (ret <= 0)
		{
			break;
		}

		p->ch = ch;
		p->count = data;
		p->next = NULL;;
		q->next = p;
		q = p;

		}
	close(fd);
	return head;
}

Char_code *Count (char ch, Char_code *head)
{
	Char_code *p = head->next;

	while (p != NULL )
	{
		if(p->ch == ch)
		{
		//	if (p->ch == 'w')
		//	  printf("\n%d\n", p->count);
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
		head->count++;

		p = (Char_code *)malloc(LEN);

		p->ch = ch;
		p->count = 1;

		p->next = head->next;
		head->next = p;
	}

	return head;
}
void write_file(Char_code *head)
{
	int fd;
	int flag1, flag2, flag3, flag4;
	Char_code *p = head->next;
	char tmp[100];
	char test[100] = {"woshizhu"};

	fd = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC , 0777);

	if (fd == -1)
	{
		printf("打开文件失败");
	}
//	write(fd, test, strlen(test));

	while (p != NULL)
	{
	//	printf("jinru\n");
//	flag1 = 	write(fd, &p->ch, sizeof(p->ch));
		memset(tmp, '\0', sizeof(tmp));
strcpy(tmp, &p->ch);
strcat(tmp, ":");
	flag2 = 	write(fd, tmp, strlen(tmp));
		sprintf(tmp, "%d", p->count);
		strcat(tmp, "\n");
	//	printf("%s\n", tmp);
	flag3 = 	write(fd, tmp, strlen(tmp));
//	flag4 = 	write(fd, test, strlen(test));
//	printf("%d\t%d\t%d\t%d\n", flag1, flag2, flag3, flag4);
		p = p->next;
	}
	close(fd);
}

//未完待续

void show(Char_code *head)
{
	Char_code *p;

	p = head->next;

	printf("begin\n");
	while (p != NULL)
	{
		printf("%c:%d\n", p->ch, p->count);
		p = p->next;
	}
	printf("end\n");
}

void read_words(Char_code *head)
{
	int fd;
	int ret;
	int i;
	char tmp[1024];

	fd = open("a.txt", O_RDONLY);

	while (1)
	{

		ret = read(fd, tmp, 1024);
		printf("%s\n", tmp);
		for (i = 0; i < strlen(tmp); i++)
		{
			head = Count(tmp[i], head);
		}
		if (ret <= 1024)
		{
			break;
		}
	}
	close(fd);

}

void trans_to_code(Char_code *head)
{
	Char_code *p = head->next;

	while (p)
	{

	}
}
void read_file(Char_code *head)
//void read_file(Char_code *head)
{
	int fd;
	int ret;
	char tmp;
	int count;
	Char_code *p ;

	fd = open("a.txt", O_RDONLY);

	while (1)
	{
		ret = read(fd, &tmp, 1);
//		printf("%c", tmp);
		head = Count(tmp, head);


		if (ret != 1)
		{
			break;
		}
	}
	close(fd);
/*
	p = head->next;

	while (p)
	{
		printf("%d", p->count);
		p = p->next;
	}

	return p;
	*/
}

int main(int argc, char *argv[])
{
	HTNODE ht[MAX];
	Char_code *head;
	Char_code *p;
	Char_code *code;
	char data[MAX][MAX];
	char data1[MAX][MAX];

	head = (Char_code *)malloc(LEN);
	head->next = NULL;
	head->count = 0;

	int i;
	int j;
	int count = 0;


	read_file(head);
	show(head);
	p = head->next;
	while (p)
	{
		count++;
		p = p->next;
	}

	printf("count %d\n", count);
	
	Creat_Huffman(ht, head, count);
	Get_Code(ht, data, count);

	for (i = 1; i <= count; i++)
	{
		j = 0;

		while ((*(*(data + i) + j)) != '\0')
		{
			printf("%c", (*(*(data + i) + j)));
			j++;
		}

		printf("\n");

	}
	write_file(head);

	write_import(ht, data, count , 1);
	printf("kaishi\n");

	code = get_tree(code);

	printf("\n\n");
	show(code);
//	Print(ht, count * 2 -1);
	Creat_Huffman(ht, head, count);
	Get_Code(ht, data1, count);

	for (i = 1; i <= count; i++)
	{
		j = 0;

		while ((*(*(data1 + i) + j)) != '\0')
		{
			printf("%c", (*(*(data1 + i) + j)));
			j++;
		}

		printf("\n");

	}

	return EXIT_SUCCESS;
}
