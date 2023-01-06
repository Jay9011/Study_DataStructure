#pragma once

struct Node
{
    int Data;

    Node* NextNode;
};

class Stack
{
public:
    Stack();
    ~Stack();

    void Push(Node* node);
    Node* Pop();

    Node* Top() { return top; }
    int Size();

    bool IsEmpty() { return list == nullptr; }

    static Node* CreateNode(int data);
    static void DestroyNode(Node** node);

private:
    Node* list = nullptr;
    Node* top = nullptr;
};