#include "Stack.h"

Stack::Stack()
{
}

Stack::~Stack()
{
    while (IsEmpty() == false)
    {
        Node* node = Pop();
        DestroyNode(&node);
    }

    list = nullptr;
    top = nullptr;
}

void Stack::Push(Node* node)
{
    if (list != nullptr)
    {
        Node* oldTop = list;
        while (oldTop->NextNode != nullptr)
            oldTop = oldTop->NextNode;

        oldTop->NextNode = node;
    }
    else
    {
        list = node;
    }

    top = node;
}

Node* Stack::Pop()
{
    Node* temp = top;

    if (list == top)
    {
        list = nullptr;
        top = nullptr;
    }
    else
    {
        Node* currentTop = list;
        while ((currentTop->NextNode != nullptr) && (currentTop->NextNode != top))
            currentTop = currentTop->NextNode;

        top = currentTop;
        currentTop->NextNode = nullptr;
    }

    return temp;
}

int Stack::Size()
{
    int count = 0;
    Node* node = list;

    while (node != nullptr)
    {
        node = node->NextNode;
        count++;
    }

    return count;
}

Node* Stack::CreateNode(int data)
{
    Node* node = new Node();
    node->Data = data;
    node->NextNode = nullptr;

    return node;
}

void Stack::DestroyNode(Node** node)
{
    delete* node;
    *node = nullptr;
}
