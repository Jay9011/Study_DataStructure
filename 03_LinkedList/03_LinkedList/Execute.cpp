#include "LinkedList.h"

typedef LinkedList<int> List;

//int main()
//{
//    List::Node* node = List::Create(10);
//
//    List* list = new List(node);
//    list->Push(List::Create(20));
//
//    List::Node* temp = List::Create(30);
//    list->Push(temp);
//    list->Push(List::Create(5));
//
//    list->Print(list->Head());
//
//    cout << endl;
//
//    list->Print(temp);
//
//    return 0;
//}

int main()
{
    List::Node* node = List::Create(1);

    List* list = new List(node);
    list->Push(List::Create(2));
    list->Push(List::Create(3));
    list->Push(List::Create(4));
    list->Push(List::Create(5));

    list->Print(list->Head());

    cout << endl;

    List::Node* temp = list->GetNode(3);
    list->Insert(temp, List::Create(10));

    list->Print(list->Head());

    return 0;
}