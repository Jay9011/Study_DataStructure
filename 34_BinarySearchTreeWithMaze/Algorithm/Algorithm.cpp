#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

#include "BinarySearchTree.h"

using namespace std;


/*
* 이진 탐색 (Binary Search)
* 
* 정렬되어 있는 배열에서 매 탐색시 절반씩 나누어 탐색하는 방법.
*/
vector<int> numbers;

void BinarySearch(int n)
{
    int left = 0;
    int right = static_cast<int>(numbers.size()) - 1;

    while (left <= right)
    {
        cout << "탐색 범위 : " << left << " ~ " << right << endl;
        int mid = (left + right) / 2;

        if (n < numbers[mid])
        {
            cout << n << " < " << numbers[mid] << endl;
            right = mid - 1;
        }
        else if (n > numbers[mid])
        {
            cout << n << " > " << numbers[mid] << endl;
            left = mid + 1;
        }
        else
        {
            cout << "Find!" << endl;
            break;
        }
    }
}

int main()
{
    //numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81, 91 };
    //BinarySearch(81);

    //cout << endl;

    BinarySearchTree bst;

    bst.Insert(20);
    bst.Insert(10);
    bst.Insert(30);
    bst.Insert(25);
    bst.Insert(26);
    bst.Insert(40);
    bst.Insert(50);

    bst.Delete(20);
    bst.Delete(26);

    bst.Print();
}