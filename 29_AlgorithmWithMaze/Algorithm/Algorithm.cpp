#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
class Vector
{
public:
	Vector() = default;
	~Vector()
	{
		if (Data)
			delete[] Data;
	}

	void push_back(const T& value)
	{
		// ���� ������ Ȯ���� Ȯ���մϴ�.
		if (Size == Capacity)
		{
			int newCapacity = static_cast<int>(Capacity * 1.5);
			if (newCapacity == Capacity)
				newCapacity++;	// ���� ���ο� ���� ũ�Ⱑ ���� ������ ũ��� ���� ��� (1*1.5=1)

			reserve(newCapacity);
		}

		// ���ο� �����͸� ����
		Data[Size] = value;

		// ���� ������� ������ ũ�⸦ �����մϴ�.
		Size++;
	}

	void reserve(int capacity)
	{
		if (Capacity >= capacity)
			return;

		Capacity = capacity;

		T* newData = new T[Capacity];

		// ���� �����͸� �����մϴ�.
		for (int i = 0; i < Size; i++)
			newData[i] = Data[i];

		if (Data)
			delete[] Data;

		// ���ο� ������ ����ŵ�ϴ�.
		Data = newData;
	}

	T& operator[](const int pos) { return Data[pos]; }

	int size() { return Size; }
	int capacity() { return Capacity; }

	void clear()
	{
		if (Data)
		{
			delete[] Data;
			Data = new T[Capacity];
		}

		Size = 0;
	}

private:
	T* Data = nullptr;
	int Size = 0;     // ������� ���� ũ��
	int Capacity = 0; // ���� ���� ũ��
};


template<typename T>
class Node
{
public:
	Node() : Prev(nullptr), Next(nullptr), Data(T())
	{}

	Node(const T& value) : Prev(nullptr), Next(nullptr), Data(value)
	{}

public:
	T Data;
	Node* Prev;
	Node* Next;
};

template<typename T>
class Iterator
{
public:
	Iterator() : node(nullptr)
	{}

	Iterator(Node<T>* node) : node(node)
	{}

	// ++it
	Iterator& operator++()
	{
		node = node->Next;
		return *this;
	}

	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		node = node->Next;
		return temp;
	}

	// --it
	Iterator& operator--()
	{
		node = node->Prev;
		return *this;
	}

	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		node = node->Prev;
		return temp;
	}

	// *it
	T& operator*()
	{
		return node->Data;
	}

	bool operator==(const Iterator& other)
	{
		return node == other.node;
	}

	bool operator!=(const Iterator& other)
	{
		return node != other.node;
	}

public:
	Node<T>* node;
};

template<typename T>
class List
{
public:
	List() : Size(0)
	{
		// head �� tail �̶�� ���� ��带 ����ϴ�.
		// (���� ��带 ����� ��� Add�� Remove�� �ϰ��� �ְ� �ۼ��� �� �ֽ��ϴ�.)
		// (�̶��� size �� �������Ѽ��� �ȵ˴ϴ�.)
		// [head] <-> ... <-> [tail]
		Head = new Node<T>();
		Tail = new Node<T>();
		Head->Next = Tail;
		Tail->Prev = Head;
	}

	~List()
	{
		while (Size > 0)
			pop_back();

		delete Head;
		delete Tail;
	}

	void push_back(const T& value)
	{
		// tail ������ value �� �߰��մϴ�.
		AddNode(Tail, value);
	}

	void pop_back()
	{
		// tail �ٷ� ���� ��带 �����մϴ�. (���� ���� �� Node)
		RemoveNode(Tail->Prev);
	}

private:
	// [head] <-> [1] <-> [prevNode] <-> [before] <-> [tail]
	// [head] <-> [1] <-> [prevNode] <-> [newNode] <-> [before] <-> [tail]
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->Prev;

		prevNode->Next = newNode;
		newNode->Prev = prevNode;

		newNode->Next = before;
		before->Prev = newNode;

		Size++;

		return newNode;
	}

	// [head] <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]
	// [head] <-> [prevNode] <-> [nextNode] <-> [tail]
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->Prev;
		Node<T>* nextNode = node->Next;

		prevNode->Next = nextNode;
		nextNode->Prev = prevNode;

		delete node;

		Size--;

		return nextNode;
	}

	int size() { return Size; }

public:
	// List ������ Iterator<T> �� ������ �Ͽ� ����ϴ� ���� ���մϴ�.
	using iterator = Iterator<T>;

	iterator begin() { return iterator(Head->Next); }	// �����Ͱ� ���� �����ϴ� ��ġ�� Head �� Next �Դϴ�.
	iterator end() { return iterator(Tail); }			// tail �� ���� end �� ����ų �� �ֽ��ϴ�.

	// ���ͷ����� '�տ�' �����͸� �߰� ���ݴϴ�.
	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it.node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it.node);
		return iterator(node);
	}

private:
	Node<T>* Head;
	Node<T>* Tail;
	int Size;
};

int main()
{
	//vector<int> v;
	////Vector<int> v;

	//v.reserve(100);
	//cout << v.size() << " " << v.capacity() << endl;

	//for (int i = 0; i < 100; i++)
	//{
	//	v.push_back(i);
	//	cout << v.size() << " " << v.capacity() << endl;
	//}

	////v.resize(10);
	////cout << v.size() << " " << v.capacity() << endl;

	//v.clear();
	//cout << v.size() << " " << v.capacity() << endl;

	//list<int> li;

	//list<int>::iterator eraseIt;
	List<int> li;

	List<int>::iterator eraseIt;
	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			eraseIt = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
		}
	}

	li.pop_back();

	li.erase(eraseIt);

	for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}
}