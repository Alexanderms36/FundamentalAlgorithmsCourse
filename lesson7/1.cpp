#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "Stack_m.h"

using namespace std;

//Поиск эйлерова пути в графе
//Пусть граф задан с помощью списков смежности.
//Написать функцию, возвращающую эйлеров путь в заданном графе, если таковой есть.

bool hasPath(vector<vector<int>> gr) {
    size_t сount = 0;
    for (auto elem : gr) {
        if (elem.size() % 2 != 0) 
            сount++;
    }
    return сount <= 2;
}

vector<int> getEulerPath(vector<vector<int>> gr) {
    if (!hasPath(gr))
        return {};

    vector<int> path;
    Stack_m<int> s;
    
    size_t countVs = 0, indexVs = 0;

    for (size_t i = 0; i < gr.size(); i++) {
        if (gr[i].size() % 2 != 0) {
            countVs++;
            indexVs = i;
        }
    }

    if (countVs == 2)
        s.push(indexVs);
    else
        s.push(0);

    while (s.size() != 0) {
        int v = s.top();
        
        if (gr[v].size() != 0) {
            int u = gr[v].back();
            gr[v].pop_back();
            auto it = find(gr[u].begin(), gr[u].end(), v);
            if (it != gr[u].end())
                gr[u].erase(it);
            s.push(u);
        } else {
            path.push_back(v);
            s.pop();
        }
    }

    reverse(path.begin(), path.end());
    return path;
}

//Написать функцию, которая по заданному графу выдаёт минимальный список рёбер, добавление которых делает этот граф эйлеровым.
vector<pair<size_t, size_t>> findEdges(vector<vector<int>> gr) {

    vector<pair<size_t, size_t>> newEdges;
    vector<size_t> odds;

    for (size_t i = 0; i < gr.size(); i++) {
        if (gr[i].size() % 2 != 0)
            odds.push_back(i);
    }

    for (size_t i = 0; i < odds.size() - 1; i += 2) {
        auto edge = make_pair(odds[i], odds[i + 1]);
        newEdges.push_back(edge);
    }

    return newEdges;
}

int main() {
    int n = 5;
    vector<vector<int>> gr(n);

    gr[0] = { 1, 3 };
    gr[1] = { 0, 2 };
    gr[2] = { 1, 3 };
    gr[3] = { 0, 2, 4 };
    gr[4] = { 3 };
 
    vector<int> s = getEulerPath(gr);
    auto ep = findEdges(gr);

    for (size_t i = 0; i < ep.size(); i++) {
        cout << i << " " << ep[i].first << " " << ep[i].second << endl;
    }

    return 0;
}
