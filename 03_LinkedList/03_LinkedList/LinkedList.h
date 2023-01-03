#pragma once

#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
	struct Node;
	
public:
	static Node* Create(T data)
	{
		Node* node = new Node();

		node->Data = data;
		node->Next = nullptr;

		return node;
	}

	static void Destroy(Node* node)
	{
		delete node;
		node = nullptr;
	}

public:
	LinkedList(Node* head)
	{
		this->head = head;
	}

	Node* Head() { return head; }

	void Push(Node* node)
	{
		Node* tail = head;

		while (tail->Next != nullptr)
			tail = tail->Next;

		tail->Next = node;
	}

	void Insert(Node* current, Node* node)
	{
		node->Next = current->Next;
		current->Next = node;
	}

	Node* GetNode(int index)
	{
		Node* current = head;

		while (current != nullptr && (--index) >= 0)
			current = current->Next;

		return current;
	}

	int Size()
	{
		int count = 0;
		Node* current = head;

		while (current != nullptr)
		{
			current = current->Next;
			count++;
		}

		return count;
	}

	void Print(Node* node)
	{
		if (node == nullptr)
			return;

		cout << node->Data << endl;

		return Print(node->Next);
	}

public:
	struct Node
	{
		T Data;
		Node* Next;
	};

private:
	Node* head;

};