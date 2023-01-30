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

// Binary Tree 미로 생성 알고리즘
// - Mazes For Programmers
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

	// 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			// 이미 벽인 경우 생략
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 가장 우측이나 가장 아래쪽은 벽이여야 하므로 다른 방향으로 뚫어줍니다.
			if (y == size - 2 && x == size - 2)
				continue;
			if (y == size - 2)
			{
				tile[y][x + 1] = TileType::EMPTY;
				continue;
			}
			if (x == size - 2)
			{
				tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			// 랜덤으로 우측이나 아래를 뚫어 줍니다.
			const INT32 randValue = rand() % 2;
			if (randValue == 0)
			{
				tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				tile[y + 1][x] = TileType::EMPTY;
			}
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
