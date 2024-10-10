#include <iostream>
#include <vector>

using namespace std;


//2)
//Площадь пересечения набора прямоугольников
//Написать функцию, которая по набору прямоугольников, заданных противоположными вершинами типа point одной из диагоналей,
//определяет площадь их общего пересечения.

double findIntersectionArea(vector<point> vec) {
	int n = vec.size();

	if (n == 2) {
		double width = max(vec[0].x, vec[1].x) - min(vec[0].x, vec[1].x);
		double height = max(vec[0].y, vec[1].y) - min(vec[0].y, vec[1].y);

		return width * height;
	}

	double intersection_left = max(min(vec[0].x, vec[1].x), min(vec[2].x, vec[3].x));
	double intersection_bottom = max(min(vec[0].y, vec[1].y), min(vec[2].y, vec[3].y));

	double intersection_right = min(max(vec[0].x, vec[1].x), max(vec[2].x, vec[3].x));
	double intersection_top = min(max(vec[0].y, vec[1].y), max(vec[2].y, vec[3].y));

	if (n > 4) {
		for (int i = 4; i < n - 1; i += 2) {
			intersection_left = max(min(intersection_left, intersection_right), min(vec[i].x, vec[i + 1].x));
			intersection_bottom = max(min(intersection_bottom, intersection_top), min(vec[i].y, vec[i + 1].y));

			intersection_right = min(max(intersection_left, intersection_right), max(vec[i].x, vec[i + 1].x));
			intersection_top = min(max(intersection_bottom, intersection_top), max(vec[i].y, vec[i + 1].y));
		}
	}

	if (intersection_left < intersection_right && intersection_bottom < intersection_top)
		return (intersection_right - intersection_left) * (intersection_top - intersection_bottom);

	return 0;
}

int main() {
	vector<point> vec;
	point a2, a1, b1, b2, c1, c2, d1, d2, e1, e2;
	a1.x = 2; a1.y = 4;
	a2.x = 8; a2.y = 14;
	b1.x = 4; b1.y = 1;
	b2.x = 12; b2.y = 10;
	c1.x = 5; c1.y = 7;
	c2.x = 14; c2.y = 17;
	d1.x = 6; d1.y = 8;
	d2.x = 17; d2.y = 9;
	e1.x = 6; e1.y = 8;
	e2.x = 7; e2.y = 20;

	vec.push_back(a1); vec.push_back(a2);
	vec.push_back(b1); vec.push_back(b2);
	vec.push_back(c1); vec.push_back(c2);
	vec.push_back(d1); vec.push_back(d2);
	vec.push_back(e1); vec.push_back(e2);

	cout << findIntersectionArea(vec);
	
	return 0;
}
