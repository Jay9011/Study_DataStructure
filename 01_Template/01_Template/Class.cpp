#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Character
{
public:
    void Set(T name)
    {
        this->name = name;
    }

    void Print()
    {
        cout << "Ä³¸¯ÅÍ : " << name << endl;
    }

private:
    T name;
};

//void main()
//{
//    Character<int> ob;
//    ob.Set(20);
//    ob.Print();
//
//    Character<string> obs;
//    obs.Set("Oak");
//    obs.Print();
//}