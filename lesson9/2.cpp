#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//Разбиение арифметического выражения на термы
//Написать функцию, которая по строке с записью арифметического выражения разбивает его на
//вектор термов, имеющих строковое представление и тип(константа, переменная, отк.скобка, закр.скобка, функция или оператор).

enum class termtype { variable, constant, function, operation, openbracket, closebracket };

string termTypeToString(termtype type) {
    switch (type) {
    case termtype::variable:
        return "variable";
    case termtype::constant: 
        return "constant";
    case termtype::function: 
        return "function";
    case termtype::operation: 
        return "operation";
    case termtype::openbracket: 
        return "openbracket";
    case termtype::closebracket: 
        return "closebracket";
    default: 
        return "none";
    }
}

struct term {
    string value;
    termtype type;
};

vector<term> parseExpression(string expression) {
    vector<term> terms;
    size_t i = 0;

    for (size_t i = 0; i < expression.size(); i++) {
        if (isspace(expression[i]))
            continue;
        if (isdigit(expression[i])) {
            string num;
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                num += expression[i];
                if (isdigit(expression[i + 1]) || expression[i + 1] == '.')
                    i++;
                else
                    break;
            }
            terms.push_back({ num, termtype::constant });

        } else if (isalpha(expression[i])) {
            string s;

            while (i < expression.size() && isalpha(expression[i])) {
                s += expression[i];
                if (isalpha(expression[i + 1]))
                    i++;
                else
                    break;
            }

            if (i < expression.size() && expression[i] == '(')
                terms.push_back({ s, termtype::function });
            else
                terms.push_back({ s, termtype::variable });

        } else if (expression[i] == '(') {
            terms.push_back({ "(", termtype::openbracket });

        } else if (expression[i] == ')') {
            terms.push_back({ ")", termtype::closebracket });

        } else {
            string s;
            s += expression[i];
            terms.push_back({ s, termtype::operation });
        }
    }
    return terms;
}

int main() {

    vector<term> terms = parseExpression("2*4+sin(x^2)");
    vector<term> terms = parseExpression("3.14 * abc - x * sin((2^a) / 5.299 - bc) + 1");
    for (auto t : terms) {
       cout << t.value << " " << termTypeToString(t.type) << endl;
    }

    return 0;
}
