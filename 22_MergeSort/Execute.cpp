#include <iostream>
using namespace std;

void Merge(int datas[], int start, int mid, int end)
{
    int left = start;
    int right = mid + 1;

    int destIndex = 0;
    int* dest = new int[(end - start + 1)] {};

    // 한 쪽의 정렬이 끝나면 비교를 종료합니다.
    while (left <= mid && right <= end)
    {
        if (datas[left] < datas[right])
            dest[destIndex++] = datas[left++];
        else
            dest[destIndex++] = datas[right++];
    }

    // 나머지 한 쪽의 남은 요소들을 전부 넣어줍니다.
    while (left <= mid)
        dest[destIndex++] = datas[left++];

    while (right <= end)
        dest[destIndex++] = datas[right++];
    
    // 정렬된 요소들을 원본에 대입합니다.
    destIndex = 0;
    for (int i = start; i <= end; i++)
        datas[i] = dest[destIndex++];

    delete[] dest;
}

void MergeSort(int datas[], int start, int end)
{
    if (end - start < 1)    // 더 이상 나눌 수 없을 때까지 나눈다.
        return;

    int mid = (start + end) / 2;

    MergeSort(datas, start, mid);
    MergeSort(datas, mid + 1, end);

    // Merge(병합) 시작
    Merge(datas, start, mid, end);
}

int main()
{
    int datas[] = { 5, 1, 6, 4, 8, 3, 7, 9, 2 };
    int count = sizeof(datas) / sizeof(datas[0]);

    for (int i = 0; i < count; i++)
        cout << datas[i] << " ";
    cout << endl;

    MergeSort(datas, 0, count - 1);

    for (int i = 0; i < count; i++)
        cout << datas[i] << " ";
    cout << endl;

    return 0;
}