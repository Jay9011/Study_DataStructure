#pragma once

template<typename T>
class Queue
{
public:
    struct Node;

public:
    ~Queue()
    {
        while (IsEmpty() == false)
        {
            Node* node = Dequeue();
            DestroyNode(&node);
        }
    }

    void Enqueue(Node* node)
    {
        if (front == nullptr)
            front = node;
        else
            rear->Next = node;

        rear = node;

        count++;
    }

    Node* Dequeue()
    {
        Node* node = front;

        if (front->Next == nullptr)
            front = rear = nullptr;
        else
            front = front->Next;

        count--;

        return node;
    }

    int Size() { return count; }

    bool IsEmpty()
    {
        return front == nullptr;
    }

public:
    static Node* CreateNode(T data)
    {
        Node* node = new Node();
        node->Data = data;
        node->Next = nullptr;

        return node;
    }

    static void DestroyNode(Node** node)
    {
        delete* node;
        *node = nullptr;
    }

public:
    struct Node
    {
        T Data;
        Node* Next;
    };

private:
    int count = 0;

    Node* front = nullptr;
    Node* rear = nullptr;
};