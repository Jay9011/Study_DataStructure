#pragma once
#include "ConsoleHelper.h"

class Player;

constexpr INT32	BOARD_MAX_SIZE = 100;

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Board
{
public:
	Board();
	~Board();

	void Init(INT32 size, Player* player);
	void Render();

	void GenerateMap();
	TileType GetTileType(Pos pos);
	ConsoleColor GetTileColor(Pos pos);

	Pos GetEnterPos() { return Pos{ 1, 1 }; }
	Pos GetExitPos()  { return Pos{ size - 2, size - 2 }; }

	INT32 GetSize() { return size; }
private:
	TileType tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	INT32 size = 0;
	Player* player = nullptr;
};

