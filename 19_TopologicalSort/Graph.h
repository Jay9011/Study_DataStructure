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
                DFS(edge->Target);  // 함수 스택 콜

            edge = edge->Next;  // 다음 간선 탐색 (연결된 인접 노드가 존재하는지 확인)
        }

        list.push_front(node);  // Head에 삽입한다. (DFS의 마지막은 처음 위치한 노드이기 때문)
    }

    void Sort(Node* node)
    {
        // 모든 node들을 탐색하며 incoming edge가 없던 노드의 DFS를 실행한다.
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

        Node* Next = nullptr;   // 모든 정점 리스트들을 관리하기 위한 노드 리스트 (선형 리스트)

        Edge* Edge = nullptr;   // 이 정점과 연결되어 있는 인접 정점을 표현하는 간선들
    };

    struct Edge
    {
        Node* Start = nullptr;  // 간선의 시작 정점
        Node* Target = nullptr; // 시작 정점과 인접하는 인접 정점

        Edge* Next = nullptr;   // 정점에 포함되는 모든 Edge 리스트
    };

private:
    Node* head = nullptr;
    int count = 0;

    list<Node*> list;
};