#include <stdio.h>
#include <Windows.h>

struct Data
{
    UINT Index;
    UINT Score;
};

void ReadData(Data* data)
{
    FILE* file;
    fopen_s(&file, "Data.txt", "r");
    {
        for (UINT i = 0; i < USHRT_MAX; i++)
            fscanf_s(file, "%d, %d", &data[i].Index, &data[i].Score);
    }
    fclose(file);
}

Data* SequenceSearch(Data* datas, UINT size, UINT target, OUT UINT* count)
{
    *count = 0;
    Data* result = nullptr;

    for (UINT i = 0; i < USHRT_MAX; i++)
    {
        if (target == datas[i].Index)
        {
            *count = i;
            result = &datas[i];

            break;
        }
    }

    return result;
}

Data* BinarySearch(Data* datas, UINT size, UINT target, OUT UINT* count)
{
    *count = 0;

    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (datas[middle].Index == target)
        {
            return &datas[middle];
        }
        else if (target > datas[middle].Index)
        {
            left = middle + 1;
        }
        else if (target < datas[middle].Index)
        {
            right = middle - 1;
        }

        *count = (*count) + 1;
    }

    return nullptr;
}

int BinaryCompare(const void* val1, const void* val2)
{
    Data* data1 = (Data*)val1;
    Data* data2 = (Data*)val2;
    
    if (data1->Index > data2->Index)
        return 1;
    else if (data1->Index < data2->Index)
        return -1;
    else
        return 0;
}

int main()
{
    Data data[USHRT_MAX];
    ReadData(data);

    //for (int i = 0; i < USHRT_MAX; i++)
    //    printf("%d, %d\n", data[i].Index, data[i].Score);

    UINT count = 0;
    UINT target = 60000;

    /*
    * SequenceSearch
    */
    {
        Data* result = SequenceSearch(data, USHRT_MAX, target, &count);
    }
    printf("순차 탐색 %d번 만에 찾음\n", count);

    /*
    * BinarySearch
    */
    {
        Data* result = BinarySearch(data, USHRT_MAX, target, &count);
    }
    printf("이진 탐색 %d번 만에 찾음\n", count);

    /*
    * STL BinarySearch
    */
    {
        bsearch((void*)&target, (void*)data, USHRT_MAX, sizeof(Data), BinaryCompare);
    }
    printf("이진 탐색 %d번 만에 찾음\n", count);

    return 0;
}