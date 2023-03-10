#include "Graph.h"

typedef Graph<char> G;

int main()
{
    G graph;

    G::Node* A = G::CreateNode('A');
    G::Node* B = G::CreateNode('B');
    G::Node* C = G::CreateNode('C');
    G::Node* D = G::CreateNode('D');
    G::Node* E = G::CreateNode('E');
    G::Node* F = G::CreateNode('F');
    G::Node* G = G::CreateNode('G');
    G::Node* H = G::CreateNode('H');
    G::Node* I = G::CreateNode('I');

    graph.AddNode(A);
    graph.AddNode(B);
    graph.AddNode(C);
    graph.AddNode(D);
    graph.AddNode(E);
    graph.AddNode(F);
    graph.AddNode(G);
    graph.AddNode(H);
    graph.AddNode(I);

    graph.AddEdge(A, G::CreateEdge(A, E, 247));

    graph.AddEdge(B, G::CreateEdge(B, A, 35));
    graph.AddEdge(B, G::CreateEdge(B, C, 126));
    graph.AddEdge(B, G::CreateEdge(B, F, 150));

    graph.AddEdge(C, G::CreateEdge(C, D, 117));
    graph.AddEdge(C, G::CreateEdge(C, F, 162));
    graph.AddEdge(C, G::CreateEdge(C, G, 220));

    graph.AddEdge(E, G::CreateEdge(E, H, 98));

    graph.AddEdge(F, G::CreateEdge(F, E, 82));
    graph.AddEdge(F, G::CreateEdge(F, G, 154));
    graph.AddEdge(F, G::CreateEdge(F, H, 120));

    graph.AddEdge(G, G::CreateEdge(G, I, 106));

    Graph<char> dijkstra;
    cout << "다익스트라 알고리즘" << endl;
    graph.Dijkstra(B, &dijkstra);
    dijkstra.Print();

    return 0;
}