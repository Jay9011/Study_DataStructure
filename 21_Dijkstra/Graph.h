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
        * �� Node�� �ʱ�ȭ
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
        typename PQueue<Node*>::Node startQNode = typename PQueue<Node*>::Node(0, startNode);  // ù ���� �������� ����ġ�� 0�̴�.

        queue.Insert(startQNode);
        weights[startNode->Index] = 0;
        while (queue.Empty() == false)
        {
            typename PQueue<Node*>::Node poped = queue.RemoveMin();
            currentNode = poped.Data;

            connected[currentNode->Index] = currentNode;


            //������ ����� ��� �������� �˻��Ѵ�.
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
                    queue.Insert(newNode);  //�ش� �������� ����ġ�� ���ٸ� queue�� �߰��Ѵ�.

                    parents[targetNode->Index] = currentEdge->Start;    // �߰��� ����� �θ� �����Ѵ�.
                    weights[targetNode->Index] = weights[currentNode->Index] + currentEdge->Weight; // �߰��� ����� ����ġ�� �����Ѵ�.
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