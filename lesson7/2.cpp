#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "Stack_m.h"

using namespace std;


//3) Быстрая сортировка стека
//Написать шаблонную функцию, сортирующую переданный ей стек с помощью идеи быстрой сортировки.Схема алгоритма :
//Выбираем из исходного стека один элемент, называемый опорным.Далее распределяем все элементы исходного стека по трём вспомогательным :
//первый содержит элементы строго больше опорного,
//второй - строго меньше,
//третий - равные опорному.
//Рекурсивно сортируем большие и малые элементы, после чего в правильном порядке перегоняем вспомогательные стеки в исходный стек,
//чтобы получилась отсортированная последовательность.

template <typename stack_t>
void quickStackSort(stack_t& src) {
    if (src.size() <= 1) {
        return;
    }
    auto el = src.top();
    stack_t higher, lower, equal;

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

    if (higher.size() != 0) {
        while (higher.size() != 0) {
            src.push(higher.top());
            higher.pop();
        }
    }

    while (equal.size() != 0) {
        src.push(equal.top());
        equal.pop();
    }

    if (lower.size() != 0) {
        while (lower.size() != 0) {
            src.push(lower.top());
            lower.pop();
        }
    }
}

//Реализовать сортировку по описанной выше схеме, но уже с выбором двух опорных элементов.

template <typename stack_t>
void quickStackSort2Els(stack_t& src) {
    if (src.size() <= 1) {
        return;
    }

    auto el1 = src.top(); //min
    src.pop();
    auto el2 = src.top(); //max
    src.pop();

    if (el1 > el2)
        swap(el1, el2);

    stack_t higher, lower, equal;
    
    while (src.size() != 0) {
        if (src.top() > el2)
            higher.push(src.top());
        else if (src.top() < el1)
            lower.push(src.top());
        else
            equal.push(src.top());
        src.pop();
    }

    quickStackSort2Els(higher);
    quickStackSort2Els(lower);
    quickStackSort2Els(equal);

    invert(higher);
    invert(lower);
    invert(equal);

    while (higher.size() != 0) {
        src.push(higher.top());
        higher.pop();
    }

    src.push(el2);

    while (equal.size() != 0) {
        src.push(equal.top());
        equal.pop();
    }

    src.push(el1);

    while (lower.size() != 0) {
        src.push(lower.top());
        lower.pop();
    }
}

//Сравнить скорости работы полученных алгоритмов

template <typename stack_t>
void fillStack(stack_t& s, int size) {
    for (int i = 0; i < size; ++i) {
        s.push(rand() % 1000);
    }
}

int main() {
    Stack_m<int> stack1, stack2;
    int size = 1000;

    fillStack(stack1, size);
    stack2 = stack1;

    auto start1 = chrono::high_resolution_clock::now();
    quickStackSort(stack1);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

    auto start2 = chrono::high_resolution_clock::now();
    quickStackSort2Els(stack2);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();

    cout << duration1 << endl;
    cout << duration2 << endl;

    return 0;
}
