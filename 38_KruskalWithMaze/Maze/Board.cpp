#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "DisjointSet.h"
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

// Kruskal's 미로 생성 알고리즘
void Board::GenerateMap()
{
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

	vector<CostEdge> edges;

	// edges 후보를 랜덤 cost로 등록합니다.
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측으로 연결하는 간선 후보를 만듭니다.
			if (x < size - 2)
			{
				const INT32 randValue = rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y, x}, Pos{y, x + 2} });
			}

			// 아래로 연결하는 간선 후보를 만듭니다.
			if (y < size - 2)
			{
				const INT32 randValue = rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y, x}, Pos{y + 2, x} });
			}
		}
	}

	sort(edges.begin(), edges.end());

	DisjointSet sets(size * size);

	for (CostEdge& edge : edges)
	{
		int u = edge.u.y * size + edge.u.x;
		int v = edge.v.y * size + edge.v.x;

		// 같은 그룹이면 Union 을 하지 않습니다. (사이클 방지)
		if (sets.Find(u) == sets.Find(v))
			continue;

		// 두 그룹을 Union 합니다.
		sets.Merge(u, v);
		
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		tile[y][x] = TileType::EMPTY;
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
