#pragma once

#include <iostream>
#include <list>
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

    void Prim(Node* startNode, Graph<T>* graph)
    {
        /*
        *  새로운 그래프에 기존 그래프의 데이터를 초기화
        */
        Node* currentNode = nullptr;
        Edge* currentEdge = nullptr;

        int* weights = new int[count];
        Node** mstNodes = new Node * [count];
        Node** friends = new Node * [count];
        Node** parents = new Node * [count];


        int index = 0;
        currentNode = head;
        while (currentNode != nullptr)
        {
            Graph<T>::Node* newNode = CreateNode(currentNode->Data);
            graph->AddNode(newNode);    // 기존 그래프의 노드들을 똑같이 추가해줍니다. (이때, 간선은 연결되어있지 않습니다.)

            weights[index] = INT_MAX;
            mstNodes[index] = newNode;
            friends[index] = nullptr;
            parents[index] = nullptr;
            currentNode = currentNode->Next;

            index++;
        }


        /*
        * Priority Queue를 통해 최소 비용에 대한 배열 정보를 입력합니다.
        */
        PQueue<Node*> queue(10);
        typename PQueue<Node*>::Node startQueueNode = typename PQueue<Node*>::Node(0, startNode);

        queue.Insert(startQueueNode);
        weights[startNode->Index] = 0;

        while (queue.Empty() == false)
        {
            typename PQueue<Node*>::Node poped = queue.RemoveMin();

            currentNode = poped.Data;
            friends[currentNode->Index] = currentNode;

            currentEdge = currentNode->Edge;
            while (currentEdge != nullptr)
            {
                Node* targetNode = currentEdge->Target;

                if (friends[targetNode->Index] == nullptr && currentEdge->Weight < weights[targetNode->Index])
                {
                    typename PQueue<Node*>::Node newNode = typename PQueue<Node*>::Node(currentEdge->Weight, targetNode);
                    queue.Insert(newNode);

                    parents[targetNode->Index] = currentEdge->Start;
                    weights[targetNode->Index] = currentEdge->Weight;
                }

                currentEdge = currentEdge->Next;    // currentNode의 모든 Edge들을 확인합니다.
            }//while(currentEdge)
        }//while(queue)


        /*
        * 만들어진 정보들을 가지고 간선을 연결해 줍니다.
        */
        for (int i = 0; i < count; i++)
        {
            int start, target;

            if (parents[i] == nullptr)
                continue;

            start = parents[i]->Index;
            target = i;

            graph->AddEdge(mstNodes[start], Graph<T>::CreateEdge(mstNodes[start], mstNodes[target], weights[i]));
            graph->AddEdge(mstNodes[target], Graph<T>::CreateEdge(mstNodes[target], mstNodes[start], weights[i]));

            cout << mstNodes[start]->Data << " -> " << mstNodes[target]->Data << ", " << weights[i] << endl;
        }

        cout << endl;

        delete[] weights;
        delete[] mstNodes;
        delete[] friends;
        delete[] parents;
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