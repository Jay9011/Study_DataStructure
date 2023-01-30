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

// Binary Tree �̷� ���� �˰���
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

	// �������� ���� Ȥ�� �Ʒ��� ���� �մ� �۾�
	for (INT32 y = 0; y < size; y++)
	{
		for (INT32 x = 0; x < size; x++)
		{
			// �̹� ���� ��� ����
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// ���� �����̳� ���� �Ʒ����� ���̿��� �ϹǷ� �ٸ� �������� �վ��ݴϴ�.
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

			// �������� �����̳� �Ʒ��� �վ� �ݴϴ�.
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
