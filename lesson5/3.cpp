#include <iostream>
#include "Stack_m.h"
#include <algorithm>
#include <utility>
using namespace std;


//Сортировка выбором
//Написать сортировку шаблонного стека с помощью функции из предыдущего задания.

template <typename stack_t>
void selectSort(stack_t& src) {
    stack_t tmp;
    stack_t minimum;

    while (src.size() != 0) {
        extractMin(src, minimum);
        while (minimum.size() != 0) {
            tmp.push(minimum.top());
            minimum.pop();
        }
    }

    src = tmp;
}

int main() {

    Stack_m<int> src;
    for (int i = 1; i < 22; i++)
       src.push(i);
    src.push(1);
    src.push(4);
    src.push(7);

    int n = src.size();
    selectSort(src);
    for (int i = 0; i < n; i++) {
       cout << src.top() << endl;
       src.pop();
    }

    return 0;
}
