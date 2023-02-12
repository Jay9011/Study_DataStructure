#include "pch.h"
#include "Player.h"
#include "Board.h"

#include <stack>

void Player::Init(Board* board)
{
	this->pos = board->GetEnterPos();
	this->board = board;

	AStar();
}

void Player::Update(UINT64 deltaTick)
{
	if (pathIndex >= path.size())
	{
		this->board->GenerateMap();
		Init(this->board);
		return;
	}

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

	}//while(start != dest)


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

// 우선순위 큐에서 사용될 노드
struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	INT32 f; // f = g + h
	INT32 g;
	Pos pos;
};

void Player::AStar()
{
	// 점수 매기기
	// F = G + H
	// F : 최종 점수 (작을 수록 좋습니다. 경로에 따라 달라집니다.)
	// G : 시작점에서 해당 좌표까지 이동하는데 드는 비용입니다. (경로에 따라 달라집니다)
	// H : 목적지에서 얼마나 가까운지 표현됩니다. (고정값 입니다)

	Pos start = this->pos;
	Pos dest = board->GetExitPos();

	enum
	{
		DIR_COUNT = 8
	};

	Pos front[] =
	{
		Pos { -1, 0 }, // UP
		Pos {  0,-1 }, // LEFT
		Pos {  1, 0 }, // DOWN
		Pos {  0, 1 }, // RIGHT
		Pos { -1,-1 }, // UP_LEFT
		Pos {  1,-1 }, // DWON_LEFT
		Pos {  1, 1 }, // DOWN_RIGHT
		Pos { -1, 1 }  // UP_RIGHT
	};

	// 이동 비용
	INT32 cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14, // UP_LEFT
		14, // DWON_LEFT
		14, // DOWN_RIGHT
		14  // UP_RIGHT
	};

	const INT32 size = board->GetSize();

	////////////////
	// ClosedList //
	////////////////
	// closed[y][x] : (y,x)에 방문했는지 여부를 저장합니다.
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	
	// best[y][x] : 지금까지 발견한 (y,x)에 대한 가장 좋은 비용을 저장합니다.
	// 더 좋은 비용을 발견하게 되면 교환할 것입니다.
	vector<vector<INT32>> best(size, vector<INT32>(size, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	////////////////
	// OpenList   //
	////////////////
	// 지금까지 발견된 리스트를 관리하는 List 입니다.
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;


	/////////////////////////////////////////////////////////////////////////////////
	// 1) 예약(발견) 시스템을 구현합니다.
	// - 정점을 방문 할때마다 인접한 새로운 정점에 대한 비용을 계산하여 예약합니다.
	//
	// 2) 뒤늦게 더 좋은 경로가 발견된 경우 예외 처리를 해야합니다.
	// - OpenList 에서 찾아서 제거합니다.
	// - Priority Queue 를 사용합니다.
	/////////////////////////////////////////////////////////////////////////////////

	// 초기값
	{
		INT32 g = 0;
		INT32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); // 목적지와의 거리를 대략적으로 계산합니다.
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾습니다.
		PQNode node = pq.top();
		pq.pop();


		// 동일한 좌표를 여러 경로로 찾아서
		// 더 빠른 경로로 인해 이미 방문(closed)된 경우 넘어갑니다.
		if (closed[node.pos.y][node.pos.x])	// 우선순위 큐에 의해 해당 좌표로 향하는 제일 빠른 경로로 이미 들어가 있기 때문에 closed 를 사용할 수 있습니다.
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했다면 종료합니다
		if (node.pos == dest)
			break;

		for (INT32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			
			// 갈 수 있는지 확인합니다.
			if (CanGo(nextPos) == false)
				continue;
			// 이미 방문한 곳이면 넘어갑니다. (되돌아가지 않는 경우)
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			INT32 g = node.g + cost[dir];
			INT32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			
			// 다른 경로에서 더 빠른 길을 찾았으면 넘어갑니다.
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약합니다.
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}
	path.clear();
	pathIndex = 0;

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
