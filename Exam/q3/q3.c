#include <stdio.h>

#define N 20

void multiply(int a[N][N], int b[N][N], int c[N][N])
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            c[i][j] = 0;
        }
    }
    int count = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
                count += 1;
                printf("count = %d\n", count);
            }
        }
    }
}

int main(void)
{
    int a[N][N] =
    {
        {1, 2, 1},
        {3, 4, 1},
        {4, 6, 7},
    };
    int b[N][N] =
    {
        {1, 2, 1},
        {3, 4, 1},
        {4, 6, 7},
    };
    int c[N][N];
    multiply(a, b, c);

    return 0;
}