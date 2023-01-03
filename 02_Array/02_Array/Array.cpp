#include <stdio.h>
#include <array>
using namespace std;

void main()
{
    int a[3] = { 20, 10, 30 };
    for (int b : a)
    {
        printf("%d\n", b);
    }

    array<int, 3> list;
    for (int b : list)
    {
        printf("%d\n", b);
    }
}