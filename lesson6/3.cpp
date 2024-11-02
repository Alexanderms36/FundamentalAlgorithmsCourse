#include <iostream>
#include <vector>
#include "Stack_m.h"

using namespace std;

//3)
//Наиболее частые элементы
//Написать функции, которые в данном наборе элементов находят элемент, который
//встречается больше половины раз;
// 
//Про тип элементов известно только то, что в нём реализована операция == .
//Сложность итогового алгоритма должна быть линейной.

template <typename T>
T getMajor(vector<T> src) {
    Stack_m<T> s;
    for (auto elem : src) {
        if (s.size() == 0)
            s.push(elem);

        if (s.size() != 0) {
            if (s.top() == elem)
                s.push(elem);
            else
                s.pop();
        }
    }

    size_t count = 0;

    if (s.size() == 0) return count;

    for (auto elem : src) {
        if (s.top() == elem)
            count++;
    }

    if (count > src.size() / 2) return s.top();
    return -1;
}

int main() {
    vector<char> vec = { 'a', 'a', 'a', '4', 'a' };
    cout << getMajor(vec);
}
