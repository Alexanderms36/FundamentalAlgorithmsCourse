#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

//Задача про контрабанду
//Написать функцию, решающую задачу :
//Дана последовательность прямоугольных коробок, заданных шириной и высотой,
//стоящих вплотную друг к другу на прямой.
//Требуется определить прямоугольник наибольшей площади, также стоящий на прямой,
//который целиком можно спрятать за данными прямоугольниками.

struct rect {
    double w, h;
};

rect largestRectangle(vector<rect> rects) {
    double maxArea = 0.0;
    double minH = INT_MAX;
    double allWidth = 0.0;
    double maxW = 0;
    double maxH = 0;

    for (auto r : rects) {
        double tmpArea = r.h * r.w;
        allWidth += r.w; 
        minH = min(minH, r.h);
        if (tmpArea > maxArea) {
            maxArea = tmpArea;
            maxW = r.w;
            maxH = r.h;
        }
    }
    double allRecArea = allWidth * minH;
    if (maxArea < allRecArea) {
        maxArea = allRecArea;
        maxW = allWidth;
        maxH = minH;
    }


    for (size_t i = 0; i < rects.size(); i++) {
        double width = rects[i].w;
        minH = INT_MAX;

        for (size_t j = i + 1; j < rects.size() - 1; j++) {
            width += rects[j].w;
            minH = min(min(rects[i].h, minH), rects[j].h);
            double jRec = width * minH;
            if (jRec > maxArea) {
                maxArea = jRec;
                maxW = width;
                maxH = minH;
            }
        }

        width = rects[i].w;
        minH = INT_MAX;
        for (int j = i - 1; j > -1; j--) {
            width += rects[j].w;
            minH = min(min(rects[i].h, minH), rects[j].h);
            double jRec = width * minH;
            if (jRec > maxArea) {
                maxArea = jRec;
                maxW = width;
                maxH = minH;
            }
        }
    }

    return { maxW, maxH };
}

int main() {
    vector<rect> recs = { {1.0, 1.0}, {4.0, 3.0}, {2.0, 5.0}, {1.0, 4.0}, {4.0, 2.0} };
    
    rect newRec = largestRectangle(recs);

    cout << "w = " << newRec.w << ", h = " << newRec.h << endl << "s = " << newRec.h * newRec.w << endl;
}
