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

	}//while(pos != dest)


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
