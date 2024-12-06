#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//1️) Целые точки и многоугольники
//Написать функцию, которая по целочисленным концам отрезка на плоскости определяет количество точек с целыми координатами,
//лежащих на этом отрезке.

struct Point {
    double x, y;
};

pair<double, double> calcLineParams(vector<Point> seg) {
    if (seg[0].x == seg[1].x) {
        throw invalid_argument("invalid args");
    }

    double k = (seg[1].y - seg[0].y) / (seg[1].x - seg[0].x);
    double b = seg[0].y - seg[0].x * k;

    return { k, b };
}

size_t countIntCoords(vector<Point> seg) {
    if (seg[0].x > seg[1].x) swap(seg[0], seg[1]);
    
    auto params = calcLineParams(seg);
    double k = params.first, b = params.second;
    int start = ceil(seg[0].x);
    int end = floor(seg[1].x);
    
    vector<int> vec(end - start + 1);
    iota(vec.begin(), vec.end(), start);

    size_t count = count_if(vec.begin(), vec.end(), [&](int i) {
            double y = k * i + b;
            return (abs(y - round(y)) == 0.00);
        }
    );

    return count;
}

int main() {
    vector<Point> vec = { {0.5, 1.2}, {3.5, 4.8} };
    cout << countIntCoords(vec);
}
