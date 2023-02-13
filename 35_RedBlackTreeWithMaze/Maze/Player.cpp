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

	// �������� �����ϱ� ������ ����ؼ� ����Ǿ�� �մϴ�.
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
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ���մϴ�.
		INT32 newDir = (dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))	// ������ ĭ�� �˻��մϴ�.
		{
			// ������ �������� 90�� ȸ���մϴ�.
			dir = newDir;

			// ������ �����մϴ�.
			pos += front[dir];
			path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ���մϴ�.
		else if (CanGo(pos + front[dir])) // �� ĭ�� �˻��մϴ�.
		{
			// ������ �����մϴ�.
			pos += front[dir];
			path.push_back(pos);
		}
		else
		{
			// ���� �������� 90�� ȸ���մϴ�.
			dir = (dir + 1) % DIR_COUNT;
		}//if(CanGo)

	}//while(start != dest)


	/*
	* ������ ����ؼ� ��� Ž���� ��� ��θ� Ž��������, ����� �ߺ��� ��θ� ������ŵ�ϴ�.
	*/
	stack<Pos> s;

	// ���� ��θ� Ž���ϱ� ���� �������� ������ �������� �˻��մϴ�.
	for (int i = 0; i < path.size() - 1; i++)
	{
		// ��θ� ���ÿ� �߰��ϴ� ����, �̹� �߰��� ��ζ�� ���ƿ��� ��� �Ǵ��ϰ�
		// ������ �߰��� ���� �������ϴ�. (���ٸ� ���� 1�� �߰��ǰ� ���ư��� ���� 2�� �߰��˴ϴ�.)
		if (s.empty() == false && s.top() == path[i + 1])
			s.pop();	// ���ƿԴ� ���� �����մϴ�.
		else
			s.push(path[i]);
	}

	if (path.empty() == false)
		s.push(path.back());	// ���ܵ� �������� �߰��մϴ�.

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

	// �������� �����ϱ� ������ ����ؼ� ����Ǿ�� �մϴ�.
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0 }, // UP
		Pos {  0,-1 }, // LEFT
		Pos {  1, 0 }, // DOWN
		Pos {  0, 1 }, // RIGHT
	};

	const INT32 size = board->GetSize();
	// �߰��� ����(ť�� �־��� ���� �ִ���) �����մϴ�.
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// parent[A] = B; -> A�� B�� ���� �߰���
	map<Pos, Pos> parent;

	// queue�� [y][x] ��ǥ�� �����մϴ�.
	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) // �湮�� ��ġ�� �������̸� �����մϴ�.
			break;

		for (INT32 dir = 0; dir < 4; dir++)
		{
			// �� �������� �� �� �ִ��� Ȯ���մϴ�.
			Pos nextPos = pos + front[dir];
			if (CanGo(nextPos) == false)
				continue;

			// �̹� queue�� �־��� ���̸� �����մϴ�.
			if (discovered[nextPos.y][nextPos.x])
				continue;

			// BFS ���·� �� �� �ִ� ���� queue�� �ֽ��ϴ�.
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}
	path.clear();

	pos = dest; // ���������� �����մϴ�.

	while (true)
	{
		path.push_back(pos);

		// �ڽ��� ��ġ�� �θ� ��ġ�� ���ٸ� �������Դϴ�.
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
}

// �켱���� ť���� ���� ���
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
	// ���� �ű��
	// F = G + H
	// F : ���� ���� (���� ���� �����ϴ�. ��ο� ���� �޶����ϴ�.)
	// G : ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ����Դϴ�. (��ο� ���� �޶����ϴ�)
	// H : ���������� �󸶳� ������� ǥ���˴ϴ�. (������ �Դϴ�)

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

	// �̵� ���
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
	// closed[y][x] : (y,x)�� �湮�ߴ��� ���θ� �����մϴ�.
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	
	// best[y][x] : ���ݱ��� �߰��� (y,x)�� ���� ���� ���� ����� �����մϴ�.
	// �� ���� ����� �߰��ϰ� �Ǹ� ��ȯ�� ���Դϴ�.
	vector<vector<INT32>> best(size, vector<INT32>(size, INT32_MAX));

	// �θ� ���� �뵵
	map<Pos, Pos> parent;

	////////////////
	// OpenList   //
	////////////////
	// ���ݱ��� �߰ߵ� ����Ʈ�� �����ϴ� List �Դϴ�.
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;


	/////////////////////////////////////////////////////////////////////////////////
	// 1) ����(�߰�) �ý����� �����մϴ�.
	// - ������ �湮 �Ҷ����� ������ ���ο� ������ ���� ����� ����Ͽ� �����մϴ�.
	//
	// 2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� ��� ���� ó���� �ؾ��մϴ�.
	// - OpenList ���� ã�Ƽ� �����մϴ�.
	// - Priority Queue �� ����մϴ�.
	/////////////////////////////////////////////////////////////////////////////////

	// �ʱⰪ
	{
		INT32 g = 0;
		INT32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); // ���������� �Ÿ��� �뷫������ ����մϴ�.
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã���ϴ�.
		PQNode node = pq.top();
		pq.pop();


		// ������ ��ǥ�� ���� ��η� ã�Ƽ�
		// �� ���� ��η� ���� �̹� �湮(closed)�� ��� �Ѿ�ϴ�.
		if (closed[node.pos.y][node.pos.x])	// �켱���� ť�� ���� �ش� ��ǥ�� ���ϴ� ���� ���� ��η� �̹� �� �ֱ� ������ closed �� ����� �� �ֽ��ϴ�.
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// �湮
		closed[node.pos.y][node.pos.x] = true;

		// �������� �����ߴٸ� �����մϴ�
		if (node.pos == dest)
			break;

		for (INT32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			
			// �� �� �ִ��� Ȯ���մϴ�.
			if (CanGo(nextPos) == false)
				continue;
			// �̹� �湮�� ���̸� �Ѿ�ϴ�. (�ǵ��ư��� �ʴ� ���)
			if (closed[nextPos.y][nextPos.x])
				continue;

			// ��� ���
			INT32 g = node.g + cost[dir];
			INT32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			
			// �ٸ� ��ο��� �� ���� ���� ã������ �Ѿ�ϴ�.
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// �����մϴ�.
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}
	path.clear();
	pathIndex = 0;

	pos = dest; // ���������� �����մϴ�.

	while (true)
	{
		path.push_back(pos);

		// �ڽ��� ��ġ�� �θ� ��ġ�� ���ٸ� �������Դϴ�.
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
}
