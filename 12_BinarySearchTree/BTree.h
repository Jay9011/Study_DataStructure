#pragma once

#include <iostream>
using namespace std;

template<typename T>
class BTree
{
public:
	struct Node;

public:
	BTree(){}
	~BTree()
	{
		
	}

	void Insert(Node** parent, Node* child)
	{
		if ((*parent)->Data < child->Data)
		{
			// �� �����̶�� �ּ� ����
			if ((*parent)->Right == nullptr)
				(*parent)->Right = child;
			// ��尡 �����Ѵٸ� ������ ��带 �θ�� �ٽ� ����
			else
				return Insert(&(*parent)->Right, child);
		}
		else if ((*parent)->Data > child->Data)
		{
			// �� �����̶�� �ּ� ����
			if ((*parent)->Left == nullptr)
				(*parent)->Left = child;
			// ��尡 �����Ѵٸ� ���� ��带 �θ�� �ٽ� ����
			else
				return Insert(&(*parent)->Left, child);
		}
	}

	Node* Search(Node* node, T data, int& depth)
	{
		if (node == nullptr)
			return nullptr;

		depth++;

		if (node->Data == data)
			return node;
		else if (node->Data > data)
			return Search(node->Left, data, depth);
		else if (node->Data < data)
			return Search(node->Right, data, depth);

		return nullptr;
	}

	Node* SearchMinValue(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->Left == nullptr)
			return node;
		else
			return SearchMinValue(node->Left);
	}
	
	Node* SearchMaxValue(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->Right == nullptr)
			return node;
		else
			return SearchMaxValue(node->Right);
	}

	Node* Remove(Node* node, Node* parent, T data)
	{
		Node* remove = nullptr;
		if (node == nullptr)
			return nullptr;

		if (node->Data > data)
		{
			remove = Remove(node->Left, node, data);
		}
		else if (node->Data < data)
		{
			remove = Remove(node->Right, node, data);
		}
		// Ž�� �Ϸ�, ��� ����
		else
		{
			remove = node;

			// Leaf ����� ���
			if (node->Left == nullptr && node->Right == nullptr)
			{
				if (parent->Left == node)
					parent->Left = nullptr;
				else
					parent->Right = nullptr;
			}
			else
			{
				// �ڽ� ��尡 �� �� �ִ� ���
				if ((node->Left != nullptr) && (node->Right != nullptr))
				{
					Node* minNode = SearchMinValue(node->Right);

					minNode = Remove(node, nullptr, minNode->Data);
					node->Data = minNode->Data;

					return minNode;
				}
				// �ڽ� ��尡 �� �� �ִ� ���
				else
				{
					Node* temp = nullptr;

					if (node->Left != nullptr)
						temp = node->Left;
					else
						temp = node->Right;

					if (parent->Left == node)
						parent->Left = temp;
					else
						parent->Right = temp;
				}
			}//if (node->Left == nullptr && node->Right == nullptr)
		}//if (node->Data > data)

		return remove;
	}

	void InOrder(Node* node, int depth)
	{
		if (node == nullptr)
			return;

		depth++;

		InOrder(node->Left, depth);
		cout << " " << node->Data << "|" << depth;
		InOrder(node->Right, depth);
	}

	Node* Root() { return root; }
	void Root(Node* node) { this->root = node; }

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
	struct Node
	{
		T Data;
		Node* Left;
		Node* Right;
	};

private:
	Node* root;
};