/*
 * =====================================================================================
 *
 *       Filename:  final.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月23日 01时02分59秒
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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define MAX 1024
#define N 256       //定义最大值
#define M 2 * N - 1  
#define LEN sizeof(Char_code)

typedef struct code
{
	char ch;
	int count;
	char tmp[MAX];
	struct code *next;
}CODE;

typedef char** DATA;   //定义编码存放类型

typedef struct  charactor
{
	char ch;
	int count;
	struct charactor *next;
}Char_code;

typedef struct 
{
	char ch;
	int count;
}LINK;

typedef struct         //哈夫曼编码结构成员
{
	Char_code code;        //出现的频率
	int parent;        //父节点序号
	int Lchild;        //左孩子序号
	int Rchild;        //右孩子序号
	int flag;          //标志是被处理，默认为0，未处理
	int where;
}HTNODE;

char do_press(char *data)
{
	int tmp[8] = {0};
	int asci = 0;
	int i;

	for (i = 0; i <= 7; i++)
	{
		tmp[i] = (data[i] - '0');
	}


	for (i = 0; i <= 7; i++)
	{
		asci += tmp[i] * (int) pow(2, 7 - i);
	}

	return (char)asci;
}
void do_unpress(unsigned char data, char *need)
{
	int flag = (int)data;
	int tmp[8] = {0};
	int i = 7;
	int j = 0;
	int m;
	
	if (flag == 0)
	{
		strcpy(need, "00000000");
		return ;
	}

	while (flag != 0)
	{
		m = flag % 2;
		flag /= 2;
		tmp[i--] = m;
	}

	memset(need, '\0', 8);
	for (i = 0; i < 8; i++)
	{
		*(need + i) = tmp[i] + '0';
	}
	return ;
}
void press()
{
	unsigned char ch;
	int i;
	int fd1;
	int fd2;
	int ret1;
	char temp[8];
	char data;
	int t = 0;
	int j;
	long long size;
	struct stat buf;
	char longth[20];
	fd1 = open("/home/gaoyuan/source/from.txt", O_RDONLY);
	fd2 = open("/home/gaoyuan/source/asci.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	fstat(fd1, &buf);

	size = buf.st_size;
	memset(longth, '\0', sizeof(longth));

	sprintf(longth, "%lld", size);

	write(fd2, longth, sizeof(longth));

	while (1)
	{
		ret1 = read(fd1, temp, 8);

		ch = 0;

	for  (j = 0; j <= 7; j++)
		{
			if (temp[j] == '1')
			{
				ch = (ch << 1) | 1;

			}
			else
			{
				ch = (ch << 1);
			}
		}

		data = do_press(temp);
		memset(temp, '0', 8);

		write(fd2, &ch, 1);
		if (ret1 < 8)
		{
			break;
		}
	
	}

}
void unpress()
{
	int fd1;
	int ret1;
	int fd2;
	char data;
	char file[8];

	fd1 = open("/home/gaoyuan/source/asci.txt", O_RDONLY);
	fd2 = open("/home/gaoyuan/source/to.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	long long size;
	char longth[20];

	read(fd1, longth, 20);


	size = atol(longth) ;

	while (1)
	{
		ret1 = read(fd1, &data, 1);


		do_unpress(data, file);

		if (size < 8)
		{
			write(fd2, file, size);
			break;
		}
		else
		{
			write(fd2, file, 8);
		}
		size -= 8;

	}

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
	
	       
	
	 // 初始化选择函数的初始位置
	

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


	 // 开始比较，已经比较过的此次不再比较
	

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


void Creat_Huffman_file (HTNODE * ht, CODE *head, int n)
{

	int m;     
	int i, s1, ls2;
	int flag1 = 1;
	int flag2 = 1;
	CODE *p = head->next;
	CODE *q = p;
	int num = 0;
	while (q)
	{
		num++;
		q = q->next;
	}

	m = 2 * num - 1;


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
		ht[i].where = i;
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
		ht[i].where = i;
	}
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
		ht[i].where = i;
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
		ht[i].where = i;
	}
	/*
	 * 从第n-1个结点开始构造新结点
	 */

	for (i = n + 1; i <= m; i++)
	{
		Select(ht, i - 1, &flag1, &flag2);

		printf("min  = %d sec = %d\n", flag1, flag2);
		ht[flag1].flag = -1;
		ht[flag2].flag = -1;
		ht[i].code.count= (ht[flag1].code.count + ht[flag2].code.count);
		ht[i].Lchild = flag1;
		ht[i].Rchild = flag2;
		ht[flag1].parent = i;
		ht[flag2].parent = i;
	}
}

