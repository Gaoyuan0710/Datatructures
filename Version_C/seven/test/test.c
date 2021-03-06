
/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月08日 12时08分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 690892695@qq.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

/*
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	return EXIT_SUCCESS;
}
*/
#include<malloc.h>
#include<stdio.h>
#include<string.h>
//#define NULL 0
#define MAX 100

struct edgenode
    {
        int     no;
        struct edgenode *next;
    };

struct vex
    {
        struct edgenode *first;
    };

typedef struct vex adjlist;     //
int     n, e;                   //
adjlist *g;

void initalize ()               //
{
    int     i, s, t;
    struct edgenode *p, *q;

    printf ("Enter the n and e:");
    scanf ("%d %d", &n, &e);
    g = (adjlist *) malloc (n * sizeof (adjlist));
    for(i = 0; i < n; i++)
        g[i].first = NULL;
    for(i = 1; i <= e; i++)
    {
        printf ("The %d edge’s start and end:", i);
        scanf ("%d %d", &s, &t);
//p=(struct edgenode *)malloc(sizeof(struct edgenode));
        q = (struct edgenode *) malloc (sizeof (struct edgenode));
//p->no=s;
        q->no = t;
//p->next=g[t].first;g[t].first=p; 此句加上即可变为无向图。
        q->next = g[s].first;
        g[s].first = q;
    }
}

void path (int st, int en)
{
    int    *visit, *stack, top, v, head = 1, i;
    struct edgenode *p;

    visit = (int *) malloc (n * sizeof (int));
    stack = (int *) malloc ((n + 1) * sizeof (int));
    for(i = 0; i < n; i++)
        visit[i] = 0;
    v = st;
    visit[st] = 1;
    top = 1;
    stack[top] = v;
    do
    {
        if(head == 1)
        {
            p = g[v].first;
            head = 0;
        }
        else
            p = p->next;
        if(p)
        {
            if(visit[p->no] == 0)
            {
                visit[p->no] = 1;
                top++;
                stack[top] = p->no;
                if(p->no == en)
                {
                    for(i = 1; i <= top; i++)
                        printf ("%d ", stack[i]);
                    printf ("\n");
                    visit[en] = 0;
                    top--;
                    v = stack[top];
                    head = 0;
                }
                else
                {
                    v = stack[top];
                    head = 1;
                }
            }                   //
        }
        else
        {
            visit[stack[top--]] = 0;    //
            if(top)
            {
                p = g[stack[top]].first;
                while(p->no != v)
                    p = p->next;
                v = stack[top];
                head = 0;
            }
        }
    }
    while(top);
}

main ()
{
    int     st, en;             //

    initalize ();
    printf ("Enter the start and the end:");
    scanf ("%d %d", &st, &en);
    path (st, en);
    getchar ();
    getchar ();
}
