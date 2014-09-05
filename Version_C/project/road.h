/*
 * =====================================================================================
 *
 *       Filename:  road.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月10日 10时55分39秒
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

typedef struct infomation
{
	int num;
	char name[50];
	char introduction[100];
}INFOMATION;

typedef struct ArcNode
{
	int adj;
	int weight;
	struct ArcNode *next;
}ArcNode;

typedef struct
{
	int num;
	char name[50];
	ArcNode *head;
}VertexNode;

typedef struct
{
	VertexNode vertex[MAX_NUM];
	int vexnum;
	int arcnum;
}Graph;


typedef struct 
{
	int arcs[MAX][MAX];
	char vex[MAX];
	int vexnum;
	int arcnum;
}AdjMatrix;

