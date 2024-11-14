#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

//2)
//Выпуклая оболочка множества
//Реализовать структуру point, состоящую из двух полей - координат.
//Добавить в структуру операции покоординатного сложения и вычитания точек, 
//а также операцию <, проверяющую, что поворот радиус - вектора первой точки ко второй осуществляется против часовой стрелки.

struct point {
    double x, y;

    point(double x_coord, double y_coord) : x(x_coord), y(y_coord) {}

    point operator+(point other) {
        return { x + other.x, y + other.y };
    }

    point operator-(point other) {
        return { x - other.x, y - other.y };
    }

    bool operator<(point other) {
        //x1 * y2 - y1 * x2
        return (x * other.y - y * other.x) > 0;
    }

    bool operator==(point other) {
        return (x == other.x && y == other.y);
    }
};

//Реализовать с помощью структуры point лекционный алгоритм построения выпуклой оболочки,
//получающий на вход последовательность точек, а на выходе дающий вершины выпуклой оболочки.

stack<point> convexHull(vector<point> points) {
    point lowestPoint = points[0];

    for (auto p : points) {
        if (p.y < lowestPoint.y)
            lowestPoint = p;
    }

    points.erase(remove(points.begin(), points.end(), lowestPoint), points.end());

    sort(points.begin(), points.end(), [lowestPoint](point p1, point p2) {
        return (p1 - lowestPoint) < (p2 - lowestPoint);
        });

    points.insert(points.begin(), lowestPoint);

    stack<point> s;
    s.push(points[0]);
    s.push(points[1]);

    for (size_t i = 2; i < points.size(); i++) {
        point c = points[i];

        while (s.size() >= 2) {
            point b = s.top();
            s.pop();
            point a = s.top();

            point ab = b - a;
            point ac = c - a;

            if (ab < ac) {
                s.push(b);
                break;
            }
        }

        s.push(c);
    }
    
    return s;
}


int main() {
    //2)
    point a(2, 2);
    point b(3, -190);
    auto c = a < b;
    cout << c;
    vector<point> vec4 = { {1, 2}, {0, 1}, {2, 0}, {1, 3}, {4, 0}, {2, 3}, {3, 2}, {4, 1}, {6, 2}, {5, 3}, {4, 3} };

    stack<point> stack = convexHull(vec4);

}
