#pragma once

// 그래프/트리 응용
/*
 *	최소 스패닝 트리 (Minimum Spanning Tree)
 *
 *	상호 배타적 집합 (Disjoint Set)
 *	-> 유니온-파인드 Union-Find (합치기-찾기)
 *
 *	트리 구조를 이용한 상호 배타적 집합의 표현
 *
 *	시간 복잡도 : 트리의 높이에 비례한 시간이 걸림
 */

// 트리가 한쪽으로 기우는 문제를 해결?
// 트리를 합칠 때, 항상 [높이가 낮은 트리를] [높이가 높은 트리] 밑으로
// (Union-By-Rank) 랭크에 의한 합치기 최적화

// 시간 복잡도 O(Ackermann(n)) = O(1)
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}
	
	int Find(int u)
	{
		if (u == _parent[u])
			return u;
		
		return _parent[u] = Find(_parent[u]);
	}

	// u와 v를 합친다
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		if (_rank[u] > _rank[v])
			swap(u, v);

		// rank[u] <= rank[v] 보장됨
		_parent[u] = v;

		// 서브트리 u 밑에 서브트리 v 가 추가로 들어가므로 v 의 rank 가 1 증가합니다.
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};
