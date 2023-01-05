#pragma once

typedef int DataType;

struct Node
{
    DataType Data;
    Node* PrevNode;
    Node* NextNode;
};

Node* Create(DataType data);
void Destroy(Node** node);

void Push(Node** head, Node* node);
void Insert(Node* current, Node* node);
void InsertHead(Node** current, Node* head);

Node* GetNode(Node* head, int index);
int GetNodeCount(Node* head);

void Remove(Node** head, Node* remove);

