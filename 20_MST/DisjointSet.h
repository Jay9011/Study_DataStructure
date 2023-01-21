#pragma once

template<typename T>
class DisjointSet
{
public:
	struct Set;

public:
	static Set* CreateSet(T data)
	{
		Set* set = new Set();
		set->Data = data;
		set->parent = nullptr;

		return set;
	}

	static void DestroySet(Set* set)
	{
		delete set;
		set = nullptr;
	}

	static void UnionSet(Set* parent, Set* set)
	{
		set = FindSet(set);
		set->parent = parent;
	}

	static Set* FindSet(Set* set)
	{
		while (set->parent != nullptr)
			set = set->parent;

		return set;
	}

public:
	struct Set
	{
		T Data;
		Set* parent;
	};

private:

};