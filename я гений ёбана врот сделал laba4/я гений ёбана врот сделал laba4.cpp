#include <iostream>
#include <stack>
#include <string>
using namespace std;

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return 0;
}

string infixToPostfix(string infix) {
    stack<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char f = infix[i];

        if (isalnum(f)) {
            postfix += f;
        }
        else if (f == '(') {
            stack.push(f);
        }
        else if (f == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else {
            while (!stack.empty() && priority(f) <= priority(stack.top())) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(f);
        }
    }

    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

double evaluatePostfix(string postfix, double a, double b, double c, double d, double e) {
    stack<double> stack;

    for (int i = 0; i < postfix.length(); i++) {
        char f = postfix[i];

        if (isalpha(f)) {
            switch (f) {
            case 'a':
                stack.push(a);
                break;
            case 'b':
                stack.push(b);
                break;
            case 'c':
                stack.push(c);
                break;
            case 'd':
                stack.push(d);
                break;
            case 'e':
                stack.push(e);
                break;
            }
        }
        else {
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();
            switch (f) {
            case '+':
                stack.push(operand1 + operand2);
                break;
            case '-':
                stack.push(operand1 - operand2);
                break;
            case '*':
                stack.push(operand1 * operand2);
                break;
            case '/':
                stack.push(operand1 / operand2);
                break;
            case '^':
                stack.push(pow(operand1, operand2));
                break;
            }
        }
    }

    return stack.top();
}

int main() {
    string infix = "a/(b*(c+d))-e";
    double a, b, c, d, e;

    cout << "Enter the value of a: ";
    cin >> a;
    cout << "Enter the value of b: ";
    cin >> b;
    cout << "Enter the value of c: ";
    cin >> c;
    cout << "Enter the value of d: ";
    cin >> d;
    cout << "Enter the value of e: ";
    cin >> e;

    string postfix = infixToPostfix(infix);

    double result = evaluatePostfix(postfix, a, b, c, d, e);

    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;

    return 0;
}
