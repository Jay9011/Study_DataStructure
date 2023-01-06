#include <stdio.h>
#include "Queue.h"

int main()
{
    Queue<int> queue;
    queue.Enqueue(Queue<int>::CreateNode(10));
    queue.Enqueue(Queue<int>::CreateNode(20));
    queue.Enqueue(Queue<int>::CreateNode(30));

    printf("Size : %d\n", queue.Size());

    while (queue.IsEmpty() == false)
    {
        Queue<int>::Node* node = queue.Dequeue();
        printf("Dequeue : %d\n", node->Data);

        Queue<int>::DestroyNode(&node);
    }

    printf("Final Size : %d\n", queue.Size());

    return 0;
}