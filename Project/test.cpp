#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <stack>

int mystery (std::stack<int> stack) {
    int result = 0;
    int loop = stack.size();
    for (int i = 0; i < loop; i++) {
        if( !(i % 2) ) {
            result += stack.top();
        } else {
            result *= stack.top();
        }
        stack.pop();
    }
    return result;
}

int main() {
    std::stack<int> stack;

    stack.push(7);
    stack.push(20);
    stack.push(300);
    stack.push(5);
    stack.push(10);

    std::cout << mystery(stack) << std::endl;
    return 0;
}