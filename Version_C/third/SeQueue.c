/*
 * =====================================================================================
 *
 *       Filename:  SeQueue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月24日 10时16分03秒
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

#define MAX 100

typedef struct 
{
	int data[MAX];
	int rear, front;
}SeQueue;

SeQueue *initSeQueue ( SeQueue *p)
{
	p = malloc(sizeof(SeQueue));
	p ->front = p->rear = MAX;

	return p;
}

int in_SeQuque(SeQueue *q, int data)
{
	if ((q->rear + 1) % MAX == q->front)
	{
		return -1;
	}

	else
	{
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear] = dara;
		return 0;
	}
}

int out_SeQueue(SeQueue *q, int *data)
{
	if (q->front == q->rear)
	{
		return -1;
	}
	else
	{
		q->front = (q->front + 1) % MAX;
		*data = q->data[q->front];
		return 0;
	}
}

int empty_SeQueue(SeQueue *q)
{
	if (q->front == q->rear)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

