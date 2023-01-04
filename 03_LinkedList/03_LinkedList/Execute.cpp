#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
    Node* node = nullptr;
    for (int i = 0; i < 5; i++)
    {
        Node* temp = Create(i);
        Push(&node, temp);
    }

    Node* newNode = nullptr;
    {
        newNode = Create(-1);
        InsertHead(&node, newNode);

        newNode = Create(-2);
        InsertHead(&node, newNode);
    }

    // Print
    {
        Node* current = GetNode(node, 2);
        newNode = Create(1000);

        Insert(current, newNode);

        int count = GetNodeCount(node);
        for (int i = 0; i < count; i++)
        {
            Node* current = GetNode(node, i);
            cout << "List[" << i << "] : " << current->Data << endl;
        }
        cout << "---------------------------------------------------" << endl << endl;
    }

    // Remove
    {
        Node* remove = GetNode(node, 3);
        Remove(&node, remove);

        int count = GetNodeCount(node);
        for (int i = 0; i < count; i++)
        {
            Node* current = GetNode(node, i);
            cout << "List[" << i << "] : " << current->Data << endl;
        }
        cout << "---------------------------------------------------" << endl << endl;
    }
    
    // Remove All
    {
        int count = GetNodeCount(node);

        for (int i = 0; i < count; i++)
        {
            Node* current = GetNode(node, 0);

            if (current != nullptr)
            {
                Remove(&node, current);
                Destroy(current);
            }
        }
    }

    return 0;
}