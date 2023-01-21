#pragma once

#include <iostream>
#include <list>
using namespace std;

#include "PQueue.h"
#include "DisjointSet.h"

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
        *  ���ο� �׷����� ���� �׷����� �����͸� �ʱ�ȭ
        */
        Node* currentNode = nullptr;
        Edge* currentEdge = nullptr;

        int* weights = new int[count];
        Node** mstNodes = new Node * [count];
        Node** connected = new Node * [count];
        Node** parents = new Node * [count];


        int index = 0;
        currentNode = head;
        while (currentNode != nullptr)
        {
            Graph<T>::Node* newNode = CreateNode(currentNode->Data);
            graph->AddNode(newNode);    // ���� �׷����� ������ �Ȱ��� �߰����ݴϴ�. (�̶�, ������ ����Ǿ����� �ʽ��ϴ�.)

            weights[index] = INT_MAX;
            mstNodes[index] = newNode;
            connected[index] = nullptr;
            parents[index] = nullptr;
            currentNode = currentNode->Next;

            index++;
        }


        /*
        * Priority Queue�� ���� �ּ� ��뿡 ���� �迭 ������ �Է��մϴ�.
        */
        PQueue<Node*> queue(10);
        typename PQueue<Node*>::Node startQueueNode = typename PQueue<Node*>::Node(0, startNode);

        queue.Insert(startQueueNode);
        weights[startNode->Index] = 0;

        while (queue.Empty() == false)
        {
            typename PQueue<Node*>::Node poped = queue.RemoveMin();

            currentNode = poped.Data;
            connected[currentNode->Index] = currentNode;

            currentEdge = currentNode->Edge;
            while (currentEdge != nullptr)
            {
                Node* targetNode = currentEdge->Target;

                if (connected[targetNode->Index] == nullptr && currentEdge->Weight < weights[targetNode->Index])
                {
                    typename PQueue<Node*>::Node newNode = typename PQueue<Node*>::Node(currentEdge->Weight, targetNode);
                    queue.Insert(newNode);

                    parents[targetNode->Index] = currentEdge->Start;
                    weights[targetNode->Index] = currentEdge->Weight;
                }

                currentEdge = currentEdge->Next;    // currentNode�� ��� Edge���� Ȯ���մϴ�.
            }//while(currentEdge)
        }//while(queue)


        /*
        * ������� �������� ������ ������ ������ �ݴϴ�.
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
        delete[] connected;
        delete[] parents;
    }

    void Kruskal(Graph<T>* graph)
    {
        Node** mstNodes = new Node * [count];
        PQueue<Edge*> queue(10);

        typename DisjointSet<Node*>::Set** sets = new typename DisjointSet<Node*>::Set * [count];


        int index = 0;
        Node* currentNode = head;
        Edge* currentEdge = nullptr;

        while (currentNode != nullptr)
        {
            sets[index] = DisjointSet<Node*>::CreateSet(currentNode);
            mstNodes[index] = CreateNode(currentNode->Data);
            graph->AddNode(mstNodes[index]);

            currentEdge = currentNode->Edge;
            while (currentEdge != nullptr)
            {
                typename PQueue<Edge*>::Node newNode = typename PQueue<Edge*>::Node(currentEdge->Weight, currentEdge);
                queue.Insert(newNode);

                currentEdge = currentEdge->Next;
            }//while(currentEdge)

            currentNode = currentNode->Next;
            index++;
        }//while(currentNode)


        while (queue.Empty() == false)
        {
            typename PQueue<Edge*>::Node poped = queue.RemoveMin();
            currentEdge = poped.Data;


            int start = currentEdge->Start->Index;
            int target = currentEdge->Target->Index;

            // Start�� ���� �θ�� Target�� ���� �θ� ������ ���� ���տ� ���������Ƿ� �������� �ʽ��ϴ�.
            if (DisjointSet<Node*>::FindSet(sets[start]) == DisjointSet<Node*>::FindSet(sets[target]))
                continue;

            // Ȯ�ε� �� ������ ���������� �������ݴϴ�.
            DisjointSet<Node*>::UnionSet(sets[start], sets[target]);

            graph->AddEdge(mstNodes[start], Graph<T>::CreateEdge(mstNodes[start], mstNodes[target], currentEdge->Weight));
            graph->AddEdge(mstNodes[target], Graph<T>::CreateEdge(mstNodes[target], mstNodes[start], currentEdge->Weight));

            cout << mstNodes[start]->Data << " -> " << mstNodes[target]->Data << ", " << currentEdge->Weight << endl;
        }

        cout << endl;

        delete[] sets;
        delete[] mstNodes;
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

        Node* Next = nullptr;   // ��� ���� ����Ʈ���� �����ϱ� ���� ��� ����Ʈ (���� ����Ʈ)

        Edge* Edge = nullptr;   // �� ������ ����Ǿ� �ִ� ���� ������ ǥ���ϴ� ������
    };

    struct Edge
    {
        int Weight = 0;

        Node* Start = nullptr;  // ������ ���� ����
        Node* Target = nullptr; // ���� ������ �����ϴ� ���� ����

        Edge* Next = nullptr;   // ������ ���ԵǴ� ��� Edge ����Ʈ
    };

private:
    Node* head = nullptr;
    int count = 0;
};