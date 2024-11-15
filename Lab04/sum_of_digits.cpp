#include <iostream>

int sum_of_digits(int n) {
    if (n / 10 == 0) {
        return n;
    }
    return n % 10 + sum_of_digits(n / 10);
}

int main(int argc, char* argv[]) {

    int num = std::stoi(argv[1]);

    std::cout << sum_of_digits(num) << std::endl;

    return 0;

}