#include <iostream>

void hanoiTower(int num_disks, int source_rod, int destination_rod) {
    if (num_disks == 1) {
        std::cout << "Move disk 1 from tower " << source_rod << " to tower " << destination_rod << std::endl;
        return;
    }
    hanoiTower(num_disks - 1, source_rod, 6 - source_rod - destination_rod);
    std::cout << "Move disk " << num_disks << " from tower " << source_rod << " to tower " << destination_rod << std::endl;
    hanoiTower(num_disks - 1, 6 - source_rod - destination_rod, destination_rod);
} 

int main(int argc, char* argv[]) {

    int num_disks = std::stoi(argv[1]);
    int source_rod = std::stoi(argv[2]);
    int destination_rod = std::stoi(argv[3]);

    hanoiTower(num_disks, source_rod, destination_rod);

    return 0;

}