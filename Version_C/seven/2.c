#include <stdio.h>
//#include <math.h>

int path[100][100];///path[i][j]为0表示i, j两点之间不通，为1表示有一条路
int stack[120], m=1, n, x, y;///存储路径

void dfs(int p)
{
    int i, j;

    for(i=1; i<=100; i++)
    {
        if(path[p][i]==1)
        {
            if(i == y)///如果深搜到了终点，就输出刚才经过的路径
            {
                for(j=0; j<m; j++)
                {
                    printf("%-5d", stack[j]);
                }
                printf("%-5d\n", y);
            }
            else///如果该点不是终点
            {
				printf("m = %d\n", m);
                stack[m] = i;///将该点存起来
                m++;
                dfs(i);///接着深搜
                m--;
            }
        }
    }
}

int main()
{
    int i, j;

    memset(path, 0, sizeof(path));
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        scanf("%d %d", &x, &y);
        path[x][y] = path[y][x] = 1;///这两点之间有路径
    }
    scanf("%d %d", &x, &y);
    stack[0] = x;
    dfs(x);
}
