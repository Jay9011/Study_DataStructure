#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(INT32 size, Player* player)
{
	this->size = size;
	this->player = player;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (INT32 y = 0; y < 25; y++)
	{
		for (INT32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y, x });
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}
}

// Prim's 미로 생성 알고리즘
void Board::GenerateMap()
{
	struct CostEdge
	{
		int cost;
		Pos vtx;

		bool operator<(const CostEdge& other) const
		{
			return cost < other.cost;
		}
	};

	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				tile[y][x] = TileType::WALL;
			else
				tile[y][x] = TileType::EMPTY;
		}
	}

	// edges[u] : u 정점과 연결된 간선 목록
	map<Pos, vector<CostEdge>> edges;

	// edges 후보를 랜덤으로 등록합니다.
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측으로 연결하는 간선 후보
			if (x < size - 2)
			{
				const INT32 randValue = ::rand() % 100;
				Pos u = Pos{ y, x };
				Pos v = Pos{ y, x + 2 };

				// 서로 양쪽의 간선을 연결-등록합니다.
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}

			// 아래로 연결하는 간선 후보
			if (y < size - 2)
			{
				const INT32 randValue = ::rand() % 100;
				Pos u = Pos{ y, x };
				Pos v = Pos{ y + 2, x };

				// 서로 양쪽의 간선을 연결-등록합니다.
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}
		}
	}

	// 해당 정점이 이미 트리에 포함되어 있는지 확인하기 위한 map 입니다.
	map<Pos, bool> added;
	// 정점이 어디에서부터 연결되었는지 확인하는 map 입니다.
	map<Pos, Pos> parent;
	// 만들고 있는 트리에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	map<Pos, INT32> best;
	
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			best[Pos{ y, x }] = INT32_MAX;	// 비용 초기화
			added[Pos{ y, x }] = false;
		}
	}

	priority_queue<CostEdge> pq;	// 최소 비용 탐색을 위한 priority_queue 입니다.

	// 시작 점을 지정합니다.
	const Pos startPos = Pos{ 1, 1 };
	pq.push(CostEdge{ 0, startPos });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (pq.empty() == false)
	{
		// 현재까지 발견된 간선들 중 최소 비용 간선을 가져옵니다.
		CostEdge bestEdge = pq.top();
		pq.pop();


		Pos v = bestEdge.vtx;
		
		if (added[v])	// 이미 추가된 정점이면 넘어갑니다.
			continue;

		added[v] = true;
		
		int y = (parent[v].y + v.y) / 2;
		int x = (parent[v].x + v.x) / 2;
		tile[y][x] = TileType::EMPTY;
		

		// 방금 추가한 간선들에 연결되어 있는 간선들을 검사합니다.
		for (CostEdge& edge : edges[v])
		{
			// priority_queue 에 이미 추가되어있는 간선이라면 넘어갑니다.
			if (added[edge.vtx])
				continue;

			// 다른 경로로 더 좋은 후보가 발견 되었으면 스킵합니다.
			if (edge.cost > best[edge.vtx])
				continue;

			best[edge.vtx] = edge.cost;
			parent[edge.vtx] = v;
			pq.push(edge);
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= size)
		return TileType::NONE;

	if (pos.y < 0 || pos.y >= size)
		return TileType::NONE;

	return tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (player && player->GetPos() == pos)
		return ConsoleColor::YELLOW;

	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	case TileType::WALL:
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;
}
