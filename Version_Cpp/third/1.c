#include<malloc.h>
#include<limits.h>
#include<stdio.h>
//#include<math.h>
//#include<process.h>
//#include<conio.h>
//#include<dos.h>
#define CLS system("cls")

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 1

#define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
#define STACKINCREMENT 2 /* 存储空间分配增量 */
#define N 8     /*定义棋盘大小*/
typedef  int Status;

typedef struct chess
{
	int x;
	int y;
	int z;
}SElemType; 

int map[N][N][8]; /*按各点权值递升存放待走方向,每点8个*/
int weight[N][N]; /*各点的权值*/
int board[N][N];  /*棋盘,未走过时值为0,走过后值为1*/
static SElemType HTry[8]=  /* 8个候选方向的偏移值*/
{
	{-2, 1, 0},{ -1, 2, 0},{ 1, 2, 0},{ 2, 1, 0},{ 2, -1, 0}, {1, -2, 0}, {-1, -2, 0}, {-2, -1, 0} 
};
void setweight();/*求各点权值*/
void setmap();   /*各点的8个方向按权值递增排列*/
void Path(int x, int y); /*主算法函数,踏遍棋盘*/

/*栈的顺序存储表示 */
typedef struct SqStack
{
	SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
	SElemType *top; /* 栈顶指针 */
	int stacksize; /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */
Status InitStack(SqStack *S) /* 构造一个空栈S */
{ 
	S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S->base)
		exit(OVERFLOW); /* 存储分配失败 */
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return OK;
}
Status StackEmpty(SqStack S)
{ /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}
Status GetTop(SqStack S,SElemType *e)
{ /* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
	if(S.top>S.base)
	{
		*e=*(S.top-1);
		return OK;
	}
	else
		return ERROR;
}
Status SetTop(SqStack S,SElemType *e)
{
	if(S.top>S.base)
	{
		(e->z)++;
		*(S.top-1)=*e;
		return OK;
	}
	else
		return ERROR;
}
Status Push(SqStack *S,SElemType e)
{ /* 插入元素e为新的栈顶元素 */
	if(S->top-S->base==S->stacksize) /* 栈满，追加存储空间 */
	{
		S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base)
			exit(OVERFLOW); /* 存储分配失败 */
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCREMENT;
	}
	*(S->top)++=e;
	return OK;
}
Status Pop(SqStack *S,SElemType *e)
{ /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
	if((*S).top==(*S).base)
		return ERROR;
	*e=*--(*S).top;
	return OK;
}
void main()/*主函数*/
{
	int x,y;
	int i,j,k=0;
	for(i=0;i<N;i++)
        for(j=0;j<N;j++)
			board[i][j]=0;
		setweight();
		setmap();
		while(1)
		{           
			printf("输入马的行坐标 X (from 0 to 7):");
			scanf("%d",&x);
			printf("输入马的列坐标 Y (from 0 to 7):");
			scanf("\n%d",&y);
			if(x<0||x>7||y<0||y>7)
				
			{printf("输入错误!\n\n");
			flushall();}
			
			else
				break;
		}
		Path(x,y);
		
}/*end main()*/

/*求各点权值:可走的方向数.该值越小,则被上一点选中的可能性越大*/
void setweight()
{
    int i,j,k,x1,y1;
	for(i=0;i<N;i++)/*for 1*/
	{
		for(j=0;j<N;j++)/*for 2*/
		{      
			weight[i][j]=0;
			for(k=0;k<N;k++)/*for 2*/
			{                  
				x1=i+HTry[k].x;
				y1=j+HTry[k].y;
				if(x1>=0&&x1<N&&y1>=0&&y1<N)
				{
					weight[i][j]++;/*即在8个方向中，（i，j）点有几个方向可以移动*/
				}
			}
		}
	} /*end of for 1 */
}/*end setweight()*/


/*检查(i,j)是否在棋盘内*/
int check(int i,int j) 
{
	if(i<0||i>=8||j<0||j>=8)
		return 0;
	return 1;
}


/*将各点的8个方向按该方向下的目标点的权值递增排列*/

void setmap()
{
	int i,j,k,m,d1,d2,x1,x2,y1,y2,l1,l2;
	for(i=0;i<N;i++)/*for 1*/
	{
		for(j=0;j<N;j++)/*for 2*/
		{
			for(k=0;k<8;k++)
				map[i][j][k]=k;/*默认8个方向顺时针赋值*/
			for(k=0;k<8;k++)			/*选择排序 for 3 与 for 4 两个循环 对方向索引按 点的权值升序排列，不能到达的方向排在最后*/
			{         
				for(m=k+1;m<8;m++) /*for 4*/
				{
					d1=map[i][j][k];
					x1=i+HTry[d1].x;
					y1=j+HTry[d1].y;

					d2=map[i][j][m];
					x2=i+HTry[d2].x;
					y2=j+HTry[d2].y;

					l1=check(x1,y1);
					l2=check(x2,y2);
					if((l1==0&&l2)||(l1&&l2&&(weight[x1][y1]>weight[x2][y2])))
					{
						map[i][j][k]=d2;
						map[i][j][m]=d1;     /*交换两个方向值,按权值递增排列,不可到达的目标点(超出棋盘)的方向放在最后面*/
					}
					/*end if*/
				}
				/*end for 4*/
			}
			/*end for 3*/
		}
		/*end for 2*/
	}
	/*end for 1*/
}/*end setmap()*/



