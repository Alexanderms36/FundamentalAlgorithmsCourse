//5)
//Написать функцию, проверяющую, что заданная последовательность чисел является длинами сторон некоторого многоугольника.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool isAPolygonBySides(const std::vector<int>& vec) {
    int n = vec.size();

    if (n < 3)
        return false;

    bool areSidesEqual = false;
    
    for (int i = 1; i < n; i++) {
        if (vec[i] == vec[i - 1] && vec[i] != 0)
            areSidesEqual = true;
        else areSidesEqual = false;
    }

    if (areSidesEqual) return 1;

    auto maxElementIter = max_element(vec.begin(), vec.end());
    int maxElement = *maxElementIter;

    int sumsides = 0;
    for (int side : vec) {
        if (side != maxElement) {
            sumsides += side;
        }
    }

    return sumsides > maxElement;
}

int main() {
    vector<int> vec = { 2, 2, 5, 7 };
    cout << isAPolygonBySides(vec);
    return 0;
}
