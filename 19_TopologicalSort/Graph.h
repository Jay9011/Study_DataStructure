#pragma once

#include <iostream>
#include <list>
using namespace std;

template<typename T>
class Graph
{
public:
    struct Edge;
    struct Node;

public:
    void AddNode(Node* node)
    {
        Node* nodeList = head;
        if (nodeList != nullptr)
        {
            while (nodeList->Next != nullptr)
                nodeList = nodeList->Next;

            nodeList->Next = node;
        }
        else
        {
            head = node;
        }//if(nodeList != nullptr)

        node->Index = count++;
    }

    void AddEdge(Node* node, Edge* edge)
    {
        if (node->Edge != nullptr)
        {
            Edge* edgeList = node->Edge;

            while (edgeList->Next != nullptr)
                edgeList = edgeList->Next;

            edgeList->Next = edge;
        }
        else
        {
            node->Edge = edge;
        }//if(node->Edge != nullptr)
    }

    void DFS(Node* node)
    {
        node->Visited = true;
        
        Edge* edge = node->Edge;
        while (edge != nullptr)
        {
            if ((edge->Target != nullptr) && (edge->Target->Visited == false))
                DFS(edge->Target);  // �Լ� ���� ��

            edge = edge->Next;  // ���� ���� Ž�� (����� ���� ��尡 �����ϴ��� Ȯ��)
        }

        list.push_front(node);  // Head�� �����Ѵ�. (DFS�� �������� ó�� ��ġ�� ����̱� ����)
    }

    void Sort(Node* node)
    {
        // ��� node���� Ž���ϸ� incoming edge�� ���� ����� DFS�� �����Ѵ�.
        while (node != nullptr && node->Visited == false)
        {
            DFS(node);

            node = node->Next;
        }
    }

    void Print()
    {
        Node* node = nullptr;
        Edge* edge = nullptr;

        if ((node = head) == nullptr)
            return;

        while (node != nullptr)
        {
            cout << node->Data << " : ";

            if ((edge = node->Edge) == nullptr)
            {
                node = node->Next;
                cout << endl;

                continue;
            }

            while (edge != nullptr)
            {
                cout << edge->Target->Data;
                edge = edge->Next;
            }

            cout << endl;

            node = node->Next;
        }//while (node != nullptr)

        cout << endl;
    }

    void PrintResult()
    {
        while (list.empty() == false)
        {
            cout << list.front()->Data;
            list.pop_front();
        }
    }

public:
    static Edge* CreateEdge(Node* start, Node* target)
    {
        Edge* edge = new Edge();
        edge->Start = start;
        edge->Target = target;

        return edge;
    }

    static Node* CreateNode(T data)
    {
        Node* node = new Node();
        node->Data = data;

        return node;
    }

public:
    struct Node
    {
        T Data = T();
        int Index = -1;
        bool Visited = false;

        Node* Next = nullptr;   // ��� ���� ����Ʈ���� �����ϱ� ���� ��� ����Ʈ (���� ����Ʈ)

        Edge* Edge = nullptr;   // �� ������ ����Ǿ� �ִ� ���� ������ ǥ���ϴ� ������
    };

    struct Edge
    {
        Node* Start = nullptr;  // ������ ���� ����
        Node* Target = nullptr; // ���� ������ �����ϴ� ���� ����

        Edge* Next = nullptr;   // ������ ���ԵǴ� ��� Edge ����Ʈ
    };

private:
    Node* head = nullptr;
    int count = 0;

    list<Node*> list;
};