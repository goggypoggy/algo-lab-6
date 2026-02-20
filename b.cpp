#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>

struct Graph {
    int V = 0;
    int E = 0;

    std::vector<std::vector<int>> neighbours;
    std::vector<int> d;
};


std::queue<int> q;

void BFS_Launch(Graph& G, int start_node) {
    q.push(start_node);
    G.d[start_node] = 0;

    while (!q.empty()) {
        int front = q.front();
        q.pop();
        
        for (int neighbor : G.neighbours[front]) {
            if (G.d[neighbor] == -1) {
                q.push(neighbor);
                G.d[neighbor] = G.d[front] + 1;
            }
        }
    }
}

int main(int, char**) {
    Graph G;

    int K;
    std::cin >> G.V >> G.E >> K;

    G.neighbours.resize(G.V);
    G.d.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        G.neighbours[i] = {};
        G.d[i] = -1;
    }

    for (int i = 0; i < G.E; ++i) {
        int from;
        int to;

        std::cin >> from >> to;

        G.neighbours[from - 1].push_back(to - 1);
        G.neighbours[to - 1].push_back(from - 1);
    }

    BFS_Launch(G, 0);

    std::vector<int> result;

    for (int i = 0; i < G.V; ++i) {
        if (G.d[i] == K) {
            result.push_back(i);
        }
    }

    if (result.size() == 0) {
        std::cout << "NO";
    } else {
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i] + 1 << (i == result.size() - 1 ? "" : "\n");
        }
    }

    return 0;
}