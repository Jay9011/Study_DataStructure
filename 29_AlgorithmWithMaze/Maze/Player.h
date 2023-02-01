#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 500	// 얼마나 시간이 지나면 움직일지 지정합니다.
	};

public:
	void Init(Board* board);
	void Update(UINT64 deltaTick);

	void SetPos(Pos pos) { this->pos = pos; }
	Pos  GetPos() { return pos; }

	bool CanGo(Pos pos);

private:
	Pos	pos = {};
	INT32 dir = DIR_UP;
	Board* board = nullptr;

	vector<Pos> path;
	UINT32 pathIndex = 0;

	UINT64 sumTick = 0;
};

