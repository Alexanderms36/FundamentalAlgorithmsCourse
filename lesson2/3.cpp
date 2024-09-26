//3)
//Написать функцию, которая по концам отрезка типа point, а также вершине луча и его полярному углу,
//определяет, пересекает ли этот луч отрезок.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


const double PI = 3.14159;

struct point {
    double x, y;
};

bool areIntersecting(point aSegmentCoord, point bSegmentCoord, point rayStart, double angle) {
    double angle_rad = angle * PI / 180.0;
    double cos_angle = cos(angle_rad);
    double sin_angle = sin(angle_rad);

    //отрезок - это точка
    if (aSegmentCoord.x == bSegmentCoord.x && aSegmentCoord.y == bSegmentCoord.y) {
        double px = aSegmentCoord.x - rayStart.x;
        double py = aSegmentCoord.y - rayStart.y;
        double crossProduct = px * sin_angle - py * cos_angle;

        if (crossProduct < 0) return false;
        
        //скалярное произведение
        double dotProduct = px * cos_angle + py * sin_angle;
        if (dotProduct < 0) return false;
    }

    //вертикальный луч
    if (cos_angle == 0) {
        if (rayStart.x >= min(aSegmentCoord.x, bSegmentCoord.x) && rayStart.x <= max(aSegmentCoord.x, bSegmentCoord.x)) {
            return (sin_angle > 0) ? 
                rayStart.y <= max(aSegmentCoord.y, bSegmentCoord.y) : rayStart.y >= min(aSegmentCoord.y, bSegmentCoord.y);
        }
        return false;
    }

    double numeratorForS = cos_angle * (aSegmentCoord.y - rayStart.y) + sin_angle * (rayStart.x - aSegmentCoord.x);
    double denumeratorForS = sin_angle * (bSegmentCoord.x - aSegmentCoord.x) - 
        cos_angle * (bSegmentCoord.y - aSegmentCoord.y);

    //луч и отрезок параллельны
    if (denumeratorForS == 0) {
        if (abs(aSegmentCoord.y - rayStart.y) == 0 && abs(bSegmentCoord.y - rayStart.y) == 0) {
            if ((aSegmentCoord.x >= rayStart.x && bSegmentCoord.x >= rayStart.x) || 
                (aSegmentCoord.x <= rayStart.x && bSegmentCoord.x <= rayStart.x))
                return true;
        }
        return false;
    }

    double s = numeratorForS / denumeratorForS;

    double numeratorForT = s * (bSegmentCoord.x - aSegmentCoord.x) + aSegmentCoord.x - rayStart.x;
    double t = numeratorForT / cos_angle;

    return (t >= 0 && s >= 0 && s <= 1);
}


int main() {

    point a = { 0, 0 };
    point b = { 5, 5 };
    point c = { 0, 10 };
    double angle = 45;

    cout << areIntersecting(a, b, c, angle);

    return 0;
}
