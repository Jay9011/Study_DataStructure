#include <iostream>
using namespace std;

template<typename T>
void Print(T data)
{
    cout << "일반 함수 : " << data << endl;
}

template<>
void Print(float data)
{
    cout << "특수화 함수 : " << data << endl;
}

template<typename T>
void Print(T* data)
{
    cout << "포인터 함수 : " << *data << endl;
}

//void main()
//{
//    int i = 10;
//    //Print<int>(i);
//    Print(i);
//
//    float j = 20.f;
//    Print(j);
//
//    double k = 30.f;
//    Print(k);
//
//    int* p = &i;
//    Print<int>(p);
//}