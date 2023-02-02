#pragma once
#include <stdio.h>
#include <vector>
using namespace std;

// DFS (Depth First Search) ���� �켱 Ž��
// BFS (Breadth First Search) �ʺ� �켱 Ž��

struct Vertex
{
};

vector<Vertex> vertices;	  // ���� ���
vector<vector<int>> adjacent; // ���� ���
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// �� ������ ���� ���� ����Ʈ
	//adjacent[0].push_back(1);
	//adjacent[0].push_back(3);
	//adjacent[1].push_back(0);
	//adjacent[1].push_back(2);
	//adjacent[1].push_back(3);
	//adjacent[3].push_back(4);
	//adjacent[5].push_back(4);

	// ���� ���
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
	// �湮�� ��忡 üũ�մϴ�. (�ٽ� �湮���� �ʰ� �����մϴ�)
	visited[here] = true;
	printf("Visited : %d\n", here);

	// ���� ����Ʈ version
	// ���� ������ ���� ������ ��ȸ�մϴ�.
	//for (int i = 0; i < adjacent[here].size(); i++)
	//{
	//	// ���� ����� ���� ����Ʈ�� �����ɴϴ�.
	//	int there = adjacent[here][i];
	//	// �湮���� ���� ���� ������ ��� '��� ȣ��'�� �����մϴ�.
	//	if (visited[there] == false)
	//		DFS(there);
	//}

	// ���� ��� version
	// ���� ������ ��� ������ ���Ἲ�� ��ȸ Ȯ���մϴ�.
	for (int there = 0; there < 6; there++)
	{
		if (adjacent[here][there] == 0) // �� �� �ִ� ���� ������ Ȯ���մϴ�.
			continue;

		// ���� �湮���� ���� ���� ������ �湮�Ѵ�
		if (visited[there] == false)
			DFS(there);
	}
}

// ��� ������ ���� DFS�� �����մϴ�.
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
		// �ٸ� Vertex�� ����Ű�� ����
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

	// 0�� -> 3�� ������ ����Ǿ� �ִ��� Ȯ���մϴ�.
	bool connected = false;
	for (Vertex* edge : v[0].edges) // 0���� �ִ� �������� ���鼭
	{
		if (edge == &v[3])	// 3�� Vertex�� ������ �ִ��� Ȯ���մϴ�.
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
		// ������ ���� �����ϱ� ���� ������ �����մϴ�.
	};

	vector<Vertex> v;
	v.resize(6);

	// ����� ����� ���� �����մϴ�.
	// (adjacent[n] -> n��° ������ ����� ���� ���)
	// (���������� ����� ������ �ݺ��ϱ⿡�� �迭�� �����ϱ� ��ƽ��ϴ�.)
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };


	// 0�� -> 3�� ������ ����Ǿ� �ִ��� Ȯ���մϴ�.
	bool connected = false;
	for (int vertex : adjacent[0])	// 0���� ����Ǿ� �ִ� Vertex���� ���鼭
	{
		if (vertex == 3)
		{
			connected = true;	// 3�� Vertex�� ������ �ִ��� Ȯ���մϴ�.
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
		// ������ ���� �����ϱ� ���� ������ �����մϴ�.
	};

	vector<Vertex> v;
	v.resize(6);

	// ����� ����� ���� �����ϴ� ������ ����� ������ ������ �� �ֽ��ϴ�.
	// �ٸ�, Vertex�� �������� ���������� �޸� ��뷮�� �������ϴ�.
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// �д� ��� : adjacent[from][to]
	// ����� �̿��� �׷��� ǥ�� (2���� �迭)
	// �޸� �Ҹ� ��������, ���� ������ �����մϴ�.
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// 0�� -> 3�� ������ ����Ǿ� �ִ��� Ȯ���մϴ�.
	bool connected = adjacent[0][3];

	// ������ true, false�� �ƴ϶� ����ġ�� ǥ���Ҽ��� �ֽ��ϴ�. (-1�� ���� �ȵ��� ǥ���մϴ�.)
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
