#include <string>
#include <iostream>
#include <regex>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int precedence(char op) {
    switch (op) {
    case '-':return 2;
    case '+':return 2;
    case '/':return 3;
    case '*':return 3;
    }
    return -1;
}

char associativity(char op) {
    switch (op) {
    case '-':return 'L';
    case '+':return 'L';
    case '/':return 'L';
    case '*':return 'L';
    }
    return '.';
}

bool isoperator(char op) {
    switch (op) {
    case '-':return 1;
    case '+':return 1;
    case '/':return 1;
    case '*':return 1;
    }
    return 0;
}
string modify(string s)
{
    s = regex_replace(s, regex(" "), ""); //remove spaces
    for (long long i = 1;i < s.length();i++) {
        if (isoperator(s[i - 1]) && (s[i] == '-' || s[i] == 'm')) {
            s[i] = 'm';
        }
        if (isoperator(s[i - 1]) && (s[i] == '+' || s[i] == 'p')) {
            s[i] = 'p';
        }
    }
    if (s[0] == '-') { s[0] = 'm'; }
    if (s[0] == '+') { s[0] = 'p'; }

    string ans="";
    for (int i = 0;i < s.length()-1;i++) {
        if (s[i] >= '0' && s[i] <= '9' && s[i + 1] == '(') {
            ans += s[i]; ans+= '*';
        }
        else {
            ans += s[i];
        }
    }
    ans += s[s.length() - 1];
    return ans;
}

string to_postfix(string exp)
{
    exp = modify(exp);
    vector <char> operators;
    string ans = "";
    string operand = "";
    char prevchar = '*';

    for (long long i = 0;i < exp.length();i++) {

        if (i > 0) { prevchar = exp[i - 1]; }
        char c = exp[i];

        if (isdigit(c) != 0 || c == '.') { // if c is a digit or a decimal point
            operand += c;
        }
        else {// c is an operator

          //add operand to ans
            if (operand != "") {
                ans += operand + " ";
                operand = "";
            }
            if (operators.size() == 0 || c == '(') {
                operators.push_back(c);
            }
            else { //operator stack not empty
                char top = operators.back(); //operator at top of operator stack
                if (c == ')') {
                    while (top != '(') {
                        ans += top;ans += " ";
                        operators.pop_back();
                        top = operators.back();
                    }
                    operators.pop_back(); //pop the (
                }
                else {
                    if (top == '(' || (associativity(c) == 'R' && (precedence(c) >= precedence(top)))) {
                        operators.push_back(c);
                    }
                    else {
                        if (associativity(c) == 'L') {
                            while (precedence(c) <= precedence(top) && operators.size() != 0 && top != '(') {
                                ans += top; ans += " ";
                                operators.pop_back();
                                if (operators.size() == 0) { break; }
                                top = operators.back();
                            }
                            operators.push_back(c);
                        }
                    }
                }
            }

        }
    }

    if (operand != "") {
        ans += operand + " ";
    }
    if (operators.size() != 0) {
        for (int i = operators.size() - 1;i > -1;i--) {
            ans += operators[i]; ans += " ";
        }
    }

    return ans;
}

double result(double a, double b, string o) {
    //result(5.2, 1.1, "-") returns 4.1
    if (o == "+") { return a + b; }
    if (o == "-") { return a - b; }
    if (o == "*") { return a * b; }
    if (o == "/") { return a / b; }
    if (o == "^") { return pow(a, b); }
    return 0;
}
double EvaluateExpression(string exp) {
    string postfix = to_postfix(exp); //postfix has spaces but no ()
    regex regex(R"([\s]+)");
    vector<std::string> out( // save all space-separated operands and operators to out
        sregex_token_iterator(postfix.begin(), postfix.end(), regex, -1),
        sregex_token_iterator()
    );

    //Note : unary plus is always ignored
    vector <double> Operand;
    for (auto i : out) {
            if (i == "*" || i == "/" || i == "+" || i == "-" || i == "^") {
                double b = Operand.back();
                Operand.pop_back();
                double a = Operand.back();
                Operand.pop_back();
                Operand.push_back(result(a, b, i));
            }
            else {
                Operand.push_back(stod(i));
            }
    }
    return Operand.back();
}
