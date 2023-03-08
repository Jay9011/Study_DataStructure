#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

enum class Color
{
    Red = 0,
    Black = 1,
};

struct Node
{
    Color color = Color::Black;

    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    
    int key = {};
};

/*
* Red-Black Tree
*
* 1) ��� ���� Red �� Black
* 2) ��Ʈ�� Blakc
* 3) Leaf(NIL) �� Black
* 4) Red ����� �ڽĵ��� Black
* 5) �� ������ ���� �������� ��� ��ο� �ִ� Black �� ��� ���� ��
*
* �� ��� ������ Red �� �����մϴ�.
*/
class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

public:
    void Print();
    void Print(Node* node, int x, int y);

    Node* Search(Node* node, int key);

    Node* Min(Node* node);
    Node* Max(Node* node);
    Node* Next(Node* node);

    void Insert(int key);
    void InsertFixup(Node* node);

    void Delete(int key);
    void Delete(Node* node);
    void DeleteFixup(Node* node);

    void Replace(Node* u, Node* v);

    void LeftRotate(Node* node);
    void RightRotate(Node* node);

private:
    Node* root = nullptr;
    Node* nil  = nullptr;
};
