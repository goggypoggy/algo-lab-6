#include <iostream>
#include <list>
#include <stack>
#include <vector>

enum class COLOR {
    WHITE,
    GRAY,
    BLACK
};

struct Graph {
    int V = 0;
    int E = 0;

    std::vector<std::vector<int>> neighbours;
    std::vector<COLOR> color;

    bool has_cycle = false;
};

void Visit(Graph& G, int node, int parent) {
    G.color[node] = COLOR::GRAY;
    for (int neighbor : G.neighbours[node]) {
        if (G.color[neighbor] == COLOR::WHITE) {
            Visit(G, neighbor, node);
        } else if (G.color[neighbor] == COLOR::GRAY) {
            if (neighbor != parent) {
                G.has_cycle = true;
            }
        }
    }
    G.color[node] = COLOR::BLACK;
}

void DFS_Cycles(Graph& G) {
    for (int i = 0; i < G.V; ++i) {
        if (G.color[i] == COLOR::WHITE) {
            Visit(G, i, -1);
        }
    }
}

int main(int, char**) {
    Graph G;

    std::cin >> G.V >> G.E;

    G.neighbours.resize(G.V);
    G.color.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        G.neighbours[i] = {};
        G.color[i] = COLOR::WHITE;
    }

    for (int i = 0; i < G.E; ++i) {
        int from;
        int to;

        std::cin >> from >> to;

        G.neighbours[from - 1].push_back(to - 1);
        G.neighbours[to - 1].push_back(from - 1);
    }

    DFS_Cycles(G);

    std::cout << (G.has_cycle ? "YES" : "NO");

    return 0;
}