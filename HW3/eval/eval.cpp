#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cstdlib>
#include <cmath>

int eval(const std::string& postfix) {
    std::stack<int> stack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            stack.push(std::stoi(token));
        } else {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result;

            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b;
break;
                case '^': result = static_cast<int>(std::pow(a, b)); break;
            }

            stack.push(result);
        }
    }

    return stack.top();
}

int main(int argc, char* argv[]) {

    std::string postfix;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) {
            postfix += " ";
        }
        postfix += argv[i];
    }

    int result = eval(postfix);
    std::cout << result << std::endl;

    return 0;
}