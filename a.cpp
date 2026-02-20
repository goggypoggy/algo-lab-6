#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>

struct Graph {
    int V = 0;
    int E = 0;

    std::vector<std::vector<int>> neighbours;
    std::vector<bool> visited;
};


std::queue<int> q;

void BFS_Launch(Graph& G, int start_node) {
    q.push(start_node);
    G.visited[start_node] = true;

    while (!q.empty()) {
        int front = q.front();
        q.pop();
        
        for (int neighbor : G.neighbours[front]) {
            if (!G.visited[neighbor]) {
                q.push(neighbor);
                G.visited[neighbor] = true;
            }
        }
    }
}

int BFS_CC(Graph& G) {
    int total_cc = 0;

    for (int i = 0; i < G.V; ++i) {
        if (G.visited[i] == false) {
            ++total_cc;
            BFS_Launch(G, i);
        }
    }

    return total_cc;
}

int main(int, char**) {
    Graph G;

    std::cin >> G.V >> G.E;

    G.neighbours.resize(G.V);
    G.visited.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        G.neighbours[i] = {};
        G.visited[i] = false;
    }

    for (int i = 0; i < G.E; ++i) {
        int from;
        int to;

        std::cin >> from >> to;

        G.neighbours[from - 1].push_back(to - 1);
        G.neighbours[to - 1].push_back(from - 1);
    }

    std::cout << BFS_CC(G);

    return 0;
}