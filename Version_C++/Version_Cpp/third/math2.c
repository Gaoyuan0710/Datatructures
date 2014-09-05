/*
 * =====================================================================================
 *
 *       Filename:  share.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月04日 21时27分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct number
{
	int num[MAXSIZE];
	int len;
}Number;

typedef struct operate
{
	char operat[MAXSIZE];
	int len;
}Operate;

int empty_Num(Number * s)
{
	if (s->len == -1)
	{
		return 1;
	}

	return 0;

}


int push_Num(Number * s, int x)
{
	if (s->len == MAXSIZE - 1)
	{
		return 0;
	}

	else
	{
		s->len++;
		s->num[s->len] = x;
		return 1;
	}
}

int pop_Num(Number * s, int * data)
{
	if (empty_Num(s) == 1)
	{
		return 0;
	}

	else
	{
		*data = s->num[s->len];
		s->len--;
		return 1;
	}
}

int top_Number(Number * s, int * data)
{
	if (empty_Num(s) == 1)
	{
		return 0;
	}

	else 
	{
		*data = s->num[s->len];
		return 1;
	}
}

int empty_Operate(Operate * s)
{
	if (s->len == -1)
	{
		return 1;
	}

	return 0;

}


int push_Operate(Operate * s, char Oper)
{
	if (s->len == MAXSIZE - 1)
	{
		return 0;
	}

	else
	{
		s->len++;
		s->operat[s->len] = Oper;
		return 1;
	}
}

int pop_Operate(Operate * s, char * Oper)
{
	if (empty_Operate(s) == 1)
	{
		return 0;
	}

	else
	{
		*Oper = s->operat[s->len];
		s->len--;
		return 1;
	}
}

char top_Operate(Operate * s)
{
	if (empty_Operate(s) == 1)
	{
		return 'n';
	}

	else 
	{
		return s->operat[s->len];
	}
}


Operate * init_Operate()
{
	Operate *m;

	m = malloc(sizeof(Operate));
	m->len = -1;

	return m;

}

Number * init_Number()
{
	Number *m;

	m = malloc(sizeof(Number));
	m->len = -1;

	return m;

}

int if_operate(char c)
{
	if (c == '*' || c == '+' || c == '-' || c == '/')
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int level(char a)
{
	if (a == '+' || a == '-')
	{
		return 1;
	}

	else if (a == '*' || a == '/')
	{
		return 2;
	}
}

int judge_level(char a, char b)
{
	if (a == '#')
	{
		printf("结尾\n");
		return 3;
	}

	else if (b == '#')
	{
		return -3;
	}

	else 
	{
		return (level(a) - level(b));
	}
}

int calculate(int a, int b, char c)
{
	int result;

	if (c == '+')
	{
		return (a + b);
	}
	else if (c == '-')
	{
		return (a - b);
	}
	else if (c == '*')
	{
		return (a * b);
	}
	else if (c == '\\')
	{
		result = a/b;
		return result;
	}
}

int Exp(char *string, int i)
{

	Number *number;
	Operate *operate;
	char *p;
	int data;
	int flag;
	int a, b;
	char ope;
	int result;
	int result_final = 0;
	int test;
	char ch;

	p = string;

	number = init_Number();
	operate = init_Operate();

	while (*p != '#')
	{
		printf("%c", *p++);
	}
	printf("\n");

	p = string;

	push_Operate(operate, '#');


	while ( i-- )
	{
		printf("i = %d\n", i);
		if((*p) > '0' && (*p) < '9')                     //如果为操作符号
		{
			data = *p - '0';
			p++;

			while ( (*p) >= '0' && (*p) <= '9')
			{
				data = data *10 + *p - '0';
				p++;
			}

			push_Num(number, data);
			top_Number(number, &test);
		//	printf("数字栈顶部 %d\n", test);
		//	printf("%c\n", *p);
		}

		else 
		{

			flag = judge_level(*p, top_Operate(operate));
			printf("当前符号%c， 栈顶符号%c flag = %d\n", *p, top_Operate(operate), flag);

			if ((flag > 0 && flag != 3 )|| flag == -3)
			{
				push_Operate(operate, *p);
			}

			else if (flag == 3)
			{
				pop_Num(number, &a);
				pop_Num(number, &b);
				pop_Operate(operate, &ope);
				result = calculate(a, b, ope);
				printf("%d %c %d = %d\n", a, ope, b, result);
			//	push_Operate(operate, *p);
				push_Num(number, result);
				printf("当前符号栈顶 %c\n", top_Operate(operate));

			}
			else if (flag < 0 || flag == 0 )
			{
				pop_Num(number, &a);
				pop_Num(number, &b);
				sleep(2);
				pop_Operate(operate, &ope);
				result = calculate(a, b, ope);
		        printf("%d %c %d = %d\n", a, ope, b, result);
				push_Operate(operate, *p);
				push_Num(number, result);
			}
			p++;
		}

	}

	while (top_Operate(operate) != '#')
	{
		pop_Num(number, &a);
		pop_Num(number, &b);
		sleep(2);
		pop_Operate(operate, &ope);
		result = calculate(a, b, ope);
		printf("%d %c %d = %d\n", a, ope, b, result);
					push_Num(number, result);

	}
	pop_Num(number, &result_final);

	return result_final;


	
}


int main(int argc, char *argv[])
{
	char string[100];
	int num;
	int len;

	printf("请输入表达式:");
	scanf("%s", string);

	len = strlen (string);

	num = Exp(string, len);

	printf("num = %d\n", num);

	





	return EXIT_SUCCESS;
}

