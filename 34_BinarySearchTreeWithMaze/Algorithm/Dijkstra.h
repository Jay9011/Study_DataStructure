#pragma once
#include <list>
#include <vector>
using namespace std;

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // ���� ���

void CreateGraph()
{
    // ���� ��� �׷��� ����
    vertices.resize(6);
    adjacent = vector<vector<int>>(6, vector<int>(6, -1)); // ������� ���� Vertex�� -1�� ǥ���մϴ�.

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijkstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered; // �߰� ���

	// �� �������� ���ݱ��� �߰��� �ּ� �Ÿ��� ���� ������ ����մϴ�.
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	// �ʱ�ȭ
	discovered.push_back(VertexCost{ here, 0 }); // 0������ ����
	best[here] = 0;
	parent[here] = here;


	while (discovered.empty() == false)
	{
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		// ����Ǿ� �ִ� �߰� ��Ͽ��� ���� ����� ���� �༮�� �����մϴ�.
		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		// ���� ���캻 �ĺ� ��� �� ���� ���� �ĺ��� ������ �ɴϴ�.
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// ���� �ĺ��� ������ ��뺸�� ������ ����Ǿ��ִ� ����� �� ���ٸ�
		// ���� ��� �� �ʿ䰡 �����Ƿ� ��� ����� �����մϴ�.
		if (best[here] < cost)
			continue;

		/*
		* ������ ����� ��Ϻ��� ª�� ��θ� ã�����Ƿ�
		* ã�� �ִ� �Ÿ��� ���� ���� �������� ���� ���ο� ����� �����մϴ�.
		*/
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == -1) // ������� �ʾ����� ��ŵ
				continue;

			// ��� ����� ���(���� ���������� �Ÿ� + ���� there���� �Ÿ�)�ϰ�
			// there�� ���ϴ� �ִ� �Ÿ��� ������ ����� ���� �� ���ٸ� �������� �ʰ� �Ѿ�ϴ�.
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;

			// ���� ��θ� ���ϴ� �ּ� ����� discovered�� �߰��մϴ�.
			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}