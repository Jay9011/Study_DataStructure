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
* ���� ��ȸ (preorder traverse) : Parent �� �켱 Ž���ϴ� ����
* ���� ��ȸ (inorder) : Parent �� �߰��� Ž���ϴ� ����
* ���� ��ȸ (postorder) : Parent �� ���߿� Ž���ϴ� ����
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
        // ������ �� �ִ� ��尡 ������ �ش� ��带 parent �� �ٲߴϴ�.
        parent = node;

        // key �� �������� ������ ��������, ũ�� ���������� �̵��մϴ�.
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    // �߰� �� ��ġ�� parent �� �ڱ� �ڽ��� �����մϴ�.
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

// u ���� Ʈ���� v ���� Ʈ���� ��ü�մϴ�.
// �׸��� delete u
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
