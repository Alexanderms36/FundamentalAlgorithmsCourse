//Сравнение двух произведений
//Написать функцию, которая по четырем переданным целым числам типа int определяет,
//что произведение первых двух равно произведению третьего и четвертого. 
//Разрешается использовать только целочисленную арифметику типа
#include <iostream>
#include <algorithm>

using namespace std;


bool is_zero_sum(int *mas, size_t n) {
    return 0;
}



bool are_equal_products(int lhs1, int lhs2, int rhs1, int rhs2) {
    if ((lhs1 == 0 || lhs2 == 0) xor (rhs1 == 0 || rhs2 == 0))
        return false;

    if ((lhs1 == 0 || lhs2 == 0) and (rhs1 == 0 || rhs2 == 0))
        return true;

    int mag = max({ abs(lhs1), abs(lhs2), abs(rhs1), abs(rhs2) });

    for (int d = 2; d <= mag; d++) {
        while ((lhs1 % d == 0 || lhs2 % d == 0) and (rhs1 % d == 0 || rhs2 % d == 0)) {
            if (lhs1 % d == 0) lhs1 /= d;
            else lhs2 /= d;
            if (rhs1 % d == 0) rhs1 /= d;
            else rhs2 /= d;
        }
    }
    return abs(lhs1) == 1 && abs(lhs2) == 1 && abs(rhs1) == 1 && abs(rhs2) == 1 &&
        lhs1 * lhs2 == rhs1 * rhs2;
}

int main() {
    cout << are_equal_products(4, 6, 8, 3) << endl;
    return 0;
}
