#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

//3) Код Прюфера
//Написать функцию, которая по спискам смежности 
//некорневого неориентированного дерева строит код Прюфера этого дерева
//(по лекционному алгоритму).

vector<size_t> pruferSequence(vector<vector<size_t>> T) {
    vector<size_t> seq;
    size_t size = T.size();

    for (size_t i = 0; i < size - 2; i++) {
        size_t v, u;
        for (size_t j = 0; j < T.size(); j++) {
            if (T[j].size() == 1) {
                v = j;
                u = T[v][0];
                break;
            }
        }
        seq.push_back(u);
        T[v].clear();
        auto uv = find(T[u].begin(), T[u].end(), v);
        T[u].erase(uv);
    }
    return seq;
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
    auto vec1 = pruferSequence(gr);
    for (auto v : vec1) {
        cout << v << " ";
    }

}
