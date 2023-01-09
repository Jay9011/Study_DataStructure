#pragma once

#include <iostream>
using namespace std;

template<typename T>
class BTree
{
public:
	struct Node;

public:
	~BTree()
	{
		Destroy(root);
	}

public:
	void PreOrder(Node* node)
	{
		if (node == nullptr) return;

		cout << " " << node->Data;
		PreOrder(node->Left);
		PreOrder(node->Right);
	}
	
	void InOrder(Node* node)
	{
		if (node == nullptr) return;

		InOrder(node->Left);
		cout << " " << node->Data;
		InOrder(node->Right);
	}
	
	void PostOrder(Node* node)
	{
		if (node == nullptr) return;

		PostOrder(node->Left);
		PostOrder(node->Right);
		cout << " " << node->Data;
	}

private:
	void Destroy(Node* node)
	{
		if (node == nullptr) return;

		Destroy(node->Left);
		Destroy(node->Right);

		DestroyNode(&node);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Left = node->Right = nullptr;

		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

public:
	void Root(Node* node) { this->root = node; }

public:
	struct Node
	{
		T Data;

		Node* Left;
		Node* Right;
	};

private:
	Node* root = nullptr;
};