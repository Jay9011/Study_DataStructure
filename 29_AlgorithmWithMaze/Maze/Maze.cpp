#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	board.Init(25, &player);
	player.Init(&board);

	UINT64 lastTick = 0;
	while (true)
	{
#pragma region ������ ����
		const UINT64 currentTick = GetTickCount64();
		const UINT64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;
#pragma endregion

		// �Է�

		// ����
		player.Update(deltaTick);

		// ������
		board.Render();
	}
}