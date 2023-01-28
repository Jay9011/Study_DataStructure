#include <stdio.h>
#include <string.h>

#define MAX	1024
#define INIT -1

#define START   'S'
#define GOAL    'G'
#define WAY     ' '
#define WALL    '#'
#define MARKED  '+'

enum class Direction
{
    North = 0, South, East, West
};

struct Position
{
    int X, Y;
};

struct MazeDesc
{
    int Columns;
    int Rows;

    char** Data;
};


void ReadMaze(const char* path, MazeDesc* desc)
{
	FILE* fp;
	fopen_s(&fp, path, "r");

	int rows = 0, columns = INIT;
	char buffer[MAX];

	while (fgets(buffer, MAX, fp) != NULL)
	{
		rows++;

		if (columns == INIT)
			columns = (int)strlen(buffer) - 1;
	}

	desc->Rows = rows;
	desc->Columns = columns;
	desc->Data = new char* [rows];

	for (int i = 0; i < rows; i++)
		desc->Data[i] = new char[columns];

	rewind(fp);

	for (int i = 0; i < rows; i++)
	{
		fgets(buffer, MAX, fp);

		for (int j = 0; j < columns; j++)
			desc->Data[i][j] = buffer[j];
	}
	fclose(fp);
}

bool GetNextStep(MazeDesc* desc, Position* curr, Direction direction, Position* next)
{
	switch (direction)
	{
	case Direction::North:
	{
		next->X = curr->X;
		next->Y = curr->Y - 1;

		if (next->Y == -1)
			return false;
	}
	break;

	case Direction::South:
	{
		next->X = curr->X;
		next->Y = curr->Y + 1;

		if (next->Y == desc->Rows)
			return false;
	}
	break;

	case Direction::East:
	{
		next->X = curr->X + 1;
		next->Y = curr->Y;

		if (next->X == desc->Columns)
			return false;
	}
	break;

	case Direction::West:
	{
		next->X = curr->X - 1;
		next->Y = curr->Y;

		if (next->X == -1)
			return false;
	}
	break;
	}

	/*
	* 벽이나 가본 길은 다시 가지 않습니다.
	*/ 
	if (desc->Data[next->Y][next->X] == WALL) return false;
	if (desc->Data[next->Y][next->X] == MARKED) return false;

	return true;
}

bool MoveTo(MazeDesc* desc, Position* curr, Direction direction)
{
	Position next;

	if (desc->Data[curr->Y][curr->X] == GOAL)	// Goal을 찾으면 종료합니다.
		return true;

	// 가본 길은 다시 보지 않도록 Marking 해줍니다.
	desc->Data[curr->Y][curr->X] = MARKED;

	for (int i = 0; i < 4; i++)
	{
		// 모든 방향에 대해서 검사합니다. 갈 수 없다면 i를 증가시킵니다.
		if (GetNextStep(desc, curr, (Direction)i, &next) == false)
			continue;

		// 갈 수 있다면 해당 방향으로 이동하고 북쪽부터 검사를 시작하는 재귀를 호출합니다.
		if (MoveTo(desc, &next, Direction::North) == true)
			return true;
	}

	// Goal을 찾지 못하면 길을 깨끗하게 초기화 시켜줍니다.
	desc->Data[curr->Y][curr->X] = WAY;

	return false;
}

bool Solve(MazeDesc* desc)
{
	bool startFound = false;
	bool result = false;

	/*
	* 출발 지점을 찾습니다.
	*/
	Position start;
	for (int y = 0; y < desc->Rows; y++)
	{
		for (int x = 0; x < desc->Columns; x++)
		{
			if (desc->Data[y][x] == START)
			{
				start.X = x;
				start.Y = y;
				startFound = true;

				break;
			}//if(desc)
		}//for(x)
	}//for(y)
	if (startFound == false)
	{
		printf("출발 지점을 못찾음\n");

		return false;
	}

	/*
	* 출발지점에서 북쪽 방향부터 탐색을 시작합니다.
	*/
	result |= MoveTo(desc, &start, Direction::North);
	result |= MoveTo(desc, &start, Direction::South);
	result |= MoveTo(desc, &start, Direction::East);
	result |= MoveTo(desc, &start, Direction::West);

	
	desc->Data[start.Y][start.X] = START;	// 출발 지점이 지워졌을 수 있으니 사용자에게 보여주기 위해 S를 기록합니다.

	return result;
}

int main()
{
	const char* path = "Maze01.txt";

	MazeDesc desc;
	ReadMaze(path, &desc);

	if (Solve(&desc) == false)
		return 0;

	for (int y = 0; y < desc.Rows; y++)
	{
		for (int x = 0; x < desc.Columns; x++)
		{
			printf("%c", desc.Data[y][x]);
		}

		printf("\n");
	}

	return 0;
}