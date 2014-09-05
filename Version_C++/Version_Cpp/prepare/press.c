/*
 * =====================================================================================
 *
 *       Filename:  press.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月22日 18时35分35秒
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

char do_press(char *data)
{
	int tmp[8] = {0};
	int asci = 0;
	int i;

	for (i = 0; i <= 7; i++)
	{
		tmp[i] = (data[i] - '0');
	}

//	for (i = 0; i <= 7; i++)
//	{
//		printf("%d", tmp[i]);
//	}
//	printf("\n");

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

//	printf("kankan %d\n", data);

//	if (data == 0)
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
//	while (j <= 7)
//	{
//		printf("data %c\n", data);

//		printf("&%d\n", data & 1);
//		getchar();
//		if (data & 128 == 1)
//		{
//			*(need + j) = '1';
//		}
//		else
//		{
//			*(need + j) = '0';
//		}

//		data = data << 1;
//		j++;;

//	}

//	strcpy(need, tmp);

//	printf("%s\n", need);


//	getchar();

	for (i = 0; i < 8; i++)
	{
		printf("%d", tmp[i]);
	}

	for (i = 0; i < 8; i++)
	{
		*(need + i) = tmp[i] + '0';
	}
//	printf("test%s\n", need);
//	getchar();
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
//fd1 = open("data.txt", O_RDONLY);
	fd1 = open("from.txt", O_RDONLY);
	fd2 = open("asci.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

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

		//		ch = ch | 1;
			}
			else
			{
		//		;
				ch = (ch << 1);
			}
		//	printf("")
		}

//		printf("%d\n", ch);
//		getchar();
		data = do_press(temp);
		memset(temp, '0', 8);
//		write(fd2, &data, 1);

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

	fd1 = open("asci.txt", O_RDONLY);
	fd2 = open("to.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	long long size;
	char longth[20];

	read(fd1, longth, 20);

//	sprintf(&size, "%s", longth);

	size = atol(longth) - 1;

	while (1)
	{
		ret1 = read(fd1, &data, 1);

		//	longth -= ret1;

	//	if (ret1 != 1)
	//	{
	//		break;
	//	}
		do_unpress(data, file);

		if (size < 8)
		{
			printf("\nsize %lld\n", size);
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
int main(int argc, char *argv[])
{
	/*
	char flag;

	char test[8];
	char data[8] = {"01001101"};
	flag = do_press(data);

	printf("%c\n", flag);

	do_unpress(flag, test);

	printf("%s  %d\n", test, (int)strlen(test));

	*/
	press();
	unpress();
	return EXIT_SUCCESS;
}

