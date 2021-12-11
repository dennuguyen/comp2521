#include <stdio.h>

int hash(int k)
{
    return k % 13;
}

void insert(int *table, int num)
{
    int pos = hash(num);
    for (int i = 0; 1; i++)
        if (table[(pos + 1 * i) % 13] == 0)
        {
            table[(pos + 1 * i) % 13] = num;
            return;
        }
}

int main(void)
{
    int input[8] = { 13, 2, 5, 18, 15, 6, 20, 26 };
    int table[13];
    for (int i = 0; i < 13; i++)
        table[i] = 0;

    int num;
    for (int i = 0; i < 8; i++)
    {
        num = input[i];
        insert(table, num);
        printf("[");
        for (int i = 0; i < 13; i++)
        {
            printf("%d, ", table[i]);
        }
        printf("]\n");
    }

    return 0;
}