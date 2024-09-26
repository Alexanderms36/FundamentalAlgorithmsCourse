//4)
//Написать функцию от трёх аргументов типа int, которая при всех значениях входных параметров
//корректно определяет среднее арифметическое этих трёх чисел, округленное по правилам округления.
//Разрешается использовать только целочисленную арифметику типа int

#include <iostream>

using namespace std;


int arithmeticMeanByThreeNums(int num1, int num2, int num3) {
    if (num1 == num2 && num2 == num3)
        return num1;

    int avg1 = num1 / 3;
    int rem1 = num1 % 3;

    int avg2 = num2 / 3;
    int rem2 = num2 % 3;

    int avg3 = num3 / 3;
    int rem3 = num3 % 3;

    int sumAvg = avg1 + avg2 + avg3;

    int sumRem = rem1 + rem2 + rem3;

    if (sumRem >= 3) {
        sumAvg++;
        sumRem -= 3;
    }
    else if (sumRem <= -3) {
        sumAvg--;
        sumRem += 3;
    }

    return sumAvg + (sumRem / 3);
}

int main() {
    cout << arithmeticMeanByThreeNums(1, 1, 0);    // -5, 5, 10; 2147483647, 2147483647, 2147483642
    
    return 0;
}
