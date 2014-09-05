/*
 * =====================================================================================
 *
 *       Filename:  math3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月12日 22时45分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct number
{
	int num[MAXSIZE];
	int len;
}Number;

typedef struct operate
{
	char operate[MAXSIZE];
	int len;
}Operate;

int empty_num(Number *s)
{
	if (s->len == -1)
	{
		return 1;
	}

	return 0;
}

int push_num(Number *s, int x)
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

int pop_num(Number *s, int * data)
{
	if (empty_num(s) == 1)
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

int top_number(Number *s, int *data)
{
	if (empty_num(s) == 1)
	{
		return 0;
	}

	else 
	{
		*data = s->num[s->len];
		return 1;
	}
}
Number * init_number()
{
	Number *m;

	m = malloc(sizeof(Number));
	m->len = -1;

	return m;
}

int empty_operate(Operate *s)
{
	if (s->len == -1)
	{
		return 1;
	}

	return 0;
}

int push_operate(Operate *s, char oper)
{
	if (s->len == MAXSIZE - 1)
	{
		return 0;
	}

	else
	{
		s->len++;
		s->operate[s->len] = oper;
		return 1;
	}
}

int pop_operate(Operate *s, char *oper)
{
	if (empty_operate(s) == 1)
	{
		return 0;
	}

	else 
	{
		*oper = s->operate[s->len];
		s->len--;
		return 1;
	}
}

char top_operate(Operate *s)
{
	if (s->len == -1)
	{
		return 'n';
	}

	else
	{
		return s->operate[s->len];
	}
}

Operate * init_operate()
{
	Operate *m;

	m = malloc(sizeof(Operate));
	m->len = -1;

	return m;
}

int if_operte(char c)
{
	if (c == '*' || c == '+' || c == '-' || c == '/' || c == '(' || c == ')')
	{
		return 1;
	}

	return 0;
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

	else if (a == '(' || a == ')')
	{
		return 3;
	}

	else if (a == '#')
	{
		return 0;
	}
}

int judge_level(char a, char b)
{
		return (level(a) - level(b));
}
void translate(char * quest, char * ans ,int n)
{
	Operate *tmp;
	char c;

	tmp = init_operate();
	push_operate(tmp, '#');

	while (n--)
	{
//		printf("%c\n", *quest);
		if ((*quest) >= '0' && (*quest) <= '9')
		{
			*ans++ = *quest;
		}

		else if ((*quest) == '(')   //如果是（，直接压栈
		{
			push_operate(tmp, (*quest));
		//	printf("ya %c\n", top_operate(tmp));
		}

		else if ((*quest) == ')')  //如果是），弹栈到数组，直到遇到（
		{
			while (top_operate(tmp) != '(')
			{
				pop_operate(tmp, &c);
				*ans++ = c;
		//		printf("c = %c\n", c);
				*ans++ = ' ';
		//		printf("ding %c %d\n", top_operate(tmp), tmp->len);
		//		getchar();
			}
			pop_operate(tmp, &c);
		}

		else if (if_operte(*quest) == 1)
		{
			if (top_operate(tmp) == '(')
			{
				push_operate(tmp, *quest);
			}

			else if (judge_level(*quest, top_operate(tmp)) > 0)  //如果扫描到的运算符优先级高于栈顶优先级，将运算符压栈
			{
				push_operate(tmp, *quest);
			}

			else if (judge_level(*quest, top_operate(tmp)) <= 0)  //如果扫描到的运算符优先级低于或等于栈顶优先级，依次弹出栈顶元素到数组，直到遇到优先级比扫描到的优先级低的
			{
				while (judge_level((*quest), top_operate(tmp)) <= 0 && (top_operate(tmp) != '#'))
				{
					pop_operate(tmp, &c);
		//			printf("tan %c\n", c);
					*ans++ = c;
					*ans++ = ' ';
			//		*ans++ = *quest;
				}
				push_operate(tmp, *quest);
		//		printf("栈顶%c\n", top_operate(tmp));

			}
		}

		if (( if_operte(*quest)  == 0) &&  (if_operte(*(quest + 1)) == 1))
		{
			*ans++ = ' ';
		}
		quest++;
	}

//	printf("剩余%d\n", tmp->len);
	while (tmp->len != 0)
	{
		pop_operate(tmp, &c);
		*ans++ = c;
		*ans++ = ' ';
	}

	*ans = '\0';
}

int calculate (int num1, int num2, char ope)
{
	int result;
	
	switch (ope)
	{
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
	}

	return result;
}

void result (char * string, int n)
{
	char exp;
	char *p;
	int num, num3;
	int num1, num2;
	int i = 0, j = 0;
	int flag = 0;
	int tmp[MAXSIZE];
	char ope[MAXSIZE];
	Operate *operate;
	Number  *number;


	operate = init_operate();
	number  = init_number();
	p = string;

	while (*p != '\0')
	{
		num = 0;
		flag = 0;


		while ((*p) >= '0' && (*p) <= '9')
		{
			flag = 1;
			num = (*p - '0') + num * 10;
			p++;
		}

		if (flag == 1)
		{
			tmp[i++] = num;
			push_num(number, num);
		//	printf("压栈%d大小%d\n", num, number->len);
		}

		if (if_operte(*p) == 1)
		{
			pop_num(number, &num1);
			pop_num(number, &num2);


		//	printf("弹出%d %d\n", num1, num2);
		//	printf("还剩%d\n", number->len);
			push_num(number, calculate(num2, num1, *p));
			top_number(number, &num3);
		///	printf("%d %c %d = %d\n", num2, *p, num1, num3);
		//	printf("压栈%d\n", calculate(num2, num1, *p));
		
		}

		p++;
	}

	top_number(number, &num);
	printf("结果是%d\n", num);

}

int main(int argc, char *argv[])
{
	char string1[100];
	char string2[100];

	char *p, *q;

	printf("请输入\n");
	scanf("%s", string1);
//	printf("%s\n", string1);
	string1[strlen(string1)] = '\0';
//	printf("完了\n");

	p = string1;
	q = string2;

	translate(p, q, strlen(string1));

	printf("后缀表达式为\n%s\n", string2);
	string2[strlen(string2)] = '\0';

	result(string2, strlen(string2));


	return EXIT_SUCCESS;
}

