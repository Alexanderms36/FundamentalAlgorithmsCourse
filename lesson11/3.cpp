#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <functional>
#include <numeric>
#include <map>

using namespace std;

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

//3) Расшифровка кода Прюфера
//Написать функцию, восстанавливающую дерево по коду Прюфера по лекционному алгоритму.
//В реализации разрешается использовать только вектора

vector<vector<size_t>> pruferRestore(vector<size_t> seq) {
    size_t seq_size = seq.size();
    size_t n = seq_size + 2;
    vector<vector<size_t>> gr(n);
    vector<size_t> s(n);

    for (size_t i = 0; i < s.size(); i++)
        s[i] = i;
    

    for (size_t i = 0; i < seq_size; i++) {
        size_t a = seq[i];
        size_t b;
        for (size_t j = 0; j < s.size(); j++) {
            bool isThere = false;
            for (size_t k = i; k < seq_size; k++) {
                if (seq[k] == s[j]) {
                    isThere = true;
                    break;
                }

            }
            if (!isThere) {
                b = s[j];
                break;
            }
        }
        gr[a].push_back(b);
        gr[b].push_back(a);

        auto b_ind = find(s.begin(), s.end(), b);
        s.erase(b_ind);

    }
    gr[s[0]].push_back(s[1]);
    gr[s[1]].push_back(s[0]);
    return gr;
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

    auto seq = pruferSequence(gr);
    auto T = pruferRestore(seq);
    
    for (size_t i = 0; i < T.size(); i++) {
        (T[0] == gr[0]) ? cout << "yes" : cout << "no";
        cout << endl;
    }

    return 0;
}
