#pragma once
#include <list>
#include <vector>
using namespace std;

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 행렬

void CreateGraph()
{
    // 인접 행렬 그래프 생성
    vertices.resize(6);
    adjacent = vector<vector<int>>(6, vector<int>(6, -1)); // 연결되지 않은 Vertex는 -1로 표현합니다.

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

	list<VertexCost> discovered; // 발견 목록

	// 각 정점별로 지금까지 발견한 최소 거리와 이전 정점을 기록합니다.
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	// 초기화
	discovered.push_back(VertexCost{ here, 0 }); // 0번에서 시작
	best[here] = 0;
	parent[here] = here;


	while (discovered.empty() == false)
	{
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		// 저장되어 있는 발견 목록에서 가장 비용이 적은 녀석을 선택합니다.
		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		// 현재 살펴본 후보 목록 중 제일 좋은 후보를 가지고 옵니다.
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 현재 후보로 가져온 비용보다 이전에 저장되어있던 비용이 더 적다면
		// 새로 계산 할 필요가 없으므로 경로 계산을 생략합니다.
		if (best[here] < cost)
			continue;

		/*
		* 이전에 저장된 기록보다 짧은 경로를 찾았으므로
		* 찾은 최단 거리에 대한 다음 정점으로 가는 새로운 기록을 저장합니다.
		*/
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == -1) // 연결되지 않았으면 스킵
				continue;

			// 경로 비용을 계산(현재 정점까지의 거리 + 다음 there로의 거리)하고
			// there로 향하는 최단 거리가 이전에 저장된 값이 더 적다면 저장하지 않고 넘어갑니다.
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;

			// 다음 경로를 향하는 최소 비용을 discovered에 추가합니다.
			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}