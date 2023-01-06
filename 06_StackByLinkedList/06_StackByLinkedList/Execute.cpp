#include <stdio.h>
#include "Stack.h"

int main()
{
    Stack stack;
    stack.Push(Stack::CreateNode(10));
    stack.Push(Stack::CreateNode(20));
    stack.Push(Stack::CreateNode(30));
    stack.Push(Stack::CreateNode(40));

    int count = stack.Size();
    printf("Size : %d\n", count);

    for (int i = 0; i < count; i++)
    {
        if (stack.IsEmpty() == true)
            break;

        Node* temp = stack.Pop();
        printf("pop : %d\n", temp->Data);
        Stack::DestroyNode(&temp);

        if (stack.IsEmpty() == false)
            printf("Top : %d\n", stack.Top()->Data);
        else
            printf("스택 비어있음!\n");
    }

    return 0;
}