#pragma once
#include <vector>

using namespace std;

inline void BubbleSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());

	// (N-1) + (N-2) + ... + 2 + 1
	// 등차수열의 합 = N * (N-1) / 2
	// O(N^2)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < (n - 1 - i); ++j)
		{
			if(v[j] > v[j + 1])
			{
				// Swap
				const int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

inline void SelectionSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());

	// O(N^2)
	for (int i = 0; i < n - 1; ++i)
	{
		int bestIdx = i;

		for (int j = i + 1; j < n; ++j)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		// Swap
		const int temp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = temp;
	}
}

inline void InsertionSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());

	for (int i = 1; i < n; ++i)
	{
		int insertData = v[i];

		int j = 0;
		for (j = i - 1; j >= 0; --j)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}

		v[j + 1] = insertData;
	}
}

inline void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	// O(NlogN)
	for (int num : v)
		pq.push(num);

	v.clear();

	// O(NlogN)
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

/*
 * 병합 정렬
 * 분할 정복 (Divide and Conquer)을 사용합니다.
 * - 분할 (Divide)	: 문제를 더 단순하게 분할합니다.
 * - 정복 (Conquer) : 분할된 문제를 해결합니다.
 * - 결합 (Combine) : 결과를 취합해 마무리 합니다.
 */
inline void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// [2][3][7][K][4][8][9][J]
	// [l]         [r]
	int leftIdx = left;
	int rightIdx = mid + 1;
	
	vector<int> temp;	// 정렬된 배열을 담을 temp 를 만듭니다.

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	// 한 쪽이 정렬되었다면 나머지 쪽도 정렬되어 있다는 뜻이므로
	// 나머지 정렬된 데이터를 한 번에 옮깁니다.
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
}

inline void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;

	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// O(N)
	while (low <= high) // 두 low 와 high 가 교차된다면 pivot 기준으로 값이 나뉘어 졌다는 뜻입니다.
	{
		// low 가 pivot 왼쪽에 와야 할 데이터라면 넘어갑니다.
		while (low <= right && pivot >= v[low])
			low++;

		// high 가 pivot 오른쪽에 와야 할 데이터라면 넘어갑니다.
		while (high >= left + 1 && pivot <= v[high])
			high--;

		// low 가 멈췄고, high 가 멈췄다면 pivot 기준으로 섞여야 하는 데이터 이므로 섞어줍니다.
		if (low < high)
			swap(v[low], v[high]);
	}

	// pivot 과 pivot 과 바꿔야 할 데이터를 교환합니다.
	// 이때, 이미 정렬되어 있다면 서로 같은 값을 교환할 겁니다.
	swap(v[left], v[high]);
	return high;
}

// O(N^2) < 최악
// O(NlogN) < 평균
inline void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}