#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <functional>
#include <numeric>
#include <map>

using namespace std;

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

vector<term> parseExpression(const string& expr) {
    vector<term> res;
    auto cur = expr.begin();
    while (cur != expr.end()) {
        if (isspace(*cur)) {
            ++cur;
            continue;
        }
        auto last = find_if(cur, expr.end(), [](auto c) { return !isalnum(c) && c != '.' && c != '_'; });
        if (cur == last) ++last;
        res.push_back({ string(cur, last), termtype::operation });
        cur = last;
    }
    for (size_t i = 0; i < res.size(); i++) {
        char c = res[i].value[0];
        if (isdigit(c) || c == '.') res[i].type = termtype::constant;
        else if (c == '(') res[i].type = termtype::openbracket;
        else if (c == ')') res[i].type = termtype::closebracket;
        else if ((isalpha(c) || c == '_') && i + 1 < res.size() && res[i + 1].value == "(")
            res[i].type = termtype::function;
        else if (isalpha(c) || c == '_') res[i].type = termtype::variable;
    }
    return res;
}

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
        }
        else if (type == termtype::operation) {
            if (!s.empty()) {
                auto top = s.top();
                while (!s.empty()) {
                    if (s.top().type != termtype::openbracket && precedence(t) <= precedence(s.top())) {
                        out.push_back(s.top());
                        top = s.top();
                        s.pop();
                    }
                    else {
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

//2) Вычислитель постфиксного выражения
//Написать функцию, которая по последовательности токенов постфиксной записи, а также по ассоциативному массиву,
//содержащему значения переменных, и ассоциативному массиву, сопоставляющему имя операции и вычисляющий её код,
//находит значение постфиксного выражения.
//В качестве второго ассоциативного массива можно использовать вот такой тип :
//auto operations = map<string, function<(double(stack<double>&))>>;
//
//Добавление операции или функции в такой массив может быть таким :
//operations["sin"] = [](stack<double>& s) { auto t = s.top(); s.pop(); return sin(t); };
//
//Здесь стек s -- это как раз тот стек промежуточных вычислений из алгоритма. Каждая операция сама решает,
//сколько ей аргументов нужно извлечь из стека для вычисления.
//Добавить в вычислитель операции + , -, *, / , ^, %, все тригонометрические функции, логарифмирование, потенциирование

map<string, function<double(stack<double>&)>> getOperations() {
    map<string, function<double(stack<double>&)>> operations;
    const double M_PI = 3.14159;
    operations["+"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return a + b;
        };

    operations["-"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return b - a;
        };

    operations["*"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return a * b;
        };

    operations["/"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return b / a;
        };

    operations["%"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return fmod(b, a);
        };

    operations["^"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        auto b = s.top();
        s.pop();
        return pow(b, a);
        };

    operations["sqrt"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        return sqrt(a);
        };

    operations["exp"] = [](stack<double>& s) {
        auto a = s.top();
        s.pop();
        return exp(a);
        };

    operations["sin"] = [M_PI](stack<double>& s) {
        auto t = s.top() * M_PI / 180;
        s.pop();
        return sin(t);
        };

    operations["cos"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return cos(t);
        };

    operations["tg"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return tan(t);
        };

    operations["ctg"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return cos(t) / sin(t);
        };

    operations["asin"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return asin(t);
        };

    operations["acos"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return acos(t);
        };

    operations["atg"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return atan(t);
        };

    operations["actg"] = [M_PI](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return M_PI / 2 - atan(t);
        };

    operations["ln"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return log(t);
        };

    operations["log10"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return log10(t);
        };

    operations["log2"] = [](stack<double>& s) {
        auto t = s.top();
        s.pop();
        return log2(t);
        };

    return operations;
}

map<string, double> getVariables() {
    map<string, double> variables;
    variables["abc"] = 1.0;
    variables["a"] = 2.0;
    variables["b"] = 4.0;
    variables["c"] = 6.0;
    variables["x"] = 4.0;
    variables["pi"] = 3.14159;
    variables["e"] = 2.71828;

    return variables;
}

double calculateExpression(vector<term> expr) {

    auto variables = getVariables();
    auto operations = getOperations();

    stack<double> s;
    for (size_t i = 0; i < expr.size(); i++) {
        auto t = expr[i].type;
        switch (t) {
        case termtype::constant:
            s.push(stod(expr[i].value));
            break;
        case termtype::variable:
            s.push(variables[expr[i].value]);
            break;
        case termtype::operation:
        case termtype::function: {
                string op = expr[i].value;
                if (operations.find(op) != operations.end()) {
                    s.push(operations[op](s));
                } else {
                    return 0;
                }
            }
            break;
        default:
            break;
        }
    }

    return (!s.empty()) ? s.top() : 0.0;
}

int main() {
    string str = "3.15 * abc - x * sin(a - b / (a + 2^a / b * c))"; // = 3.045292207
    auto abob = parseExpression(str);
    auto vec = postfix(abob);
    auto num = calculateExpression(vec);

    return 0;
}
