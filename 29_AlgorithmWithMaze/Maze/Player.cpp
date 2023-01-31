#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	this->pos = board->GetEnterPos();
	this->board = board;

	Pos pos = this->pos;

	path.clear();
	path.push_back(pos);

	// 목적지에 도착하기 전에는 계속해서 실행되어야 합니다.
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0 }, // UP
		Pos {  0,-1 }, // LEFT
		Pos {  1, 0 }, // DOWN
		Pos {  0, 1 }, // RIGHT
	};

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인합니다.
		INT32 newDir = (dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))	// 오른쪽 칸을 검사합니다.
		{
			// 오른쪽 방향으로 90도 회전합니다.
			dir = newDir;

			// 앞으로 진행합니다.
			pos += front[dir];
			path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인합니다.
		else if (CanGo(pos + front[dir])) // 앞 칸을 검사합니다.
		{
			// 앞으로 진행합니다.
			pos += front[dir];
			path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전합니다.
			dir = (dir + 1) % DIR_COUNT;
			/*
			switch (dir)
			{
			case DIR_UP:
				dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				dir = DIR_UP;
				break;
			}
			*/
		}

	}
}

void Player::Update(UINT64 deltaTick)
{
	if (pathIndex >= path.size())
		return;

	sumTick += deltaTick;
	if (sumTick >= MOVE_TICK)
	{
		sumTick = 0;

		pos = path[pathIndex];
		pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}
