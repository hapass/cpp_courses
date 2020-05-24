#include <iostream>
#include <stack>

using namespace std;

ostream& operator<<(ostream& stream, stack<string> stack) {
    cout << "<";
    while(!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << ">";
    return stream;
}

string parse_expression(stack<string>& stack) {
    if (stack.empty()) return "";
    if (stack.top() == "+" || 
        stack.top() == "-" ||
        stack.top() == "*" ||
        stack.top() == "/") {
        string op = stack.top();
        stack.pop();
        string rhs = parse_expression(stack);
        string lhs = parse_expression(stack);
        return "(" + lhs + ") " + op + " " + rhs;
    } else {
        string value = stack.top();
        stack.pop();
        return value;
    }
}

int main() {
    string initial_value;
    int operations_count = 0;
    cin >> initial_value >> operations_count;

    stack<string> expression;
    expression.push(initial_value);
    while(operations_count-- > 0) {
        string operation;
        string value;
        cin >> operation >> value;
        expression.push(value);
        expression.push(operation);
    }

    cout << parse_expression(expression) << endl;
    return 0;
}