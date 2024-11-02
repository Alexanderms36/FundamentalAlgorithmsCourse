#include <iostream>
#include <vector>
#include "Stack_m.h"

using namespace std;

//Упорядоченные последовательности в стеках
//В этом задании предполагается, что для типа элементов стека определена операция < .
//Написать шаблонную функцию, извлекающую из исходного стека в другой стек элементы до тех пор, 
//пока они идут в неубывающем порядке

template <typename stack_t>
void extractNondecreasing(stack_t& src, stack_t& dest) {
    if (src.size() == 0) return;

    dest.push(src.top());
    src.pop();

    while (src.size() != 0) {
        if (src.top() < dest.top())
            break;
        dest.push(src.top());
        src.pop();
    }

}

//Написать шаблонную функцию, которая по двум стекам, отсортированным по убыванию,
//перемещает данные в заданный стек в порядке возрастания

template <typename stack_t>
void merge(stack_t& left, stack_t& right, stack_t& dest) {
    stack_t temp;

    while (left.size() != 0 && right.size() != 0) {
        if (left.top() <= right.top()) {
            temp.push(left.top());
            left.pop();
        } else {
            temp.push(right.top());
            right.pop();
        }
    }

    while (left.size() != 0) {
        temp.push(left.top());
        left.pop();
    }

    while (right.size() != 0) {
        temp.push(right.top());
        right.pop();
    }

    while (temp.size() != 0) {
        dest.push(temp.top());
        temp.pop();
    }
}

//Написать шаблонную функцию сортировки стеков на основе предыдущих двух функций. 
//Сложность полученного алгоритма (количество операций сравнения) должна быть O(n.logn)

template <typename stack_t>
void resort(stack_t& src) {
    stack_t tmp;
    while (src.size() != 0) {
        tmp.push(src.top());
        src.pop();
    }
    src = tmp;
}

template <typename stack_t>
void sortn2(stack_t& src) {
    stack_t sorted;
    bool flag = false;
    while (!flag) {
        stack_t tmp1, tmp2;
        flag = true;
        extractNondecreasing(src, tmp1);
        if (src.size() != 0) {
            extractNondecreasing(src, tmp2);
        }

        resort(tmp1);
        resort(tmp2);

        merge(tmp1, tmp2, sorted);
        if (src.size() != 0 && sorted.top() >= src.top()) {
            flag = false;
        }

        while (sorted.size() != 0) {
            src.push(sorted.top());
            sorted.pop();
        }
    }
}

template <typename stack_t>
bool similar(stack_t src) {
    if (src.size() == 0) return true;

    auto a = src.top();
    src.pop();
    if (src.size() == 0) return true;
    while (src.size() != 0) {
        if (a != src.top())
            return false;
        a = src.top();
        src.pop();
       
    }
    return true;

}

template <typename stack_t>
void sort(stack_t& src) {
    if (src.size() <= 1 || similar(src)) {
        return;
    }

    stack_t left, right;

    extractNondecreasing(src, left);

    right = src;
    
    while (src.size() != 0)
        src.pop();

    sort(left);
    sort(right);

    merge(left, right, src);

}

int main() {
    Stack_m<int> a;
    Stack_m<int> b;
    Stack_m<int> c;
    a.push(1);
    a.push(2);
    a.push(1);   
    a.push(2);
    a.push(14);
    a.push(2);
    a.push(1);
    a.push(2);
    a.push(1);

    a.push(2);

    sort(a);

}
