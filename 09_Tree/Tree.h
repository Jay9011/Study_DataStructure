#pragma once

#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template<typename T>
class Tree
{
public:
	struct Node;

public:
	void AddChild(Node* parent, Node* child)
	{
		if (parent->LeftChild == nullptr)
		{
			parent->LeftChild = child;
			return;
		}

		Node* node = parent->LeftChild;
		while (node->RightSibling != nullptr)
			node = node->RightSibling;

		node->RightSibling = child;
	}

	void PrintNode(Node* node, int depth)
	{
		for (int i = 0; i < depth; i++)
			cout << "-";

		cout << node->Data << endl;
		queue.push(node->Data);
		stack.push(node);
		
		if (node->LeftChild != nullptr)
			PrintNode(node->LeftChild, depth + 1);

		if(node->RightSibling != nullptr)
			PrintNode(node->RightSibling, depth);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->LeftChild = node->RightSibling = nullptr;

		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

public:
	queue<T>* Queue() { return &queue; }
	stack<Node*>* Stack() { return &stack; }

public:
	struct Node
	{
		T Data;

		Node* LeftChild;
		Node* RightSibling;

		~Node()
		{
			Data = 0;

			LeftChild = nullptr;
			RightSibling = nullptr;
		}
	};

private:
	queue<T> queue;
	stack<Node*> stack;
};