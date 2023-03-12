#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "��";

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

// Prim's �̷� ���� �˰���
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

	// edges[u] : u ������ ����� ���� ���
	map<Pos, vector<CostEdge>> edges;

	// edges �ĺ��� �������� ����մϴ�.
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// �������� �����ϴ� ���� �ĺ�
			if (x < size - 2)
			{
				const INT32 randValue = ::rand() % 100;
				Pos u = Pos{ y, x };
				Pos v = Pos{ y, x + 2 };

				// ���� ������ ������ ����-����մϴ�.
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}

			// �Ʒ��� �����ϴ� ���� �ĺ�
			if (y < size - 2)
			{
				const INT32 randValue = ::rand() % 100;
				Pos u = Pos{ y, x };
				Pos v = Pos{ y + 2, x };

				// ���� ������ ������ ����-����մϴ�.
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}
		}
	}

	// �ش� ������ �̹� Ʈ���� ���ԵǾ� �ִ��� Ȯ���ϱ� ���� map �Դϴ�.
	map<Pos, bool> added;
	// ������ ��𿡼����� ����Ǿ����� Ȯ���ϴ� map �Դϴ�.
	map<Pos, Pos> parent;
	// ����� �ִ� Ʈ���� ������ ���� ��, �ش� ������ ��� �ּ� ������ ����
	map<Pos, INT32> best;
	
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			best[Pos{ y, x }] = INT32_MAX;	// ��� �ʱ�ȭ
			added[Pos{ y, x }] = false;
		}
	}

	priority_queue<CostEdge> pq;	// �ּ� ��� Ž���� ���� priority_queue �Դϴ�.

	// ���� ���� �����մϴ�.
	const Pos startPos = Pos{ 1, 1 };
	pq.push(CostEdge{ 0, startPos });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (pq.empty() == false)
	{
		// ������� �߰ߵ� ������ �� �ּ� ��� ������ �����ɴϴ�.
		CostEdge bestEdge = pq.top();
		pq.pop();


		Pos v = bestEdge.vtx;
		
		if (added[v])	// �̹� �߰��� �����̸� �Ѿ�ϴ�.
			continue;

		added[v] = true;
		
		int y = (parent[v].y + v.y) / 2;
		int x = (parent[v].x + v.x) / 2;
		tile[y][x] = TileType::EMPTY;
		

		// ��� �߰��� �����鿡 ����Ǿ� �ִ� �������� �˻��մϴ�.
		for (CostEdge& edge : edges[v])
		{
			// priority_queue �� �̹� �߰��Ǿ��ִ� �����̶�� �Ѿ�ϴ�.
			if (added[edge.vtx])
				continue;

			// �ٸ� ��η� �� ���� �ĺ��� �߰� �Ǿ����� ��ŵ�մϴ�.
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
