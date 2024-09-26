//1)
//Написать функцию, принимающую на вход набор из чисел типа int, которая при всех значениях входных параметров корректно определяет,
//что сумма всех чисел промежутка равна 0. Разрешается использовать только целочисленную арифметику типа int

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool isSumEqualsZero(vector<int> vec) {
    bool areAllZeros = true;
    bool areAllPositiveOrZero = true;
    bool areAllNegativeOrZero = true;

    for (int elem : vec) {
        if (elem != 0) areAllZeros = false;
        if (elem < 0) areAllPositiveOrZero = false;
        if (elem > 0) areAllNegativeOrZero = false;
    }

    if (areAllZeros) 
        return 1;

    else if (areAllPositiveOrZero || areAllPositiveOrZero)
        return 0;

    bool areAllPositive = false;
    bool areAllNegative = false;

    while (vec.size() > 1) {
        auto maxElement = max_element(vec.begin(), vec.end());
        auto minElement = min_element(vec.begin(), vec.end());

        int maxElementIndex = distance(vec.begin(), maxElement);
        int minElementIndex = distance(vec.begin(), minElement);

        int sumOfMaxAndMin = *maxElement + *minElement;

        if (maxElementIndex > minElementIndex) {
            vec.erase(vec.begin() + maxElementIndex);
            vec.erase(vec.begin() + minElementIndex);
        } else {
            vec.erase(vec.begin() + minElementIndex);
            vec.erase(vec.begin() + maxElementIndex);
        }

        vec.push_back(sumOfMaxAndMin);

        for (int elem : vec) {
            if (elem < 0) areAllNegative = true;
            if (elem > 0) areAllPositive = true;
        }

        if ((areAllNegative || areAllPositive) && 
            !(areAllNegative == areAllPositive && areAllPositive == true)) {
            return 0;
        }

        areAllNegative = false;
        areAllPositive = false;

    }

    return (vec[0] == 0);
}

int main() {
    vector<int> vec = { -488389829, 351516404, 939326998, 726416941, 958795652, -580724563,
       671399187, 773759770, -917911214, -508151789, -799327152, 968497989, -545718768, -169589359,
       -132022834, 897509234, 531215168, -247538623, 617302079, -1015455097, -1015455097, -1015455097 };
    cout << isSumEqualsZero(vec);

    return 0;
}
