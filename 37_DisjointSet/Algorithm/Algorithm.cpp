#include <iostream>

#include "DisjointSet.h"

using namespace std;


int main()
{
	DisjointSet teams(1000);

	cout << "Before ] Team 1 : " << teams.Find(1) << " / Team 10 : " << teams.Find(10) << endl;

	teams.Merge(10, 1);
	int teamId = teams.Find(1);
	int teamId2 = teams.Find(10);

	cout << "After  ] Team 1 : " << teams.Find(1) << " / Team 10 : " << teams.Find(10) << endl;


	cout << "Before ] Team 3 : " << teams.Find(3) << " / Team 2 : " << teams.Find(2) << endl;

	teams.Merge(3, 2);
	int teamId3 = teams.Find(3);
	int teamId4 = teams.Find(2);

	cout << "After  ] Team 3 : " << teams.Find(3) << " / Team 2 : " << teams.Find(2) << endl;


	cout << "Before ] Team 1 : " << teams.Find(1) << " / Team 3 : " << teams.Find(3) << endl;

	teams.Merge(1, 3);
	int teamId5 = teams.Find(1);
	int teamId6 = teams.Find(3);

	cout << "After  ] Team 1 : " << teams.Find(1) << " / Team 3 : " << teams.Find(3) << endl;

}