//Написать функцию, которая по координатам двум противоположных вершин 
//двух прямоугольников на плоскости находит площадь их пересечения. 
//Стороны прямоугольников параллельны координатным осям.

#include <iostream>

using namespace std;


double findIntersection(int x1Diagonal1, int y1Diagonal1, int x2Diagonal1, 
                               int y2Diagonal1, int x1Diagonal2, int y1Diagonal2, int x2Diagonal2, int y2Diagonal2) {
    int intersection_left = max(min(x1Diagonal1, x2Diagonal1), min(x1Diagonal2, x2Diagonal2));
    int intersection_bottom = max(min(y1Diagonal1, y2Diagonal1), min(y1Diagonal2, y2Diagonal2));
    int intersection_right = min(max(x1Diagonal1, x2Diagonal1), max(x1Diagonal2, x2Diagonal2));
    int intersection_top = min(max(y1Diagonal1, y2Diagonal1), max(y1Diagonal2, y2Diagonal2));

    if (intersection_left < intersection_right && intersection_bottom < intersection_top)
        return (intersection_right - intersection_left) * (intersection_top - intersection_bottom);

    return 0;
}

int main() {
    int x1_1, y1_1, x2_1, y2_1, x1_2, y1_2, x2_2, y2_2;
    cin >> x1_1 >> y1_1 >> x2_1 >> y2_1 >> x1_2 >> y1_2 >> x2_2 >> y2_2;
    cout << findIntersection(x1_1, y1_1, x2_1, y2_1, x1_2, y1_2, x2_2, y2_2);
    return 0;
}
