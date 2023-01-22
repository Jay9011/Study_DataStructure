#pragma once

#include <iostream>
using namespace std;

#include "PQueue.h"

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

    void Dijkstra(Node* startNode, Graph<T>* graph)
    {
        int* weights = new int[count];
        Node** shorts = new Node * [count];
        Node** connected = new Node * [count];
        Node** parents = new Node * [count];

        /*
        * 각 Node들 초기화
        */
        Edge* currentEdge = nullptr;
        Node* currentNode = head;
        for (int index = 0; currentNode != nullptr; index++)
        {
            Node* newNode = CreateNode(currentNode->Data);
            graph->AddNode(newNode);

            weights[index] = INT_MAX;
            shorts[index] = newNode;
            connected[index] = nullptr;
            parents[index] = nullptr;

            currentNode = currentNode->Next;
        }

        /*
        * 
        */
        PQueue<Node*> queue(10);
        typename PQueue<Node*>::Node startQNode = typename PQueue<Node*>::Node(0, startNode);  // 첫 시작 노드까지의 가중치는 0이다.

        queue.Insert(startQNode);
        weights[startNode->Index] = 0;
        while (queue.Empty() == false)
        {
            typename PQueue<Node*>::Node poped = queue.RemoveMin();
            currentNode = poped.Data;

            connected[currentNode->Index] = currentNode;


            //정점에 연결된 모든 간선들을 검사한다.
            currentEdge = currentNode->Edge;
            while (currentEdge != nullptr)
            {
                Node* targetNode = currentEdge->Target;

                bool b = true;
                b &= connected[targetNode->Index] == nullptr;
                b &= weights[currentNode->Index] + currentEdge->Weight < weights[targetNode->Index];

                if (b == true)
                {
                    typename PQueue<Node*>::Node newNode = typename PQueue<Node*>::Node(currentEdge->Weight, targetNode);
                    queue.Insert(newNode);  //해당 노드까지의 가중치가 적다면 queue에 추가한다.

                    parents[targetNode->Index] = currentEdge->Start;    // 추가한 노드의 부모를 변경한다.
                    weights[targetNode->Index] = weights[currentNode->Index] + currentEdge->Weight; // 추가한 노드의 가중치를 변경한다.
                }//if

                currentEdge = currentEdge->Next;
            }//while(currentEdge)
        }//while(queue)

        for (int i = 0; i < count; i++)
        {
            if (parents[i] == nullptr)
                continue;

            int start = parents[i]->Index;
            int target = i;

            graph->AddEdge(shorts[start], Graph<T>::CreateEdge(shorts[start], shorts[target], weights[i]));

            cout << shorts[start]->Data << "->" << shorts[target]->Data << " : " << weights[i] << endl;
        }
        cout << endl;


        delete[] connected;
        delete[] parents;
        delete[] shorts;
        delete[] weights;
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

public:
    static Edge* CreateEdge(Node* start, Node* target, int weight)
    {
        Edge* edge = new Edge();
        edge->Start = start;
        edge->Target = target;
        edge->Weight = weight;

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
        int Weight = 0;

        Node* Start = nullptr;  // 간선의 시작 정점
        Node* Target = nullptr; // 시작 정점과 인접하는 인접 정점

        Edge* Next = nullptr;   // 정점에 포함되는 모든 Edge 리스트
    };

private:
    Node* head = nullptr;
    int count = 0;
};