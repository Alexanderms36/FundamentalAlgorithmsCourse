#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "Matrix.h"

using namespace std;

//2️) Построение постфиксного выражения
//Написать функцию, которая по вектору токенов арифметического
//выражения строит последовательность токенов постфиксного выражения.

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

int precedence(term op) {
    if (op.value == "+" || op.value == "-") return 1;
    if (op.value == "*" || op.value == "/" || op.value == "%") return 2;
    if (op.value == "^") return 3;
    return 4;
}

vector<term> postfix(vector<term> terms) {
    stack<term> s;
    vector<term> out;
    
    for (auto t : terms) {
        auto type = t.type;
        if (type == termtype::constant || type == termtype::variable)
            out.push_back(t);
        else if (type == termtype::openbracket || type == termtype::function)
            s.push(t);
        else if (type == termtype::closebracket) {
            if (!s.empty()) {
                while (s.top().type != termtype::openbracket) {
                    out.push_back(s.top());
                    s.pop();
                }
                s.pop();
            }
        } else if (type == termtype::operation) {
            if (!s.empty()) {
                auto top = s.top();
                while (!s.empty()) {
                    if (s.top().type != termtype::openbracket && precedence(t) <= precedence(s.top())) {
                        out.push_back(s.top());
                        top = s.top();
                        s.pop();
                    } else {
                        break;
                    }
                }
            }
            s.push(t);
        }
    }
    while (!s.empty()) {
        out.push_back(s.top());
        s.pop();
    }
    return out;
}

int main() {

    string str = "3.15 * abc - x * sin(a - b / (a + 2^a / b * c))";
    auto abob = parseExpression(str);
    auto vec = postfix(abob);

}
