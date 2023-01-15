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
                // 이미 정렬된 서브 배열의 삽입 위치에서부터 정렬 종료 지점까지의 데이터를
                // 삽입할 데이터가 있는 위치만큼(1칸만큼) 이동시킨다.
                memmove(&datas[k + 1], &datas[k], sizeof(datas[0]) * (i - k));
                // 이후 데이터를 삽입 위치에 삽입한다.
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