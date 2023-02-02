#pragma once
#include <stdio.h>
#include <vector>
using namespace std;

// DFS (Depth First Search) 깊이 우선 탐색
// BFS (Breadth First Search) 너비 우선 탐색

struct Vertex
{
};

vector<Vertex> vertices;	  // 정점 목록
vector<vector<int>> adjacent; // 인접 목록
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// 각 정점에 대한 인접 리스트
	//adjacent[0].push_back(1);
	//adjacent[0].push_back(3);
	//adjacent[1].push_back(0);
	//adjacent[1].push_back(2);
	//adjacent[1].push_back(3);
	//adjacent[3].push_back(4);
	//adjacent[5].push_back(4);

	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0},
		{ 1, 0, 1, 1, 0, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0},
	};
}

void DFS(int here)
{
	// 방문한 노드에 체크합니다. (다시 방문하지 않게 예방합니다)
	visited[here] = true;
	printf("Visited : %d\n", here);

	// 인접 리스트 version
	// 현재 정점의 인접 정점을 순회합니다.
	//for (int i = 0; i < adjacent[here].size(); i++)
	//{
	//	// 현재 노드의 인접 리스트를 가져옵니다.
	//	int there = adjacent[here][i];
	//	// 방문하지 않은 인접 정점인 경우 '재귀 호출'을 실행합니다.
	//	if (visited[there] == false)
	//		DFS(there);
	//}

	// 인접 행렬 version
	// 현재 정점과 모든 정점의 연결성을 순회 확인합니다.
	for (int there = 0; there < 6; there++)
	{
		if (adjacent[here][there] == 0) // 갈 수 있는 인접 정점을 확인합니다.
			continue;

		// 아직 방문하지 않은 곳이 있으면 방문한다
		if (visited[there] == false)
			DFS(there);
	}
}

// 모든 정점에 대해 DFS를 수행합니다.
void DFSAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
			DFS(i);
}


void CreateGraph_1()
{
	struct Vertex
	{
		// 다른 Vertex를 가리키는 간선
		vector<Vertex*> edges;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0번 -> 3번 정점이 연결되어 있는지 확인합니다.
	bool connected = false;
	for (Vertex* edge : v[0].edges) // 0번에 있는 간선들을 돌면서
	{
		if (edge == &v[3])	// 3번 Vertex를 가지고 있는지 확인합니다.
		{
			connected = true;
			break;
		}
	}
}

void CreateGraph_2()
{
	struct Vertex
	{
		// 간선을 따로 관리하기 위해 간선을 제거합니다.
	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리합니다.
	// (adjacent[n] -> n번째 정점과 연결된 정점 목록)
	// (정점끼리의 연결과 해제를 반복하기에는 배열로 관리하기 어렵습니다.)
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };


	// 0번 -> 3번 정점이 연결되어 있는지 확인합니다.
	bool connected = false;
	for (int vertex : adjacent[0])	// 0번에 연결되어 있는 Vertex들을 돌면서
	{
		if (vertex == 3)
		{
			connected = true;	// 3번 Vertex를 가지고 있는지 확인합니다.
			break;
		}
	}

	// STL
	vector<int>& adj = adjacent[0];
	bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());
}


void CreateGraph_3()
{
	struct Vertex
	{
		// 간선을 따로 관리하기 위해 간선을 제거합니다.
	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리하는 것으로 연결과 해제를 관리할 수 있습니다.
	// 다만, Vertex가 많아지면 많아질수록 메모리 사용량이 많아집니다.
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// 읽는 방법 : adjacent[from][to]
	// 행렬을 이용한 그래프 표현 (2차원 배열)
	// 메모리 소모가 심하지만, 빠른 접근이 가능합니다.
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// 0번 -> 3번 정점이 연결되어 있는지 확인합니다.
	bool connected = adjacent[0][3];

	// 간선을 true, false가 아니라 가중치로 표현할수도 있습니다. (-1은 연결 안됨을 표현합니다.)
	vector<vector<int>> adjacent2 =
	{
		vector<int> { -1, 15, -1, 35, -1, -1 },
		vector<int> { 15, -1, +5, 10, -1, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
	};
}
