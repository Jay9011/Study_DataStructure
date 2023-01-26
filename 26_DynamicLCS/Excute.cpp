#include <stdio.h>
#include <string.h>
#include <Windows.h>

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
    /*
    * 앞 부분을 0으로 초기화 시킵니다.
    */
    for (int m = 0; m < i; m++)
        table->Data[m][0] = 0;
    
    for (int n = 0; n < j; n++)
        table->Data[0][n] = 0;

    /*
    * 앞에서 비교해 갑니다.
    */
    for (int m = 1; m <= i; m++)
    {
        for (int n = 1; n <= j; n++)
        {
            // 문자가 다를 때
            if (x[m - 1] != y[n - 1])
            {
                // 이전 결과를 그대로 사용합니다. (큰 숫자를 사용)
                table->Data[m][n] = max(table->Data[m][n - 1], table->Data[m - 1][n]);
            }
            // 문자가 같을 때
            else
            {
                // 앞 쪽 숫자를 증가시킵니다.
                table->Data[m][n] = table->Data[m - 1][n - 1] + 1;
            }
        }
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