/*输出函数*/
void output(SqStack &a)   
{   SqStack b;
int c[8][8]={0},j,k=N*N,l=1,x,y;
InitStack (&b);
SElemType e;
while(!StackEmpty(a))
{
	Pop(&a,&e);
	c[e.x][e.y]=k;
	k--;
	Push(&b,e);
}
GetTop(b,&e);
x=e.x;y=e.y;
printf("起始坐标:(%d,%d)\n",x,y);
while(!StackEmpty(b))
{   Pop(&b,&e);
printf("(%d,%d)",e.x,e.y);
Push(&a,e);
}
printf("棋盘表示:       0   1   2   3   4   5   6   7\n");
printf("              ┌─┬─┬─┬─┬─┬─┬─┬─┐\n");
printf("             0");        
for(j=0;j<=7;j++)
{if(c[0][j]<10) printf("│ %d",c[0][j]);else
printf("│%d",c[0][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             1");
for(j=0;j<=7;j++)
{   if(c[1][j]<10) printf("│ %d",c[1][j]);else
printf("│%d",c[1][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             2");
for(j=0;j<=7;j++)
{   if(c[2][j]<10) printf("│ %d",c[2][j]);else
printf("│%d",c[2][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             3");
for(j=0;j<=7;j++)
{   if(c[3][j]<10) printf("│ %d",c[3][j]);else
printf("│%d",c[3][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             4");
for(j=0;j<=7;j++)
{   if(c[4][j]<10) printf("│ %d",c[4][j]);else
printf("│%d",c[4][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             5");
for(j=0;j<=7;j++)
{   if(c[5][j]<10) printf("│ %d",c[5][j]);else
printf("│%d",c[5][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             6");        
for(j=0;j<=7;j++)
{if(c[6][j]<10) printf("│ %d",c[6][j]);else
printf("│%d",c[6][j]);}printf("│\n");
printf("              ");
printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n");
printf("             7");   

for(j=0;j<=7;j++)
{if(c[7][j]<10) printf("│ %d",c[7][j]);else
printf("│%d",c[7][j]);}printf("│\n");
printf("              "); 
printf("└─┴─┴─┴─┴─┴─┴─┴─┘\n");

}
/*踏遍棋盘算法*/
void Path(int xx, int yy)
{
    int c[N*N]={0},h[N*N]={0};
	SqStack a;
	SElemType ptemp;           
	SElemType pop_temp,get_temp; 
	SElemType p,dest_p;    /*当前点和目标点*/           
	int step=0,x,y,s,k=1,l=1,d =0;   
	char ch;
	p.x = xx; p.y = yy;p.z = 0;/*初始化出发点*/ 
	board[xx][yy]=1;
	InitStack(&a);
	Push(&a,p); /*起始点的坐标和首选方向入栈*/
	while(1)
	{
		if (step==(N*N-1)) 
		{            
			output(a);
			printf("退出/返回/下一条路径?q/b/n\n");
			printf("第%d条路径",k);
		    ch=getch();
			if(ch=='b') {CLS;main();}
			else
				if(ch=='q') exit(1);
				else       /*寻找下一条路径*/
				{  
					k++;/*路径数加1*/
					Pop(&a,&pop_temp);   /*退栈*/
					GetTop(a,&get_temp); /*取当前栈顶元素*/
					SetTop(a,&ptemp);   /*更改方向*/
					step--; 
					continue;
				}
		}                  
		if(StackEmpty(a)) break;
	    GetTop(a,&p);
	    x=p.x;   y=p.y; d=p.z;
	    
		if(d>=8)/*该点所有方向已走完，退栈*/
		{
			board[x][y]=0;       /*抹去痕迹*/
		    step--;              /*步数减一*/
		    Pop(&a,&pop_temp);   /*退栈*/
		    GetTop(a,&get_temp); /*取当前栈顶元素*/
		    SetTop(a,&get_temp);   /*更改方向*/
		} /*end if (d>=8)*/
		
		if(d<8)/*方向未走完*/
		{
		    s=map[x][y][d];/*map[x][y][0]未必是(x,y)点的HTry[0]方向,
	                    而是到该点可到的权值最小的点的方向即HTry[map[x][y][0]*/
	        dest_p.x=x+HTry[s].x;
			dest_p.y=y+HTry[s].y;
	        if(check(dest_p.x,dest_p.y)&&board[dest_p.x][dest_p.y]==0)
		             /*目标点在棋盘内且未被走过,则将目标点入栈同时标记当前点为已走过*/
			{    
			     h[step]=step;
                 board[x][y]=1;step++;/*步数加一*/
                 dest_p.z=0;Push(&a,dest_p);/*存入目标点,方向栈初始*/
			}
	       else/*目标点已被走过或目标点不在棋盘内,换方向*/
                SetTop(a,&p);/*切换方向*/			   
		} /*enf if(d<8)*/
	} /*end while(1)*/ 
}
