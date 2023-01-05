#include <iostream>
#include "DLinkedList.h"
using namespace std;

Node* Create(DataType data)
{
    Node* node = new Node();

    node->Data = data;
    node->PrevNode = nullptr;
    node->NextNode = nullptr;

    return node;
}

void Destroy(Node** node)
{
    delete* node;
    *node = nullptr;
}

void Push(Node** head, Node* node)
{
    if (*head != nullptr)
    {
        Node* tail = (*head);

        while (tail->NextNode != nullptr)
            tail = tail->NextNode;

        tail->NextNode = node;
        node->PrevNode = tail;
    }
    else
    {
        *head = new Node();
    }
}

void Insert(Node* current, Node* node)
{
    node->NextNode = current->NextNode;
    node->PrevNode = current;

    if (current->NextNode != nullptr)
        current->NextNode->PrevNode = node;

    current->NextNode = node;
}

void InsertHead(Node** current, Node* head)
{
    if (*current == nullptr)
    {
        *current = head;
    }
    else
    {
        head->NextNode = *current;
        (*current)->PrevNode = head;
        *current = head;
    }
}

Node* GetNode(Node* head, int index)
{
    Node* current = head;

    while (current != nullptr && (--index >= 0))
        current = current->NextNode;

    return current;
}

int GetNodeCount(Node* head)
{
    int count = 0;
    Node* current = head;

    while (current != nullptr)
    {
        current = current->NextNode;
        count++;
    }

    return count;
}

void Remove(Node** head, Node* remove)
{
    if (*head == remove)
    {
        *head = remove->NextNode;

        if (*head != nullptr)
            (*head)->PrevNode = nullptr;

        remove->PrevNode = nullptr;
        remove->NextNode = nullptr;
    }
    else
    {
        Node* current = remove;

        remove->PrevNode->NextNode = current->NextNode;
        if (remove->NextNode != nullptr)
            remove->NextNode->PrevNode = current->PrevNode;

        remove->PrevNode = nullptr;
        remove->NextNode = nullptr;
    }
}

