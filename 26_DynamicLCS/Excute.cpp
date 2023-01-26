#include <stdio.h>
#include <string.h>
#include <Windows.h>

// 2���� �迭 �����͸� �ٷ�� ���� ����ü
struct Table
{
    int** Data;
};

/// <param name="x">�� ���ڿ�</param>
/// <param name="y">�� ���ڿ�</param>
/// <param name="i">�� ����</param>
/// <param name="j">�� ����</param>
int LCS(const char* x, const char* y, int i, int j, Table* table)
{
    /*
    * �� �κ��� 0���� �ʱ�ȭ ��ŵ�ϴ�.
    */
    for (int m = 0; m < i; m++)
        table->Data[m][0] = 0;
    
    for (int n = 0; n < j; n++)
        table->Data[0][n] = 0;

    /*
    * �տ��� ���� ���ϴ�.
    */
    for (int m = 1; m <= i; m++)
    {
        for (int n = 1; n <= j; n++)
        {
            // ���ڰ� �ٸ� ��
            if (x[m - 1] != y[n - 1])
            {
                // ���� ����� �״�� ����մϴ�. (ū ���ڸ� ���)
                table->Data[m][n] = max(table->Data[m][n - 1], table->Data[m - 1][n]);
            }
            // ���ڰ� ���� ��
            else
            {
                // �� �� ���ڸ� ������ŵ�ϴ�.
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