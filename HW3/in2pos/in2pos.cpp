#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>

int first(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isCarrot(char op) {
    if (op == '^') return true;
    return false;
}


std::string in2pos(const std::string& infix) {
    std::stack<char> operators;
    std::vector<std::string> output;
    std::istringstream iss(infix);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            output.push_back(token);
        } else if (token == "(") {
            operators.push('(');
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && first(operators.top()) >= first(token[0]) &&
                   (!isCarrot(token[0]) || first(operators.top()) > first(token[0]))) {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    std::string postfix;
    for (const std::string& s : output) {
        postfix += s + " ";
    }
    return postfix;
}

int main(int argc, char* argv[]) {
    std::string infix = argv[1];
    std::string postfix = in2pos(infix);
    std::cout << postfix << std::endl;

    return 0;
}