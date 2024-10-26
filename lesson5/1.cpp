#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

//Объединение отрезков
//Написать функцию, которая по последовательности концов отрезков на прямой находит длину их объединения
//и определяет из скольких отрезков состоит это объединение.

struct segment {
    double x1, x2;
};

pair<double, int> unionSegmentLen(vector<segment> vec) {
    sort(vec.begin(), vec.end(), [](const segment& a, const segment& b) {
        return a.x1 < b.x1 || (a.x1 == b.x1 && a.x2 < b.x2);
        });

    double length = 0.0;
    int count = 0;

    double start = vec[0].x1;
    double end = vec[0].x2;

    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i].x1 <= end) {
            end = max(end, vec[i].x2);
        } else {
            length += end - start;
            count += 1;
            start = vec[i].x1;
            end = vec[i].x2;
        }
    }
    length += end - start;
    count += 1;

    return { length, count };
}

int main() {

    vector<segment> vec = { { 1.0, 3.0 }, { 2.0, 2.5 }, { 2.0, 5.0 }, { 4.0, 6.0 }, { 7.0, 13.0 } };
    auto result = unionSegmentLen(vec);
    cout << result.first << endl;
    cout << result.second << endl;

    return 0;
}
