#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
//#include "Linear.h"
//#include "Graph.h"
//#include "Dijkstra.h"
#include "Tree.h"
using namespace std;

int main()
{
#pragma region Linear

	/*
	* Vector
	*/
	//vector<int> v;
	//Vector<int> v;

	//v.reserve(100);
	//cout << v.size() << " " << v.capacity() << endl;

	//for (int i = 0; i < 100; i++)
	//{
	//	v.push_back(i);
	//	cout << v.size() << " " << v.capacity() << endl;
	//}

	////v.resize(10);
	////cout << v.size() << " " << v.capacity() << endl;

	//v.clear();
	//cout << v.size() << " " << v.capacity() << endl;


	/*
	* List
	*/
	//list<int> li;

	//list<int>::iterator eraseIt;
	//List<int> li;

	//List<int>::iterator eraseIt;
	//for (int i = 0; i < 10; i++)
	//{
	//	if (i == 5)
	//	{
	//		eraseIt = li.insert(li.end(), i);
	//	}
	//	else
	//	{
	//		li.push_back(i);
	//	}
	//}

	//li.pop_back();

	//li.erase(eraseIt);

	//for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	//{
	//	cout << (*it) << endl;
	//}


	/*
	* Stack
	*/
	//stack<int> s;
	//Stack<int> s;

	//s.push(1);
	//s.push(2);
	//s.push(3);

	//while (s.empty() == false)
	//{
	//	// 최상위 원소를 가져옵니다. (제거하지 않습니다.)
	//	int data = s.top();
	//	// 최상위 원소를 삭제합니다.
	//	s.pop();

	//	cout << data << endl;
	//}

	//int size = s.size();


	/*
	* Queue
	*/
	//queue<int> q;
	//ArrayQueue<int> q;

	//for (int i = 0; i < 100; i++)
	//	q.push(i);

	//while (q.empty() == false)
	//{
	//	int value = q.front();
	//	q.pop();
	//	cout << value << endl;
	//}

	//int size = q.size();
#pragma endregion
#pragma region Graph
	//CreateGraph();
	//visited = vector<bool>(6, false); // 방문 초기화
	//DFS(0);
	//DFSAll();
	//BFS(0);
#pragma endregion
#pragma region Dijkstra

#pragma endregion
#pragma region Tree
	NodeRef root = CreateTree();
	PrintTree(root, 0);
	cout << "Tree Height : " << GetHeight(root) << endl;
#pragma endregion

}