#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//1) Поиск в ширину
//Написать функцию, которая по графу, заданному списками смежности, 
//и стартовой вершине возвращает массив глубин d и массив предков p с помощью поиска в ширину.

pair<vector<size_t>, vector<int>> graphDepthAndParent(vector<vector<size_t>> G, size_t s) {
    size_t n = G.size();
    vector<size_t> d(n, 9999999);
    vector<int> p(n, -1);

    d[s] = 0;
    queue<size_t> q;
    q.push(s);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto v : G[u]) {
            if (d[v] == 9999999) {
                d[v] = d[u] + 1;
                q.push(v);
                p[v] = u;
            }
        }
    }
    
    return { d, p };
}

//Написать следующие функции с применением базового поиска в ширину:
//подсчёт количества двудольных компонент связности

size_t countBipartiteComponents(vector<vector<size_t>> G) {
    size_t n = G.size();
    vector<size_t> d(n, 9999999);
    vector<int> p(n, -1);
    size_t count = 0;

    for (size_t s = 0; s < n; s++) {
        if (d[s] == 9999999) {
            d[s] = 0;
            queue<size_t> q;
            q.push(s);
            bool bipartite = true;
            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                for (auto v : G[u]) {
                    if (d[v] == 9999999) {
                        d[v] = d[u] + 1;
                        q.push(v);
                        p[v] = u;
                    } else if ((d[u] + d[v]) % 2 == 0) {
                        bipartite = false;
                    }
                }
            }
            if (bipartite) ++count;
        }
    }

    return count;
}

int main() {
    vector<vector<size_t>> gr = {
       {6, 2, 8, 11},
       {11, 4, 12},
       {0, 7},
       {11, 10, 9},
       {5, 13, 1},
       {4},
       {0},
       {2},
       {0},
       {3},
       {3},
       {0, 3, 1},
       {1},
       {4}
    };

    auto a = graphDepthAndParent(gr, 0);
    auto b1 = a.first;
    auto b2 = a.second;
    for (auto v : b1) {
       cout << v << " ";
    }

	return 0;
}
