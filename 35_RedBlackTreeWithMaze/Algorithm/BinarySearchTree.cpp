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

// 먼저 BST 삭제를 실행합니다.
void BinarySearchTree::Delete(Node* node)
{
    if (node == nil)
        return;

    if (node->left == nil)
    {
        Color color = node->color;
        Node* right = node->right;
        Replace(node, node->right);

        // 삭제한 노드의 컬러가 Black 인 경우 재검사를 실행합니다.
        if (color == Color::Black)
            DeleteFixup(right);
    }
    else if (node->right == nil)
    {
        Color color = node->color;
        Node* right = node->left;
        Replace(node, node->left);

        // 삭제한 노드의 컬러가 Black 인 경우 재검사를 실행합니다.
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

// 먼저 BST 삭제 실행...
// - Case1) 삭제할 노드가 Red -> 그냥 삭제! 끝!
// - Case2) root가 DB -> 그냥 추가 Black 삭제! 끝!
// - Case3) DB의 sibling 노드가 Red
// -- s = black, p = red (s <-> p 색상 교환)
// -- DB 방향으로 rotate(p) 
// -- goto other case
// - Case4) DB의 sibling 노드가 Black && sibling의 양쪽 자식도 Black
// -- 추가 Black을 parent에게 이전
// --- p가 Red이면 Black 됨.
// --- p가 Black이면 DB 됨.
// -- s = red
// -- p를 대상으로 알고리즘 이어서 실행 (DB가 여전히 존재하면)
// - Case5) DB의 sibling 노드가 Black && sibling의 near child = red, far child = black
// -- s <-> near 색상 교환
// -- far 방향으로 rotate(s)
// -- goto case 6
// - Case6) DB의 sibling 노드가 Black && sibling의 far child = red
// - p <-> s 색상 교환
// - far = black
// - rotate(p) (DB 방향으로)
// - 추가 Black 제거
void BinarySearchTree::DeleteFixup(Node* node)
{
    Node* x = node;

    // [Case1][Case2]
    while (x != root && x->color == Color::Black)
    {
        // 삭제하려는 노드가 Parent 의 Left 에 있는 경우
        if (x == x->parent->left)
        {
            // [Case3]
            // Sibling 노드 정보를 가져옵니다.
            Node* s = x->parent->right;

            // Sibling 이 Red 인 경우
            //      [p(B)]
            // [x(DB)]  [s(R)]
            if (s->color == Color::Red)
            {
                // Parent 를 Red 로 만들고 Sibling 을 Black으로 만들어 줍니다.
                // (Sibling 이 Red 였다면 규칙에 의해 Parent 가 Black 이었을 것이기 때문에)
                //      [p(R)]
                // [x(DB)]  [s(B)]
                //         [1]
                s->color = Color::Black;
                x->parent->color = Color::Red;

                // Left 회전을 통해
                //			[s(B)]
                //      [p(R)]
                // [x(DB)]  [1] 
                LeftRotate(x->parent);

                s = x->parent->right; // [1] 로 Sibling 교체
            }

            // [Case4]
            if (s->left->color == Color::Black && s->right->color == Color::Black)
            {
                s->color = Color::Red;
                x = x->parent;
            }
            // Sibling 의 자식 중 하나라도 Red 인 경우
            else
            {
                // [Case5]
                // Sibling 의 한 쪽 자식이 Red 라면 Black 의 개수가 맞지 않아
                // 균형이 유지되지 않고 있을 수 있다는 것이므로
                //          [p]
                // [x(DB)]       [s(B)]
                //         [near(R)][far(B)]
                if (s->right->color == Color::Black)
                {
                    //         [p]
                    // [x(DB)]    [near(B)]
                    //				  [s(R)]
                    //					 [far(B)]
                    s->left->color = Color::Black; // 균형을 바꾸기 위해 자식을 Black 으로 바꾸고
                    s->color = Color::Red; // 자신을 Red 로 바꾼 다음에

                    RightRotate(s); // Right 회전을 통해 균형을 바꿉니다.

                    s = x->parent->right; // [near] 로 Sibling 교체
                }

                // [Case6]
                s->color = x->parent->color;
                x->parent->color = Color::Black;
                s->right->color = Color::Black;
                LeftRotate(x->parent);
                x = root;
            }
        }
        // 삭제하려는 노드가 Parent 의 Right 에 있는 경우
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

    // 최종적으로 Black 이 됩니다.
    x->color = Color::Black;
}

// u 서브 트리를 v 서브 트리로 교체합니다.
// 그리고 delete u
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
