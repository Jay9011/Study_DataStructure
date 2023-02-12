#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std;

void SetCursorPosition(INT32 x, INT32 y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
    if (node == nullptr)
        return;

    SetCursorPosition(x, y);

    cout << node->key;
    Print(node->left, x - (5 / (y + 1)), y + 1);
    Print(node->right, x + (5 / (y + 1)), y + 1);
}
/*
* 전위 순회 (preorder traverse) : Parent 를 우선 탐색하는 구조
* 중위 순회 (inorder) : Parent 를 중간에 탐색하는 구조
* 후위 순회 (postorder) : Parent 를 나중에 탐색하는 구조
*/
void BinarySearchTree::PrintInorder(Node* node)
{
    if (node == nullptr)
        return;

    cout << node->key << endl;
    PrintInorder(node->left);
    PrintInorder(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
    if (node == nullptr || key == node->key)
        return node;

    if (key < node->key)
        return Search(node->left, key);
    else
        return Search(node->right, key);

}

Node* BinarySearchTree::Search2(Node* node, int key)
{
    while (node && key != node->key)
    {
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    return node;
}

Node* BinarySearchTree::Min(Node* node)
{
    while (node->left)
        node = node->left;

    return node;
}

Node* BinarySearchTree::Max(Node* node)
{
    while (node->right)
        node = node->right;

    return node;
}

Node* BinarySearchTree::Next(Node* node)
{
    if (node->right)
        return Min(node->right);

    Node* parent = node->parent;

    while (parent && node == parent->right)
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

    if (root == nullptr)
    {
        root = newNode;
        return;
    }

    Node* node = root;
    Node* parent = nullptr;

    while (node)
    {
        // 진입할 수 있는 노드가 있으면 해당 노드를 parent 로 바꿉니다.
        parent = node;

        // key 를 기준으로 작으면 왼쪽으로, 크면 오른쪽으로 이동합니다.
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    // 추가 할 위치에 parent 와 자기 자신을 연결합니다.
    newNode->parent = parent;

    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
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
