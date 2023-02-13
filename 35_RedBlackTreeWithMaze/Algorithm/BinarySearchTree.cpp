#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std;

enum class ConsoleColor
{
    BLACK = 0,
    RED = FOREGROUND_RED,
    GREEN = FOREGROUND_GREEN,
    BLUE = FOREGROUND_BLUE,
    YELLOW = RED | GREEN,
    WHITE = RED | GREEN | BLUE,
};

void SetCursorPosition(INT32 x, INT32 y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

BinarySearchTree::BinarySearchTree()
{
    nil = new Node(); // Black
    root = nil;
}

BinarySearchTree::~BinarySearchTree()
{
    delete nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
    if (node == nil)
        return;

    SetCursorPosition(x, y);

    if (node->color == Color::Black)
        SetCursorColor(ConsoleColor::BLUE);
    else
        SetCursorColor(ConsoleColor::RED);

    cout << node->key;
    Print(node->left, x - (5 / (y + 1)), y + 1);
    Print(node->right, x + (5 / (y + 1)), y + 1);

    SetCursorColor(ConsoleColor::WHITE);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
    if (node == nil || key == node->key)
        return node;

    if (key < node->key)
        return Search(node->left, key);
    else
        return Search(node->right, key);
}

Node* BinarySearchTree::Min(Node* node)
{
    while (node->left != nil)
        node = node->left;

    return node;
}

Node* BinarySearchTree::Max(Node* node)
{
    while (node->right != nil)
        node = node->right;

    return node;
}

Node* BinarySearchTree::Next(Node* node)
{
    if (node->right != nil)
        return Min(node->right);

    Node* parent = node->parent;

    while (parent != nil && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void BinarySearchTree::Insert(int key)
{
    Node* newNode = new Node();
    newNode->key = key;

    Node* node = root;
    Node* parent = nil;

    while (node != nil)
    {
        parent = node;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    newNode->parent = parent;

    if (parent == nil)
        root = newNode;
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    // 검사
    newNode->left = nil;
    newNode->right = nil;
    newNode->color = Color::Red;

    InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
    // 1) p = red, uncle = red
    // -> p = black, uncle = black, pp = red로 바꿈
    // 2) p = red, uncle = black (triangle)
    // -> 회전을 통해 case 3으로 바꿈
    // 3) p = red, uncle = black (list)	
    // -> 색상 변경 + 회전

    while (node->parent->color == Color::Red)
    {
        if (node->parent == node->parent->parent->left)
        {
            Node* uncle = node->parent->parent->right;
            if (uncle->color == Color::Red)
            {
                node->parent->color = Color::Black; // p
                uncle->color = Color::Black; // u
                node->parent->parent->color = Color::Red; // pp
                node = node->parent->parent;
            }
            else
            {
                //       [pp(B)]
                //   [p(R)]     [u(B)]
                //      [n(R)]

                //        [pp(B)]
                //      [p(R)]  [u(B)]
                //   [n(R)]   

                if (node == node->parent->right) // Triangle 타입
                {
                    node = node->parent;
                    LeftRotate(node);
                }

                // List 타입

                //        [pp(R)]
                //      [p(B)]  [u(B)]
                //   [n(R)]  

                //       [p(B)]  
                //   [n(R)]   [pp(R)]
                //					[u(B)]
                node->parent->color = Color::Black;
                node->parent->parent->color = Color::Red;
                RightRotate(node->parent->parent);
            }
        }
        else
        {
            Node* uncle = node->parent->parent->left;
            if (uncle->color == Color::Red)
            {
                node->parent->color = Color::Black; // p
                uncle->color = Color::Black; // u
                node->parent->parent->color = Color::Red; // pp
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left) // Triangle 타입
                {
                    node = node->parent;
                    RightRotate(node);
                }

                // List 타입

                //					 [p(B)]    
                //			  [pp(R)]      [n(R)]  
                //      [u(B)] 
                node->parent->color = Color::Black;
                node->parent->parent->color = Color::Red;
                LeftRotate(node->parent->parent);
            }
        }
    }

    root->color = Color::Black;
}

void BinarySearchTree::Delete(int key)
{
    Node* deleteNode = Search(root, key);
    Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr)
        Replace(node, node->right);
    else if (node->right == nullptr)
        Replace(node, node->left);
    else
    {
        Node* next = Next(node);
        node->key = next->key;
        Delete(next);
    }
}

// u 서브 트리를 v 서브 트리로 교체합니다.
// 그리고 delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;

    delete u;
}

//    [x]  
// [1]   [y]
//      [2][3]

//     [y]
//  [x]   [3]
// [1][2]
void BinarySearchTree::LeftRotate(Node* x)
{
    Node* y = x->right;

    // [2] 회전시 겹치게 될 노드를 옮겨줍니다.
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;

    // 회전을 하면 부모가 바뀌게 될 것입니다.
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

//     [y]
//  [x]   [3]
// [1][2]

//    [x]  
// [1]   [y]
//      [2][3]
void BinarySearchTree::RightRotate(Node* y)
{
    Node* x = y->left;

    // [2] 회전시 겹치게 될 노드를 옮겨줍니다.
    y->left = x->right;
    if (x->right != nil)
        x->right->parent = y;

    // 회전을 하면 부모가 바뀌게 될 것입니다.
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}
