#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	this->pos = board->GetEnterPos();
	this->board = board;
}

void Player::Update(UINT64 deltaTick)
{

}