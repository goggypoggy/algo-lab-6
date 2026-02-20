#include <iostream>
#include <vector>

struct Graph {
    int V = 0;
    int E = 0;

    std::vector<std::vector<int>> neighbours;
    std::vector<int> cc;
};

void DFS_Launch(Graph& G, int cur_node, int cur_cc) {
    G.cc[cur_node] = cur_cc;

    for (int next_node : G.neighbours[cur_node]) {
        DFS_Launch(G, next_node, cur_cc);
    }
}

int DFS_CC(Graph& G) {
    int total_cc = 0;
    for (int i = 0; i < G.V; ++i) {
        if (G.cc[i] == 0) {
            ++total_cc;
            DFS_Launch(G, i, total_cc);
        }
    }

    return total_cc;
}

int main(int, char**) {
    Graph G;

    std::cin >> G.V >> G.E;

    for (int i = 0; i < G.V; ++i) {
        G.neighbours.push_back({});
        G.cc.push_back(0);
    }

    for (int i = 0; i < G.E; ++i) {
        int from;
        int to;

        std::cin >> from >> to;

        G.neighbours[from - 1].push_back(to);
    }

    std::cout << DFS_CC(G);

    return 0;
}