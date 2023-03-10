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

void ShowConsoleCursor(bool flag)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = flag;
    SetConsoleCursorInfo(output, &cursorInfo);
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

void BinarySearchTree::Print()
{
    system("cls");
    ShowConsoleCursor(false);
    Print(root, 10, 0);
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

    // ????
    newNode->left = nil;
    newNode->right = nil;
    newNode->color = Color::Red;

    InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
    // 1) p = red, uncle = red
    // -> p = black, uncle = black, pp = red?? ????
    // 2) p = red, uncle = black (triangle)
    // -> ?????? ???? case 3???? ????
    // 3) p = red, uncle = black (list)	
    // -> ???? ???? + ????

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

                if (node == node->parent->right) // Triangle ????
                {
                    node = node->parent;
                    LeftRotate(node);
                }

                // List ????

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
                if (node == node->parent->left) // Triangle ????
                {
                    node = node->parent;
                    RightRotate(node);
                }

                // List ????

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

// ???? BST ?????? ??????????.
void BinarySearchTree::Delete(Node* node)
{
    if (node == nil)
        return;

    if (node->left == nil)
    {
        Color color = node->color;
        Node* right = node->right;
        Replace(node, node->right);

        // ?????? ?????? ?????? Black ?? ???? ???????? ??????????.
        if (color == Color::Black)
            DeleteFixup(right);
    }
    else if (node->right == nil)
    {
        Color color = node->color;
        Node* right = node->left;
        Replace(node, node->left);

        // ?????? ?????? ?????? Black ?? ???? ???????? ??????????.
        if (color == Color::Black)
            DeleteFixup(right);
    }
    else
    {
        Node* next = Next(node);
        node->key = next->key;
        Delete(next);
    }
}

// ???? BST ???? ????...
// - Case1) ?????? ?????? Red -> ???? ????! ??!
// - Case2) root?? DB -> ???? ???? Black ????! ??!
// - Case3) DB?? sibling ?????? Red
// -- s = black, p = red (s <-> p ???? ????)
// -- DB ???????? rotate(p) 
// -- goto other case
// - Case4) DB?? sibling ?????? Black && sibling?? ???? ?????? Black
// -- ???? Black?? parent???? ????
// --- p?? Red???? Black ??.
// --- p?? Black???? DB ??.
// -- s = red
// -- p?? ???????? ???????? ?????? ???? (DB?? ?????? ????????)
// - Case5) DB?? sibling ?????? Black && sibling?? near child = red, far child = black
// -- s <-> near ???? ????
// -- far ???????? rotate(s)
// -- goto case 6
// - Case6) DB?? sibling ?????? Black && sibling?? far child = red
// - p <-> s ???? ????
// - far = black
// - rotate(p) (DB ????????)
// - ???? Black ????
void BinarySearchTree::DeleteFixup(Node* node)
{
    Node* x = node;

    // [Case1][Case2]
    while (x != root && x->color == Color::Black)
    {
        // ?????????? ?????? Parent ?? Left ?? ???? ????
        if (x == x->parent->left)
        {
            // [Case3]
            // Sibling ???? ?????? ??????????.
            Node* s = x->parent->right;

            // Sibling ?? Red ?? ????
            //      [p(B)]
            // [x(DB)]  [s(R)]
            if (s->color == Color::Red)
            {
                // Parent ?? Red ?? ?????? Sibling ?? Black???? ?????? ??????.
                // (Sibling ?? Red ?????? ?????? ???? Parent ?? Black ?????? ?????? ??????)
                //      [p(R)]
                // [x(DB)]  [s(B)]
                //         [1]
                s->color = Color::Black;
                x->parent->color = Color::Red;

                // Left ?????? ????
                //			[s(B)]
                //      [p(R)]
                // [x(DB)]  [1] 
                LeftRotate(x->parent);

                s = x->parent->right; // [1] ?? Sibling ????
            }

            // [Case4]
            if (s->left->color == Color::Black && s->right->color == Color::Black)
            {
                s->color = Color::Red;
                x = x->parent;
            }
            // Sibling ?? ???? ?? ???????? Red ?? ????
            else
            {
                // [Case5]
                // Sibling ?? ?? ?? ?????? Red ???? Black ?? ?????? ???? ????
                // ?????? ???????? ???? ???? ?? ?????? ????????
                //          [p]
                // [x(DB)]       [s(B)]
                //         [near(R)][far(B)]
                if (s->right->color == Color::Black)
                {
                    //         [p]
                    // [x(DB)]    [near(B)]
                    //				  [s(R)]
                    //					 [far(B)]
                    s->left->color = Color::Black; // ?????? ?????? ???? ?????? Black ???? ??????
                    s->color = Color::Red; // ?????? Red ?? ???? ??????

                    RightRotate(s); // Right ?????? ???? ?????? ????????.

                    s = x->parent->right; // [near] ?? Sibling ????
                }

                // [Case6]
                s->color = x->parent->color;
                x->parent->color = Color::Black;
                s->right->color = Color::Black;
                LeftRotate(x->parent);
                x = root;
            }
        }
        // ?????????? ?????? Parent ?? Right ?? ???? ????
        else
        {
            // [Case3]
            Node* s = x->parent->left;
            if (s->color == Color::Red)
            {
                s->color = Color::Black;
                x->parent->color = Color::Red;
                RightRotate(x->parent);
                s = x->parent->left; // [1]
            }

            // [Case4]
            if (s->right->color == Color::Black && s->left->color == Color::Black)
            {
                s->color = Color::Red;
                x = x->parent;
            }
            else
            {
                // [Case5]
                if (s->left->color == Color::Black)
                {
                    s->right->color = Color::Black;
                    s->color = Color::Red;
                    LeftRotate(s);
                    s = x->parent->left;
                }

                // [Case6]
                s->color = x->parent->color;
                x->parent->color = Color::Black;
                s->left->color = Color::Black;
                RightRotate(x->parent);
                x = root;
            }
        }//end if(node->parent->left|right)
    }

    // ?????????? Black ?? ??????.
    x->color = Color::Black;
}

// u ???? ?????? v ???? ?????? ??????????.
// ?????? delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

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

    // [2] ?????? ?????? ?? ?????? ??????????.
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;

    // ?????? ???? ?????? ?????? ?? ????????.
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

    // [2] ?????? ?????? ?? ?????? ??????????.
    y->left = x->right;
    if (x->right != nil)
        x->right->parent = y;

    // ?????? ???? ?????? ?????? ?? ????????.
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
