#pragma once
#include <iostream>
#include <memory>
#include <string>
using namespace std;

template<typename T>
class PQueue
{
public:
    struct Node;

public:
    PQueue(int capacity)
        : capacity(capacity)
    {
        nodes = new Node[capacity];
        size = 0;
    }

    ~PQueue()
    {
        delete[] nodes;
        nodes = nullptr;
    }

    int Parent(int index)
    {
        return (int)((index - 1) / 2);
    }

    int LeftChild(int index)
    {
        return (index * 2) + 1;
    }

    int RightChild(int index)
    {
        return (index * 2) + 2;
    }

    void SwapNode(int index1, int index2)
    {
        Node temp;
        temp = nodes[index1];
        nodes[index1] = nodes[index2];
        nodes[index2] = temp;
    }

    void Insert(Node data)
    {
        int current = size;
        int parent = Parent(current);

        if (size == capacity)
        {
            Node* temp = new Node[capacity * 2 + 1];
            memcpy(temp, nodes, sizeof(Node) * capacity);

            delete[] nodes;
            nodes = temp;

            capacity = capacity * 2 + 1;
        }

        nodes[current] = data;

        while (current > 0 && nodes[current].Priority < nodes[parent].Priority)
        {
            SwapNode(current, parent);

            current = parent;
            parent = Parent(current);
        }

        size++;
    }

    Node RemoveMin()
    {
        int parent = 0;
        int left = 0;
        int right = 0;

        Node result = nodes[0];

        size--;
        SwapNode(0, size);  // 루트 노드와 마지막 노드 교환

        left = LeftChild(0);
        right = left + 1;

        while (true)
        {
            int selected = 0;

            if (left >= size)
                break;

            if (right >= size)
            {
                selected = left;
            }
            else
            {
                if (nodes[left].Priority > nodes[right].Priority)
                    selected = right;
                else
                    selected = left;
            }

            if (nodes[selected].Priority < nodes[parent].Priority)
            {
                SwapNode(parent, selected);

                parent = selected;
            }
            else
            {
                break;
            }

            left = LeftChild(parent);
            right = left + 1;
        }

        return result;
    }

    bool Empty() { return 0 == size; }

    void Print()
    {
        for (int i = 0; i < size; i++)
        {
            int parent = -1;
            if (i > 0)
                parent = Parent(i);

            cout << nodes[i].Priority << "|" << nodes[i].Data << ", ";
        }

        cout << endl << endl;
    }

public:
    struct Node
    {
        int Priority;
        T Data;

        Node() {}
        Node(int priority, T data) 
        { 
            this->Priority = priority;
            Data = data; 
        }
    };

private:
    Node* nodes;

    int capacity;
    int size;
};