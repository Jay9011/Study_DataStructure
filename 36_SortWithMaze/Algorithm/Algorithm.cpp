#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>

#include "Sort.h"

using namespace std;


int main()
{
	vector<int> v{1, 5, 3, 4, 2};

	BubbleSort(v);
	SelectionSort(v);
	InsertionSort(v);

	for (const int num : v)
	{
		cout << num << " ";
	}
}