void Get_Code_file (HTNODE * ht, char hc[][MAX], int n, CODE *head)
{
	char cd[N];                          //临时储存编码
	int start;
	int parent;
	int i;
	int child;

	CODE *p = head->next;
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
		strcpy(hc[i], &cd[start]);                      //复制到编码组
		strcpy(p->tmp, hc[i]);
		p = p->next;
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

		strcpy(hc[i], &cd[start]);                      //复制到编码组
	} 
}
void write_import(HTNODE *ht, char data[][MAX], int num, char *name)
{
	int i;
	int fd;
	int flag;
	char tmp[1024];
	char count[1024];

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);

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

		memset(count, '\0', sizeof(tmp));
		sprintf(count, "%d", ht[i].code.count);
		strcat(tmp, count);
		strcat(tmp, "#");
		strcat(tmp, "\n");
			
		flag = write(fd, tmp, strlen(tmp));
	
	}
	close(fd);
}

CODE *get_tree(CODE *head, char *name)
{
	int fd;
	int i;
	int ret;
	int flag;
	char tmp[1024];
	char ch;
	char count[MAX];
	int data;
	int jj = 0;

	CODE *p, *q;
	q = head = (CODE *)malloc(sizeof(CODE));
	head->next = NULL;
	fd = open(name, O_RDONLY);
	while (1)
	{
		i = 0;
		memset(tmp, '\0', sizeof(tmp));
		while (1)
		{
			ret = read(fd, &tmp[i++], 1);

			if (ret <= 0)
			{

				return head;
			}

			if (tmp[i - 1] == '#')
			{
				read(fd, &tmp[i], 1);
				if (tmp[i++] == '\n')
				{
					break;
				}
			}
		}
	p = (CODE *)malloc(sizeof(CODE));
		ch = tmp[0];

		if (tmp[0] == 58 && tmp[1] != ':')
		{
			ch = 0;
		}

		flag = 0;
		for (i = 0; i < strlen(tmp); i++)
		{
			if (tmp[i] == ':')
			{
				flag++;
			}
			if (tmp[i] == ':' && flag == 2)
			{
				if (tmp[i - 1] == ':')
				{
					flag = 1;
					continue;
				}
				strcpy(count, &tmp[i + 1]);
				data = atoi(count);

				break;
			}

		}

		p->ch = ch;
		p->count = data;
		strcpy(p->tmp, "\0");

		p->next = NULL;
		q->next = p;
		q = p;

	}
	close(fd);
	return head;
}

void Count_quick (char ch,  LINK *code)
{

	(code + (ch + 128))->count++;
	(code + (ch + 128))->ch = ch;
}

Char_code *Count(LINK *code, Char_code *head)
{
	int i;
	Char_code *p;
	head->next = NULL;


	for (i = 0; i <= 255 ; i++)
	{
		if ( (code + i)->count == 0)
		{
			continue;
		}
		p = (Char_code *)malloc(sizeof(Char_code));

		p->ch = (code + i)->ch;
		p->count = (code + i)->count;
		p->next = head->next;
		head->next = p;
	}

	return head;
}

