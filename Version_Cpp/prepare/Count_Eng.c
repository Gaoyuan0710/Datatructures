/*
 * =====================================================================================
 *
 *       Filename:  Count.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月08日 19时43分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 690892695@qq.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "Huffman.h"

#define LEN sizeof(Char_code)
//#define MAX 256
/*
typedef struct charactor
{
	char ch;
	int count;
	struct charactor *next;
}Char_code;
*/
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

void write_code(char ch)
{
	int fd;
	int ret;


	fd = open("c.txt", O_RDONLY | O_);
	ret = write(fd, ch, 1);
}

void show(Char_code *head)
{
	Char_code *p;

	p = head->next;

	while (p != NULL)
	{
		printf("%c:%d\n", p->ch, p->count);
		p = p->next;
	}
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
	char data[MAX][MAX];

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

	Print(ht, count * 2 -1);
	return EXIT_SUCCESS;
}

