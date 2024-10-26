#include <iostream>
#include "Stack_m.h"
#include <algorithm>
#include <utility>
using namespace std;


//Извлечение минимума из шаблонного стека
//Написать шаблонную функцию, извлекающую из стека минимальные элементы и перекладывающую их в другой стек.
//Порядок элементов в исходном стеке после извлечения должен остаться прежним.
//Для хранения элементов разрешается использовать только стеки типа stack_t
//template <typename stack_t>
//void extract_min(stack_t& src, stack_t& dest)

template <typename stack_t>
void extractMin(stack_t& src, stack_t& dest) {
    stack_t tmp;
    auto minElement = src.top();

    while (src.size() != 0) {
        if (src.top() < minElement)
            minElement = src.top();
        
        tmp.push(src.top());
        src.pop();
    }

    while (tmp.size() != 0) {
        if (tmp.top() != minElement)
            src.push(tmp.top());
        else
            dest.push(minElement);

        tmp.pop();
    }
}

int main() {

    Stack_m<int> src, dest;
    for (int i = 1; i < 20; i++) {
       src.push(i);
    }
    src.push(1);
    extractMin(src, dest);
    
    int n = dest.size();
    cout << src.size() << endl;

    cout << n << endl;
    for (int i = 0; i < n; i++) {
       cout << dest.top() << endl;
       dest.pop();
    }
    cout << "src stack: " << endl;
    n = src.size();
    for (int i = 0; i < n; i++) {
       cout << src.top() << endl;
       src.pop();
    }
    for (int i = 0; i < n; i++) {
       cout << dest.top() << endl;
       dest.pop();
    }
    return 0;
}
