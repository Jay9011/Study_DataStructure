#include "pch.h"
#include "Player.h"
#include "Board.h"

#include <stack>

void Player::Init(Board* board)
{
	this->pos = board->GetEnterPos();
	this->board = board;

	RightHand();
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

void Player::RightHand()
{
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
		}//if(CanGo)

	}//while(pos != dest)


	/*
	* 스택을 사용해서 경로 탐색시 모든 경로를 탐색했지만, 실행시 중복된 경로를 생략시킵니다.
	*/
	stack<Pos> s;

	// 다음 경로를 탐색하기 위해 목적지를 제외한 나머지만 검사합니다.
	for (int i = 0; i < path.size() - 1; i++)
	{
		// 경로를 스택에 추가하는 도중, 이미 추가된 경로라면 돌아오는 길로 판단하고
		// 이전에 추가한 값을 빼버립니다. (막다른 길을 1번 추가되고 돌아가는 길은 2번 추가됩니다.)
		if (s.empty() == false && s.top() == path[i + 1])
			s.pop();	// 돌아왔던 길을 제거합니다.
		else
			s.push(path[i]);
	}

	if (path.empty() == false)
		s.push(path.back());	// 제외된 목적지를 추가합니다.

	vector<Pos> newPath;
	while (s.empty() == false)
	{
		newPath.push_back(s.top());
		s.pop();
	}

	std::reverse(newPath.begin(), newPath.end());

	path = newPath;
}

void Player::BFS()
{
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

	const INT32 size = board->GetSize();
	// 발견한 여부(큐에 넣었던 적이 있는지) 저장합니다.
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// parent[A] = B; -> A는 B로 인해 발견함
	map<Pos, Pos> parent;

	// queue는 [y][x] 좌표로 저장합니다.
	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) // 방문한 위치가 도착점이면 종료합니다.
			break;

		for (INT32 dir = 0; dir < 4; dir++)
		{
			// 전 방향으로 갈 수 있는지 확인합니다.
			Pos nextPos = pos + front[dir];
			if (CanGo(nextPos) == false)
				continue;

			// 이미 queue에 넣었던 길이면 생략합니다.
			if (discovered[nextPos.y][nextPos.x])
				continue;

			// BFS 형태로 갈 수 있는 길을 queue에 넣습니다.
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}
	path.clear();

	pos = dest; // 도착점부터 시작합니다.

	while (true)
	{
		path.push_back(pos);

		// 자신의 위치와 부모 위치가 같다면 시작점입니다.
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
}
