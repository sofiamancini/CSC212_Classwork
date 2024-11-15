#include <iostream>
#include <vector>

void createPerms(std::vector<int>& arr, int start, int end) {
    if (start == end) {
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    } else {
        for (int i = start; i <= end; i++) {
            std::swap(arr[start], arr[i]);
            createPerms(arr, start + 1, end);
            std::swap(arr[start], arr[i]);
        }
    }
}

void listPerms(int n) {
    std::vector<int> arr;
    for (int i = 1; i <= n; i++) {
        arr.push_back(i);
    }
    createPerms(arr, 0, n - 1);
}

int main(int argc, char* argv[]) {

    int num = std::stoi(argv[1]);

    listPerms(num);

    return 0;

}