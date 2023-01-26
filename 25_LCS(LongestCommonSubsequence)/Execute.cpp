#include <stdio.h>
#include <string.h>

// 2차원 배열 포인터를 다루기 위한 구조체
struct Table
{
    int** Data;
};

/// <param name="x">행 문자열</param>
/// <param name="y">열 문자열</param>
/// <param name="i">행 길이</param>
/// <param name="j">열 길이</param>
int LCS(const char* x, const char* y, int i, int j, Table* table)
{
    if (i == 0 || j == 0)
    {
        table->Data[i][j] = 0;
    }
    else if(x[i-1] == y[j-1])
    {
        table->Data[i][j] = LCS(x, y, i - 1, j - 1, table) + 1;
    }
    else
    {
        int a = LCS(x, y, i - 1, j, table);
        int b = LCS(x, y, i, j - 1, table);

        if (a > b)
            table->Data[i][j] = a;
        else
            table->Data[i][j] = b;
    }

    return table->Data[i][j];
}

int main()
{
    const char* a = "GOOD MORNING.";
    const char* b = "GUTEN MORGEN.";

    int lengthA = strlen(a);
    int lengthB = strlen(b);

    Table table;
    table.Data = new int* [lengthA + 1];

    for (int i = 0; i < lengthA + 1; i++)
    {
        table.Data[i] = new int[lengthB + 1];
        memset(table.Data[i], 0, sizeof(int) * (lengthB + 1));
    }

    int result = LCS(a, b, lengthA, lengthB, &table);

    printf("\n%-04s", " ");

    for (int i = 0; i <= lengthA; i++)
        printf("%c ", b[i]);
    printf("\n ");

    for (int i = 0; i <= lengthA; i++)
    {
        printf("%c ", a[i - 1]);

        for (int j = 0; j <= lengthB; j++)
            printf("%d ", table.Data[i][j]);
        
        printf("\n");
    }

    printf("%d", result);

    return 0;
}