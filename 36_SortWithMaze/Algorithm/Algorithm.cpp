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
	vector<int> v;

	srand(time(0));

	for(int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}

	// BubbleSort(v);
	// SelectionSort(v);
	// InsertionSort(v);
	// HeapSort(v);
	// MergeSort(v, 0, v.size() - 1);
	QuickSort(v, 0, v.size() - 1);


	for (const int num : v)
	{
		cout << num << " ";
	}
}