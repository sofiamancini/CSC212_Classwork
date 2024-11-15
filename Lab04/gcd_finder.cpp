#include <iostream>

int gcdFinder(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcdFinder(b, a % b);
}

int main(int argc, char* argv[]) {

    int num1 = std::stoi(argv[1]);
    int num2 = std::stoi(argv[2]);

    std::cout << gcdFinder(num1, num2) << std::endl;

    return 0;

}