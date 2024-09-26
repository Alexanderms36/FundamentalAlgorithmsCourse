//Сумма чисел равна нулю
//Написать функцию, принимающую на вход промежуток из чисел типа int, 
//которая при всех значениях входных параметров корректно определяет,
//что сумма всех чисел промежутка равна 0. 
//Разрешается использовать только целочисленную арифметику типа int


#include <iostream>

using namespace std;


bool isSumOfNumbersInTheInterval(int firstNumberFromTheInterval, int theLastNumberFromTheInterval) {
    return (-firstNumberFromTheInterval == theLastNumberFromTheInterval) ? 1 : 0;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << isSumOfNumbersInTheInterval(a, b);
    return 0;
}