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

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LEN sizeof(Charactor)

typedef struct charactor
{
	char ch[3];
	int count;
	struct charactor *next;
}Charactor;

Charactor *find (char *ch, Charactor *head)
{
//	int flag = 1;
	Charactor *p = head->next;

	while (p != NULL )
	{
	//	printf("2%s", p->ch);
		if (strcmp(p->ch, ch) == 0)
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

		strcpy(p->ch, ch);
		p->count = 1;

		p->next = head->next;
		head->next = p;
	}

	return head;
}

void Count(Charactor *head)
{
	Charactor *p;

	p = head->next;

	while (p != NULL)
	{
		printf("%s:%d\n", p->ch, p->count);
		p = p->next;
	}
}
void read_words(Charactor *head)
//Charactor *read_words(Charactor *head)
{
	int fd;
	int ret;
	char ch[3];
	char tmp[1024];
	int i;

//	int fd;
	fd = open("a.txt", O_RDONLY);
//	FILE *fp;
//	fp = fopen("a.txt", "r+");

//	while (1)
//	{
//		ret = fscanf(fp, "%2s", ch);
//		ch[3] = '\0';
//		printf("%s", ch);
//		head = find(ch, head);

	ret = read(fd, tmp, 1024);
	printf("%s\n", tmp);
char *p;
p = tmp;

	while (1)
	{
	ret = sscanf(p, "%2s", ch);
	head = find(ch, head);
	for (i = 0; i < strlen(ch); i++)
	  printf("%c", ch[i]);
//	printf("%s", ch);
	p+=2;
	if (ret <= 0)
	  break;
	}
//		if (ret <= 0)
//		{
//			break;
//		}
	
//	}
	close(fd);

}
//Charactor *
int main(int argc, char *argv[])
{
	Charactor *head;
	head = (Charactor *)malloc(sizeof(Charactor));
	head->next = NULL;

	int i;

//	char data[1000] = {"我不认识你，你是谁啊，你好"};

//	for (i = 0; i < strlen(data); i++)
//	{
///		printf("%c\t", data[i]);
//	}


//	head = find(data, head);
//	Count(head);

	read_words(head);
	Count(head);
	return EXIT_SUCCESS;
}

