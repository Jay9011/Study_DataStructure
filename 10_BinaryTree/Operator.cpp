#include <string>
#include "BinaryTree.h"

void Expression(const char* postfix, BTree<char>::Node** node)
{
    char* str = const_cast<char*>(postfix);

    size_t length = strlen(str);
    char token = str[length - 1];
    str[length - 1] = '\0';

    switch (token)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    {
        *node = BTree<char>::CreateNode(token);

        Expression(postfix, &(*node)->Right);
        Expression(postfix, &(*node)->Left);
    }
        break;

    default:
    {
        *node = BTree<char>::CreateNode(token);
    }
        break;
    }
}

float Evaluate(BTree<char>::Node* node)
{
    if (node == nullptr)
        return 0.0f;

    switch (node->Data)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    {
        float left = Evaluate(node->Left);
        float right = Evaluate(node->Right);

        // 연산 시작
        switch (node->Data)
        {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        case '%':
            return (int)left % (int)right;
        }
    }
    break;

    default:
    {
        char temp[4];
        memset(temp, 0, sizeof(temp));

        temp[0] = node->Data;

        return atof(temp);
    }
    break;
    }

    return 0.0f;
}

int main()
{
    BTree<char>::Node* root = nullptr;

    string postfix = "34*12+32/+-";
    Expression(postfix.c_str(), &root);

    BTree<char> tree;
    tree.Root(root);

    cout << "-- Pre Order --" << endl;
    tree.PreOrder(root);
    cout << endl;
    cout << endl;
    
    cout << "-- In Order --" << endl;
    tree.InOrder(root);
    cout << endl;
    cout << endl;
    
    cout << "-- Post Order --" << endl;
    tree.PostOrder(root);
    cout << endl;
    cout << endl;

    cout << Evaluate(root) << endl;

    return 0;
}