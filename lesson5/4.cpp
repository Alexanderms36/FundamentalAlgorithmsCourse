#include <iostream>
#include "Stack_m.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;


//Наибольшее пустое окно
//Написать функцию, которая по последовательности точек
//внутри прямоугольника с заданными углами находит наибольший по площади прямоугольник,
//лежащий внутри данного, который не содержит ни одной из точек последовательности.

struct point {
    double x, y;
};

struct rectangle {
    point a, b, c, d;
};

bool isAnyPointBetween(point firstPoint, point secondPoint, vector<point> points, int n, int j, bool flag) {
    for (int k = 0; k < n; k++) {
        if (k != j) {
            if (firstPoint.x < points[k].x && points[k].x < secondPoint.x &&
                firstPoint.y < points[k].y && points[k].y < secondPoint.y)
                flag = false;
            if (firstPoint.x < points[k].x && points[k].x < secondPoint.x &&
                firstPoint.y > points[k].y && points[k].y > secondPoint.y)
                flag = false;
            if (firstPoint.x > points[k].x && points[k].x > secondPoint.x &&
                firstPoint.y < points[k].y && points[k].y < secondPoint.y)
                flag = false;
            if (firstPoint.x > points[k].x && points[k].x > secondPoint.x &&
                firstPoint.y > points[k].y && points[k].y > secondPoint.y)
                flag = false;
        }
    }
    return flag;
}

rectangle getLargestRect(vector<point> points, rectangle rect) {
    vector<double> maxSizeRectangleArea;
    vector<rectangle> maxSizeRectangle;

    vector<point> borderPoints;
    vector<point> insidePoints;

    rectangle tmpRec;

    int n = points.size();

    for (point point : points) {
        borderPoints.push_back({ point.x, rect.a.y });
        borderPoints.push_back({ point.x, rect.c.y });
        borderPoints.push_back({ rect.a.x, point.y });
        borderPoints.push_back({ rect.c.x, point.y });
    }

    borderPoints.push_back({ rect.a.x, rect.a.y });
    borderPoints.push_back({ rect.b.x, rect.b.y });
    borderPoints.push_back({ rect.c.x, rect.c.y });
    borderPoints.push_back({ rect.d.x, rect.d.y });

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            insidePoints.push_back({ points[i].x, points[j].y });
            insidePoints.push_back({ points[j].x, points[i].y });        
        }
    }

    double tmpArea = 0.0;

    for (int i = 0; i < borderPoints.size(); i++) {
        for (int j = 0; j < n; j++) {
            bool flag = true;
            flag = isAnyPointBetween(points[j], borderPoints[i], points, n, j, flag);
            if ((points[j].x != borderPoints[i].x ||
                points[j].y != borderPoints[i].y) && flag) {
                tmpArea = abs(points[j].x - borderPoints[i].x) * abs(points[j].y - borderPoints[i].y);
                maxSizeRectangleArea.push_back(tmpArea);
                tmpRec = { borderPoints[i], points[j], {borderPoints[i].x, points[j].y} , 
                        {points[j].x, borderPoints[i].y} };
                maxSizeRectangle.push_back(tmpRec);
            }
        }
    }

    for (int i = 0; i < insidePoints.size(); i++) {
        for (int j = i + 1; j < insidePoints.size(); j++) {
            bool flag = true;
            flag = isAnyPointBetween(insidePoints[j], insidePoints[i], points, n, -1, flag);
            if ((insidePoints[j].x != insidePoints[i].x ||
                insidePoints[j].y != insidePoints[i].y) && flag) {
                tmpArea = abs(insidePoints[j].x - insidePoints[i].x) * abs(insidePoints[j].y - insidePoints[i].y);
                maxSizeRectangleArea.push_back(tmpArea);
                tmpRec = { insidePoints[i], insidePoints[j], {insidePoints[i].x, insidePoints[j].y} , 
                        {insidePoints[j].x, insidePoints[i].y} };
                maxSizeRectangle.push_back(tmpRec);
            }
        }
    }

    // теперь оставшиеся внутренние с точками с границ
    for (int i = 0; i < borderPoints.size(); i++) {
        for (int j = 0; j < insidePoints.size(); j++) {
            bool flag = true;
            flag = isAnyPointBetween(borderPoints[i], insidePoints[j], points, n, -1, flag);
            if ((insidePoints[j].x != borderPoints[i].x ||
                insidePoints[j].y != borderPoints[i].y) && flag) {
                tmpArea = abs(insidePoints[j].x - borderPoints[i].x) * abs(insidePoints[j].y - borderPoints[i].y);
                maxSizeRectangleArea.push_back(tmpArea);
                tmpRec = { borderPoints[i], insidePoints[j], {borderPoints[i].x, insidePoints[j].y} ,
                        {insidePoints[j].x, borderPoints[i].y}};
                maxSizeRectangle.push_back(tmpRec);
            }
        }
    }

    double mArea = 0.0;
    int num = 0;

    for (int i = 0; i < maxSizeRectangleArea.size(); i++) {
        if (maxSizeRectangleArea[i] > mArea) {
            mArea = maxSizeRectangleArea[i];
            num = i;
        }
    }

    return maxSizeRectangle[num];
}

int main() {

    vector<point> vec = { {1.0, 2.0}, {4.0, 5.0}, { 6.0, 4.0 }, { 4.0, 2.0 } };
    rectangle rect, newRec;

    vector<point> points = { {1, 1}, {6, 1}, {1, 6}, {6, 6},
        {3,2}, {3,3},{5,2},{5,3},
        {3,2},{3,6},{4,2},{4,6},
        {7,8}, {4,6}, {4,2}, {7,2},
        {7,6}, {1,1},{3,1},{1,6},{3,6} };
    rectangle rec;


    rect.a = { 0.0, 0.0 };
    rect.b = { 0.0, 6.0 };
    rect.c = { 7.0, 6.0 };
    rect.d = { 7.0, 0.0 };

    rec.a = { 0.0, 0.0 };
    rec.b = { 0.0, 7.0 };
    rec.d = { 7.0, 7.0 };
    rec.c = { 7.0, 0.0 };


    newRec = getLargestRect(points, rec);
    
    cout << newRec.a.x << " " << newRec.a.y << endl;
    cout << newRec.b.x << " " << newRec.b.y << endl;
    cout << newRec.c.x << " " << newRec.c.y << endl;
    cout << newRec.d.x << " " << newRec.d.y << endl;

    return 0;
}
