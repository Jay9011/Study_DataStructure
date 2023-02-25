#pragma once
#include <vector>

using namespace std;

inline void BubbleSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());

	// (N-1) + (N-2) + ... + 2 + 1
	// ���������� �� = N * (N-1) / 2
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
 * ���� ����
 * ���� ���� (Divide and Conquer)�� ����մϴ�.
 * - ���� (Divide)	: ������ �� �ܼ��ϰ� �����մϴ�.
 * - ���� (Conquer) : ���ҵ� ������ �ذ��մϴ�.
 * - ���� (Combine) : ����� ������ ������ �մϴ�.
 */
inline void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// [2][3][7][K][4][8][9][J]
	// [l]         [r]
	int leftIdx = left;
	int rightIdx = mid + 1;
	
	vector<int> temp;	// ���ĵ� �迭�� ���� temp �� ����ϴ�.

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

	// �� ���� ���ĵǾ��ٸ� ������ �ʵ� ���ĵǾ� �ִٴ� ���̹Ƿ�
	// ������ ���ĵ� �����͸� �� ���� �ű�ϴ�.
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
	while (low <= high) // �� low �� high �� �����ȴٸ� pivot �������� ���� ������ ���ٴ� ���Դϴ�.
	{
		// low �� pivot ���ʿ� �;� �� �����Ͷ�� �Ѿ�ϴ�.
		while (low <= right && pivot >= v[low])
			low++;

		// high �� pivot �����ʿ� �;� �� �����Ͷ�� �Ѿ�ϴ�.
		while (high >= left + 1 && pivot <= v[high])
			high--;

		// low �� �����, high �� ����ٸ� pivot �������� ������ �ϴ� ������ �̹Ƿ� �����ݴϴ�.
		if (low < high)
			swap(v[low], v[high]);
	}

	// pivot �� pivot �� �ٲ�� �� �����͸� ��ȯ�մϴ�.
	// �̶�, �̹� ���ĵǾ� �ִٸ� ���� ���� ���� ��ȯ�� �̴ϴ�.
	swap(v[left], v[high]);
	return high;
}

// O(N^2) < �־�
// O(NlogN) < ���
inline void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}