void trans_to_code(CODE *head, char *data, char *name)
{
	int fd1;
	int ret1;
	int fd2;
	int ret2;
	char tmp;
	CODE *p;

	int flag = 10;
	int test = 0;

	fd1 = open(data, O_RDONLY);
	fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC , 0664);
	while (1)
	{
		ret1 = read(fd1, &tmp, 1);
		p = head->next;

		if (tmp == 0)
		{
			test++;
		}
		if (ret1 <= 0)
		{
			break;
		}

		while (p)
		{
			if (p->ch == tmp)
			{
				write(fd2, p->tmp, strlen(p->tmp));
				break;
			}
			p = p->next;
		}

		if (p == NULL)
	{
			if (tmp == 0)
			{
			  flag = write(fd2, &tmp, 1);
			}
		}
	}
}

Char_code *read_file(Char_code *head, char *name)

{
	int fd;
	int fd2;
	int ret;
	char tmp;
	int count;
	Char_code *p ;
	head = (Char_code *)malloc(sizeof(Char_code));
	head->next = NULL;
	LINK Array[256];
	int sum = 0;

	fd = open(name, O_RDONLY);

	while (1)
	{
		ret = read(fd, &tmp, sizeof(char));

		sum += ret;
		if (ret != 1)
		{
			break;
		}
		Count_quick(tmp, Array);
	}
	head = Count(Array, head);

	close(fd);
	return head;
}
void Get_Language(HTNODE *ht, int num, char *data, char *file)
{
	int i;
	int start;
	int fd;
	int fd2;
	int fd3;

	int ret2;
	int ret;
	char tmp;
	char ch;
	char flag[2];
	int j;

	fd = open (data, O_RDONLY);
	fd2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	HTNODE child, parent;
	int jj = 0;

	while (1)
	{
		i = 1;

		start = 0;
		parent = ht[num * 2 - 1];

		j = 0;

		while (1)
		{
			ret = read(fd, &tmp, 1);
			if (ret <= 0)
			{
				return;
			}

			if (tmp == '0')
			{
				child = ht[parent.Lchild];
			}
			else
			{
				child = ht[parent.Rchild];
			}
			parent = child;

			start++;

			if (ht[child.where].Lchild == 0 && ht[child.where].Rchild == 0)
			{
				write(fd2, &child.code.ch, 1);
				break;
			}
		}
	}
}

int get_count(CODE *head)
{
	CODE *p;
	int count = 0;

	p = head->next;

	while (p)
	{
		count++;
		p = p->next;
	}

	return count;
}
int get_len(Char_code *head)
{
	Char_code *p;
	int count = 0;

	p = head->next;

	while (p)
	{
		count++;
		p = p->next;
	}

	return count;
}

int main(int argc, char *argv[])
{
	HTNODE ht[MAX];
	HTNODE hs[MAX];
	Char_code *head = NULL;;
	Char_code *p;
	Char_code *pp;
	CODE *code = NULL;
	CODE *q;
	char data[MAX][MAX];
	char data1[MAX][MAX];
	int i;
	int j;
	int count = 0;
	int cou = 0;
	int pch = 0;
	int qch = 0;

	int ii, jj;

	head = read_file(head, "/home/gaoyuan/source/321.jpg");

	count = get_len(head);

	p = head;

	Creat_Huffman(ht, head, count);
	Print(ht, count * 2 -1);



	Get_Code(ht, data1, count);
	write_import(ht, data1, count , "/home/gaoyuan/source/code.txt");
	
	code = get_tree(code, "/home/gaoyuan/source/code.txt");

	cou = get_count(code);

q = code;


	Creat_Huffman_file(hs, code, count);
	Print(hs, count * 2 -1);

	Get_Code_file(hs, data, count, code);


	trans_to_code(code, "/home/gaoyuan/source/321.jpg", "/home/gaoyuan/source/from.txt");

	press();
	unpress();

	Get_Language(hs, count, "/home/gaoyuan/source/to.txt", "/home/gaoyuan/source/yuanyuan.jpg");



	return EXIT_SUCCESS;
}
