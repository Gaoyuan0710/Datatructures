/*
 * =====================================================================================
 *
 *       Filename:  72_7.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年09月24日 19时22分24秒
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

#define MAXSIZE 10

typedef struct 
{
	int data[MAXSIZE];
	int front, rear;
}Queue;

Queue * init_Queue ()
{
	Queue * q;

	q = malloc (sizeof(Queue));
	q->front = q->rear = MAXSIZE - 1;
	return q;
}

int empty_Queue (Queue * q)
{
	if (q->front == q->rear)
	{
		return 1;
	}

	return 0;
}

int full_Queue (Queue * q)
{
	if (((q->rear + 1) % MAXSIZE) == q->front)
	{
		return 1;
	}

	return 0;
}

int in_Queue (Queue * q, int data)
{
	if ((q->rear + 1) % MAXSIZE == q->front)  //队满
	{
		return 0;
	}

	q->rear = (q->rear + 1) % MAXSIZE;
	q->data[q->rear] = data;
	return 1;
}

int out_Queue(Queue * q, int *data)
{
	if (q->front == q->rear)
	{
		return 0;
	}

	q->front = (q->front + 1) % MAXSIZE;
	* data = q->data[q->front];
	return 1;
}

int main(int argc, char *argv[])
{
	Queue *p, *q;
	int i;

	p = init_Queue();

	for(i = 0; i < 10; i++)
	{
		in_Queue(p, i);
	}

	printf("%d\n", full_Queue(p));


	return EXIT_SUCCESS;
}

