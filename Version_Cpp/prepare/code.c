/*
 * =====================================================================================
 *
 *       Filename:  code.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月16日 20时23分13秒
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
//#include "Huffman.h"
//#include <>
typedef struct code
{
	char ch;
	int count;
	char tmp[256];
	struct code *next;
}CODE;

/*
void make_code_file(CODE *head)
{
	
}
CODE *get_code_link(CODE *head, char data[][256], int num)
{
	int i;
	CODE *p;

	head = (CODE *)malloc(sizeof(CODE));
	head->next = NULL;

	for (i = 1; i <= num; i++)
	{
		p = (CODE *)malloc(sizeof(CODE));
		p->ch = 
	}


}
*/

void write_import(HTNODE ht, char data[][256], int num , int flag)
{
	int i;
	int fd;
	int tmp[1024];

	fd = open("code.txt", O_WRDNLY | O_CREAT | O_TRUNC, 0777);

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
		write(fd, tmp, strlen(tmp));

		memset(tmp, '\0', sizeof(tmp));
		sprintf(tmp, "%d", ht[i].code.count);
		strcat(tmp, "\n");
		write(fd, tmp, strlen(tmp));
	}

	printf("写完了\n");

	close(fd);
}
/*
int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}
*/
