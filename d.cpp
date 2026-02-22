#include <algorithm>
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
};

std::vector<int> toposort = {};

void Visit(Graph& G, int node) {
    G.color[node] = COLOR::GRAY;
    for (int neighbor : G.neighbours[node]) {
        if (G.color[neighbor] == COLOR::WHITE) {
            Visit(G, neighbor);
        }
    }
    G.color[node] = COLOR::BLACK;

    toposort.push_back(node);
}

void DFS(Graph& G) {
    for (int i = 0; i < G.V; ++i) {
        if (G.color[i] == COLOR::WHITE) {
            Visit(G, i);
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
    }

    DFS(G);

    std::reverse(toposort.begin(), toposort.end());

    std::vector<int> output;
    output.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        output[toposort[i]] = i;
    }

    for (int i = 0; i < output.size(); ++i) {
        std::cout << output[i] + 1 << (i == output.size() - 1 ? "" : " ");
    }

    return 0;
}