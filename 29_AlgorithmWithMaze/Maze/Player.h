#pragma once

class Board;

class Player
{
public:
	void Init(Board* board);
	void Update(UINT64 deltaTick);

	void SetPos(Pos pos) { this->pos = pos; }
	Pos  GetPos() { return pos; }


private:
	Pos	pos = {};
	INT32 dir = DIR_UP;
	Board* board = nullptr;
};

