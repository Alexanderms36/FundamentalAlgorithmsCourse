#include <iostream>
#include <vector>
#include "Stack_m.h"

using namespace std;

//Правильное скобочное выражение
//Дана скобочная последовательность из разных типов скобок.Написать функции для решения следующих задач :
// ([{}])

//определить, является ли данная скобочная последовательность правильной, а если нет, то указать первый ошибочный символ;

pair<bool, char> isValidBracketStruct(vector<char> vec) {
    if (vec[0] == '}' || vec[0] == ')' || vec[0] == ']')
        return { false, vec[0] };

    Stack_m<char> s;

    for (auto elem : vec) {
        if (elem == '{' || elem == '(' || elem == '[') {
            s.push(elem);
        } else {
            if (elem == '}' && s.top() == '{' || elem == ')' && s.top() == '(' || elem == ']' && s.top() == '[')
                s.pop();
            else 
                return { false, elem };
        }
    }
    if (s.size() == 0)
        return { true, ' ' };

    return { false, s.top() };
}

int main() {
    vector<char> vec = { '{', '(', '(', '[', ']', '}' }; 
    
    auto ans = isValidBracketStruct(vec);
    cout << ans.first << ' ' << ans.second;
}
