#include <stdio.h>
#include <memory>

void Sort(int* datas, int length)
{
    for (int i = 1; i < length; i++)
    {
        if (datas[i - 1] <= datas[i])
            continue;

        int value = datas[i];
        for (int k = 0; k < i; k++)
        {
            if (datas[k] > value)
            {
                // �̹� ���ĵ� ���� �迭�� ���� ��ġ�������� ���� ���� ���������� �����͸�
                // ������ �����Ͱ� �ִ� ��ġ��ŭ(1ĭ��ŭ) �̵���Ų��.
                memmove(&datas[k + 1], &datas[k], sizeof(datas[0]) * (i - k));
                // ���� �����͸� ���� ��ġ�� �����Ѵ�.
                datas[k] = value;

                break;
            }
        }//for(findIndex)
    }//for(dataIndex)
}

int main()
{
    int datas[] = { 5, 1, 6, 4, 2, 3 };
    int length = sizeof(datas) / sizeof(datas[0]);
    Sort(datas, length);

    for (int i = 0; i < length; i++)
        printf("%d ", datas[i]);

    printf("\n\n");

    return 0;
}