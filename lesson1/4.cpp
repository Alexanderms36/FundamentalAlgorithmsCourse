//Создать структуру point, содержащую два поля для координат типа double.  
//С помощью этой структуры написать 2 функции:
//функцию, которая по концам двух отрезков на плоскости определяет, пересекаются ли они;
//функцию, которая по трем точкам определяет, лежат ли они на одной прямой.

#include <iostream>

using namespace std;


struct point {
    double x, y;
};

double findCoefficient(point point1, point point2) {
    
    return ((point2.x - point1.x) != 0) ? (point2.y - point1.y) / (point2.x - point1.x) : 0;
}

double findBias(point point1, point point2, double coeff) {
    return point1.y - coeff * point1.x;
}


bool isPointOnSegment(point p1, point p2, double x, double y) {
    return min(p1.x, p2.x) <= x && x <= max(p1.x, p2.x) &&
        min(p1.y, p2.y) <= y && y <= max(p1.y, p2.y);
}

bool areSegmentsIntersect(point point1, point point2, point point3, point point4) {

    double firstCoefficient = findCoefficient(point1, point2);
    double firstBias = findBias(point1, point2, firstCoefficient);
    double secondCoefficient = findCoefficient(point3, point4);
    double secondBias = findBias(point3, point4, secondCoefficient);

    if (firstCoefficient == secondCoefficient && firstBias != secondBias) return false; 

    double intersectingPointX = (secondBias - firstBias) / (firstCoefficient - secondCoefficient);
    double intersectingPointY = firstCoefficient * intersectingPointX + firstBias;

    return isPointOnSegment(point1, point2, intersectingPointX, intersectingPointY) && 
           isPointOnSegment(point3, point4, intersectingPointX, intersectingPointY);
}

bool areThe3PointsLieOnTheSameLine(point point1, point point2, point point3) {
    double coefficient = findCoefficient(point1, point2);
    double bias = findBias(point1, point2, coefficient);
    
    return (point3.y == coefficient * point3.x + bias);
}

int main() {
    point point1, point2, point3, point4;

    cin >> point1.x >> point1.y >> point2.x >> point2.y >> point3.x >> point3.y >> point4.x >> point4.y;
    cout << areSegmentsIntersect(point1, point2, point3, point4);

    cin >> point1.x >> point1.y >> point2.x >> point2.y >> point3.x >> point3.y;
    cout << areThe3PointsLieOnTheSameLine(point1, point2, point3);
    return 0;
}
