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

std::vector<int> v;
std::vector<int> nb_mem;

void Output(Graph& G) {
    for (int i = 0; i < G.V; ++i) {
        std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < G.V; ++i) {
        char letter = '@';
        switch (G.color[i]) {
            case COLOR::WHITE:
                letter = 'W';
            break;
            case COLOR::GRAY:
                letter = 'G';
            break;
            case COLOR::BLACK:
                letter = 'B';
            break;
        }

        std::cout << letter << ' ';
    }
    std::cout << std::endl;
}

bool DFS_Launch(Graph& G, int start_node) {
    for (int i = 0; i < G.V; ++i) {
        nb_mem[i] = 0;
    }
    
    v.push_back(start_node);
    G.color[start_node] = COLOR::GRAY;

    while (v.size() > 0) {
        int top = v[v.size() - 1];
        bool added_new = false;
        
        //std::cout << top + 1 << std::endl;
        //Output(G);

        while (nb_mem[top] < G.neighbours[top].size()) {
            int new_neighbor = G.neighbours[top][nb_mem[top]];
            
            if (G.color[new_neighbor] == COLOR::WHITE) {
                v.push_back(new_neighbor);
                G.color[new_neighbor] = COLOR::GRAY;
                added_new = true;
                break;   
            } else if (G.color[new_neighbor] == COLOR::GRAY) {
                if (v.size() >= 2) {
                    int parent = v[v.size() - 2];
                    if (new_neighbor != parent) {
                        return true;
                    }
                }
            }

            ++nb_mem[top];
        }

        if (!added_new) {
            G.color[top] = COLOR::BLACK;
            v.pop_back();
        }
    }

    return false;
}

bool DFS_Cycles(Graph& G) {
    v.reserve(G.V);
    nb_mem.resize(G.V);

    for (int i = 0; i < G.V; ++i) {
        if (G.color[i] == COLOR::WHITE) {
            if (DFS_Launch(G, i)) {
                return true;
            }
        }
    }

    return false;
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

    std::cout << (DFS_Cycles(G) ? "YES" : "NO");

    return 0;
}