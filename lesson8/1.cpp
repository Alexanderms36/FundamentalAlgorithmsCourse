#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

//1)
//Быстрая сортировка стека.v2
//Многие "справились" с написание быстрой сортировки стеков из прошлого дз.
//Но все показанные мне реализации имели один существенный недостаток :
//они не могут отсортировать исходно отсортированный стек с большим(~50т) количеством элементов(проверьте!).
//Проанализировать и выявить корень проблемы.
//Реализовать небольшую модификацию(на 4 - 5 строк) имеющегося алгоритма, решающую описанную проблему.
//template <typename stack_t>
//void quick_stack_sort(stack_t& src)

template <typename stack_t>
void invert(stack_t& src) {
    stack_t tmp;
    while (src.size() != 0) {
        tmp.push(src.top());
        src.pop();
    }
    src = tmp;
}

template <typename stack_t>
void fillStack(stack_t& s, int size) {
    for (int i = 0; i < size; ++i) {
        s.push(rand() % 50000);
    }
}

template <typename stack_t>
void printStack(stack_t s) {
    cout << "stack size: " << s.size() << endl;
    stack_t temp = s;
    while (temp.size() > 0) {
        cout << temp.top() << endl;
        temp.pop();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

}

template <typename stack_t>
void quickStackSort(stack_t& src) {
    if (src.size() <= 1) {
        return;
    }

    stack_t temp;

    srand(static_cast<unsigned>(time(nullptr)));
    size_t index = rand() % src.size();

    //random_device rd;
    //mt19937_64 mtrand(rd());
    //size_t k = mtrand() % src.size();

    if (index == 0) {
        temp.push(src.top());
        src.pop();
    } else {
        for (size_t i = 0; i < index; ++i) {
            temp.push(src.top());
            src.pop();
        }
    }
    auto el = temp.top();

    stack_t higher, lower, equal;

    while (!temp.empty()) {
        src.push(temp.top());
        temp.pop();
    }

    while (src.size() != 0) {
        if (src.top() > el)
            higher.push(src.top());
        else if (src.top() < el)
            lower.push(src.top());
        else
            equal.push(src.top());
        src.pop();
    }

    quickStackSort(higher);
    quickStackSort(lower);

    invert(higher);
    invert(lower);

    while (higher.size() != 0) {
        src.push(higher.top());
        higher.pop();
    }

    while (equal.size() != 0) {
        src.push(equal.top());
        equal.pop();
    }

    while (lower.size() != 0) {
        src.push(lower.top());
        lower.pop();
    }
}
