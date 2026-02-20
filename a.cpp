#include <iostream>
#include <list>
#include <stack>
#include <vector>

struct Graph {
    int V = 0;
    int E = 0;

    std::vector<std::vector<int>> neighbours;
    std::vector<int> cc;
};

enum class COLOR {
    WHITE,
    GRAY,
    BLACK
};

std::stack<int, std::list<int>> v;
std::vector<COLOR> color;
std::vector<int> nb_mem;

void DFS_Launch(Graph& G, int start_node, int cur_cc) {
    for (int i = 0; i < G.V; ++i) {
        color[i] = COLOR::WHITE;
        nb_mem[i] = 0;
    }
    
    v.push(start_node);
    color[start_node] = COLOR::GRAY;

    while (!v.empty()) {
        int top = v.top();
        G.cc[top] = cur_cc;
        bool added_new = false;

        while (nb_mem[top] < G.neighbours[top].size()) {
            int new_neighbor = G.neighbours[top][nb_mem[top]];
            
            if (color[new_neighbor] == COLOR::WHITE) {
                v.push(new_neighbor);
                color[new_neighbor] = COLOR::GRAY;
                added_new = true;
                break;   
            }

            ++nb_mem[top];
        }

        if (!added_new) {
            color[top] = COLOR::BLACK;
            v.pop();
        }
    }
}

int DFS_CC(Graph& G) {
    int total_cc = 0;

    color.resize(G.V);
    nb_mem.resize(G.V);

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

    G.neighbours.resize(G.V);
    G.cc.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        G.neighbours[i] = {};
        G.cc[i] = 0;
    }

    for (int i = 0; i < G.E; ++i) {
        int from;
        int to;

        std::cin >> from >> to;

        G.neighbours[from - 1].push_back(to - 1);
        G.neighbours[to - 1].push_back(from - 1);
    }

    std::cout << DFS_CC(G);

    return 0;
}