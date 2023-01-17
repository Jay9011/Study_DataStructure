#include "Graph.h"

typedef Graph<char> G;

int main()
{
    G graph;

    G::Node* n1 = G::CreateNode('A');
    G::Node* n2 = G::CreateNode('B');
    G::Node* n3 = G::CreateNode('C');
    G::Node* n4 = G::CreateNode('D');
    G::Node* n5 = G::CreateNode('E');

    graph.AddNode(n1);
    graph.AddNode(n2);
    graph.AddNode(n3);
    graph.AddNode(n4);
    graph.AddNode(n5);

    graph.AddEdge(n1, G::CreateEdge(n1, n2));
    graph.AddEdge(n1, G::CreateEdge(n1, n3));
    graph.AddEdge(n1, G::CreateEdge(n1, n4));
    graph.AddEdge(n1, G::CreateEdge(n1, n5));

    graph.AddEdge(n2, G::CreateEdge(n2, n1));
    graph.AddEdge(n2, G::CreateEdge(n2, n3));
    graph.AddEdge(n2, G::CreateEdge(n2, n5));

    graph.AddEdge(n3, G::CreateEdge(n3, n1));
    graph.AddEdge(n3, G::CreateEdge(n3, n2));

    graph.AddEdge(n4, G::CreateEdge(n4, n1));
    graph.AddEdge(n4, G::CreateEdge(n4, n5));

    graph.AddEdge(n5, G::CreateEdge(n5, n1));
    graph.AddEdge(n5, G::CreateEdge(n5, n2));
    graph.AddEdge(n5, G::CreateEdge(n5, n4));

    graph.Print();

    graph.DFS(n1);

    return 0;
}