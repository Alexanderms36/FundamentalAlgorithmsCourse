#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//1️)
//Задачи с выпуклой оболочкой
//Написать функцию, которая по заданному множеству точек подсчитывает количество колец.
//Первое кольцо - это выпуклая оболочка, второе кольцо - выпуклая оболочка внутри первого кольца, и т.д.

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

stack<point> convexHull(vector<point> points_o, stack<point> s) {
    vector<point> points; stack<point> h;
    for (size_t i = 0; i < points_o.size(); i++) {
        h = s;
        bool flag = true;
        while (!h.empty()) {
            if (points_o[i] == h.top()) {
                flag = false;
                break;
            }
            h.pop();
        }
        if (flag) {
            points.push_back(points_o[i]);
        }
    }
    point lowestPoint = points[0];

    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].y < lowestPoint.y) {
            lowestPoint = points[i];
        }
    }
    points.erase(remove(points.begin(), points.end(), lowestPoint), points.end());

    sort(points.begin(), points.end(), [lowestPoint](point p1, point p2) {
        return (p1 - lowestPoint) < (p2 - lowestPoint);
        });

    points.insert(points.begin(), lowestPoint);

    s.push(points[0]);
    if (points.size() < 2) {
        return s;
    }
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
template <typename stack_t>
void printStack(stack_t s) {
    cout << "stack size: " << s.size() << endl;
    stack_t temp = s;
    while (temp.size() > 0) {
        cout << temp.top().x << " " << temp.top().y << endl;
        temp.pop();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

}
size_t countRings(vector<point> points) {
    size_t count = 0;
    stack<point> conHull;
    size_t size = 0;
    while (points.size() != conHull.size()) {
        conHull = convexHull(points, conHull);
        if (conHull.size() - size >= 3)
            count++;
        size = conHull.size();
    }
    return count;
}

//Написать функцию, которая с помощью численного эксперимента вычисляет количество вершин
//выпуклой оболочки множества из n случайных точек
//внутри квадрата
//внутри окружности

stack<point> convex(vector<point> points) {
    point lowestPoint = points[0];

    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].y < lowestPoint.y) {
            lowestPoint = points[i];
        }
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
vector<point> generateRandomPointsInsideSquare(size_t numPoints, double squareSize) {
    vector<point> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, squareSize);

    for (int i = 0; i < numPoints; ++i) {
        point p = { dis(gen), dis(gen) };
        points.push_back(p);
    }

    return points;
}

double countPointsInsideSquare(size_t n) {
    double N = 0;
    for (size_t i = 0; i < n; i++) {
        vector<point> points = generateRandomPointsInsideSquare(1000, 100);
        N += convex(points).size();
    }
    return N / n;
}
 vector<point> generateRandomPointsInCircle(size_t numPoints, double radius) {
    vector<point> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> angleDis(0.0, 2.0 * 3.14159265358979);
    uniform_real_distribution<double> radiusDis(0.0, radius);

    for (int i = 0; i < numPoints; ++i) {
        double angle = angleDis(gen);
        double r = radiusDis(gen);
        point p = { r * cos(angle), r * sin(angle) };
        points.push_back(p);
    }

    return points;
}

double countPointsInsideCircle(size_t n) {
    double N = 0;
    for (size_t i = 0; i < n; i++) {
        vector<point> points = generateRandomPointsInCircle(1000, 100);
        N += convex(points).size();
    }
    return N / n;
}

//Повторить предыдущие 2 пункта для среднего количества колец

double countRingsInsideSquare(size_t n) {
    double N = 0;
    for (size_t i = 0; i < n; i++) {
        vector<point> points = generateRandomPointsInsideSquare(1000, 100);
        N += countRings(points);
        //cout << "num: " << N << endl;
    }
    return N / n;
}

double countRingsInsideCircle(size_t n) {
    double N = 0;
    for (size_t i = 0; i < n; i++) {
        vector<point> points = generateRandomPointsInCircle(1000, 100);
        N += countRings(points);
    }
    return N / n;
}

int main() {
    vector<point> vec4 = { {0, 0}, {2, 2}, {3, 4}, {1, 5}, {5, 7}, {6, 5}, {8, 8}, {4, 3},
        {1.5, 1.5}, {3.5, 3.5}, {4.5, 1}, {6.5, 2}, {7, 4}, {1, 6}, {4, 7}, {5, 6}, {5, 4}, {5, 4.5} };
    auto c = countRings(vec4);
    cout << c << endl;
}
