#include <iostream>
#include <vector>

using namespace std;


//1)
//Площадь объединения и пересечения набора кругов
//Написать функцию, которая по набору кругов, заданных центром типа point
//и радиусом, определяет площадь их общего объединения и пересечения.

struct point {
    double x, y;
};

double dist(double x1, double x2, double y1, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double unionOfCircles(vector<point> points, vector<double> radiuses, double eta = 0.01) {
    double min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;

    for (int i = 0; i < points.size(); i++) {
        if (min_x > points[i].x - radiuses[i]) min_x = points[i].x - radiuses[i];
        if (max_x < points[i].x + radiuses[i]) max_x = points[i].x + radiuses[i];
        if (min_y > points[i].y - radiuses[i]) min_y = points[i].y - radiuses[i];
        if (max_y < points[i].y + radiuses[i]) max_y = points[i].y + radiuses[i];
    }

    double area = dist(max_x, max_x, min_y, max_y) * dist(min_x, max_x, max_y, max_y);
    
    for (double x = min_x; x < max_x; x += eta) {
        for (double y = min_y; y < max_y; y += eta) {
            for (int i = 0; i < points.size(); i++) {
                if ((x - points[i].x) * (x - points[i].x) + (y - points[i].y) * (y - points[i].y) >
                    radiuses[i] * radiuses[i]) {
                    area -= eta * eta;
                    break;
                }
            }
        }
    }

    return area;
}

int main() {
    vector<point> points;
    vector<double> radiuses;
    point a = { 10, 20 };
    points.push_back(a);
    double ra = 20;
    radiuses.push_back(ra);

    point b = { 20, 20 };
    points.push_back(b);
    double rb = 20;
    radiuses.push_back(rb);

    cout << unionOfCircles(points, radiuses, 0.1);
    
    return 0;
}
