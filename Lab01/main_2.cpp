#include "Cat.h"
#include "Dog.h"
#include "Bird.h"
#include "Hamster.h"
#include "Snake.h"
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char*argv[]){

    // Extract # of animals we're expecting to read from the CLA
    int num_animals = std::stoi(argv[1]);

    // Extract the name of the file we'll be reading from the CLA
    std::string file_name = argv[2];

	// Create a collection (data structure) of the appropriate size to hold the # of animals we are creating
    Animal** animals = new Animal*[num_animals];
	std::ifstream file(file_name);
	// Loop through the number of animals we have.
    for(int i = 0; i < num_animals; i++){
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            float hunger;
            float thirst;
            iss >> type >> hunger >> thirst;
            if(type == "Cat"){
                animals[i] = new Cat(hunger, thirst);
            } else if(type == "Dog"){
                animals[i] = new Dog(hunger, thirst);
            } else if(type == "Bird"){
                animals[i] = new Bird(hunger, thirst);
            } else if(type == "Hamster"){
                animals[i] = new Hamster(hunger, thirst);
            } else if(type == "Snake"){
                animals[i] = new Snake(hunger, thirst);
            }
        }
    }

    file.close();

    for(int i = 0; i < num_animals; i++){
        animals[i]->Speak();
        std::cout << animals[i]->GetHunger() << std::endl;
        std::cout << animals[i]->GetThirst() << std::endl;
    }

    for(int i = 0; i < num_animals; i++){
        delete animals[i];
    }

    delete[] animals;

	return 0;
}