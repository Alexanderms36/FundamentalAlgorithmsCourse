//2) 
//Написать эффективную функцию, которая по четырем переданным целым числам типа int определяет,
//что произведение первых двух равно произведению третьего и четвертого.
//Разрешается использовать только целочисленную арифметику типа int

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool areEqualProducts(int lhs1, int lhs2, int rhs1, int rhs2) {

    if ((lhs1 == 0 || lhs2 == 0) xor (rhs1 == 0 || rhs2 == 0))
        return false;

    if ((lhs1 == 0 || lhs2 == 0) and (rhs1 == 0 || rhs2 == 0))
        return true;

    bool isOne = 0;
    int maxlhs = max(lhs1, lhs2), maxrhs = max(rhs1, rhs2);
    int gcdForMaxValues = gcd(maxlhs, maxrhs);

    while (!isOne) {

        if (maxlhs == lhs1 && maxrhs == rhs1) {
            lhs1 /= gcdForMaxValues;
            rhs1 /= gcdForMaxValues;
        } else if (maxlhs == lhs1 && maxrhs == rhs2) {
            lhs1 /= gcdForMaxValues;
            rhs2 /= gcdForMaxValues;
        } else if (maxlhs == lhs2 && maxrhs == rhs1) {
            lhs2 /= gcdForMaxValues;
            rhs1 /= gcdForMaxValues;
        } else {
            lhs2 /= gcdForMaxValues;
            rhs2 /= gcdForMaxValues;
        }

        maxlhs = max(lhs1, lhs2), maxrhs = max(rhs1, rhs2);

        gcdForMaxValues = gcd(maxlhs, maxrhs);


        isOne = abs(gcdForMaxValues) == 1;

    }

    return lhs1 * lhs2 == rhs1 * rhs2;
}

int main() {

    cout << areEqualProducts(9378783, 1466, 3126261, 4398) << endl; //13 749 295 878

    return 0;
}
