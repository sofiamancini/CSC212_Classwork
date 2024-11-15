#pragma once
#include "Animal.h"

class Hamster : public Animal{
public:
    Hamster(float initial_hunger, float initial_thirst) : Animal(initial_hunger, initial_thirst){};
    void Speak() { std::cout << "Squeak!" << std::endl; }
};