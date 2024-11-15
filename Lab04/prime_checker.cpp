#include <iostream>

bool checkPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {

    int num = std::stoi(argv[1]);

    if (checkPrime(num)) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }

    return 0;

}