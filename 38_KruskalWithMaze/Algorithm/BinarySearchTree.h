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
* 1) 모든 노드는 Red 나 Black
* 2) 루트는 Blakc
* 3) Leaf(NIL) 은 Black
* 4) Red 노드의 자식들은 Black
* 5) 각 노들부터 리프 노드까지의 모든 경로에 있는 Black 은 모두 같은 수
*
* 새 노드 삽입은 Red 를 삽입합니다.
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
