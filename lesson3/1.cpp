#include <iostream>
#include <vector>

using namespace std;


//1)
//Сравнение двух произведений.
//Написать эффективную функцию, которая по двум переданным наборам целых чисел типа int определяет,
//что произведение чисел первого набора равно произведению чисел второго набора.
//Разрешается использовать только целочисленную арифметику типа int

int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

bool containsZero(vector<int> vec) {
	for (int num : vec)
		if (num == 0) return 1;
	return 0;
}

bool areProductsEqual(vector<int> vec1, vector<int> vec2) {
	int n1 = vec1.size();
	int n2 = vec2.size();

	bool areEqual = true;
	bool vec1HasZero = containsZero(vec1);
	bool vec2HasZero = containsZero(vec2);

	if (vec1HasZero != vec2HasZero)
		return 0;
	else if (vec1HasZero && vec2HasZero)
		return 1;

	bool isGCDOne = true;
	
	while(isGCDOne){
		int n = min(n1, n2);
		int gcdn = 0;
		for (int i = 0; i < n; i++) {
			gcdn = gcd(vec1[i], vec2[i]);
			if (gcdn != 1) {
				vec1[i] /= gcdn;
				vec2[i] /= gcdn;
				continue;
			}
			else if (i == n - 1) {
				isGCDOne = false;
			}
		}

	}
	
	int product1 = 1;
	int product2 = 1;

	for (int elem : vec1)
		product1 *= elem;

	for (int elem : vec2)
		product2 *= elem;

	return product1 == product2;
}

int main() {
	vector<int> vec1 = { 2147483647, 1073741821, 2, 1073741821, 2, 1073741821, 2 };
	vector<int> vec2 = { 2147483647, 2147483642, 2147483642, 2147483642 };

	vector<int> vec1 = { 1, 2147483647, 16, 4 };
	vector<int> vec2 = { 1, 2147483647, 2 };

	cout << areProductsEqual(vec1, vec2);

	return 0;
}
