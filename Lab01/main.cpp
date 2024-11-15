#include "Cat.h"
#include "Dog.h"
#include "Hamster.h"
#include "Snake.h"
#include "Bird.h"


int main(){

    float hunger_arr[5] = {0, 20, 40, 60, 80};
    float thirst_arr[5] = {10, 30, 50, 70, 90};
    float eat_amount = 25;
    float drink_amount = 50;

    Cat cat1(hunger_arr[0], thirst_arr[0]);	
    Dog dog1(hunger_arr[1], thirst_arr[1]);
    Bird bird1(hunger_arr[2], thirst_arr[2]);
    Hamster hamster1(hunger_arr[3], thirst_arr[3]);
    Snake snake1(hunger_arr[4], thirst_arr[4]);

    std::cout << "Cat hunger: " << cat1.GetHunger() << std::endl;
    std::cout << "Dog hunger: " << dog1.GetHunger() << std::endl;
    std::cout << "Bird hunger: " << bird1.GetHunger() << std::endl;
    std::cout << "Hamster hunger: " << hamster1.GetHunger() << std::endl;
    std::cout << "Snake hunger: " << snake1.GetHunger() << std::endl;

    std::cout << std::endl;

    cat1.Eat(eat_amount);
    dog1.Eat(eat_amount);
    bird1.Eat(eat_amount);
    hamster1.Eat(eat_amount);
    snake1.Eat(eat_amount);

    std::cout << "Cat hunger: " << cat1.GetHunger() << std::endl;
    std::cout << "Dog hunger: " << dog1.GetHunger() << std::endl;
    std::cout << "Bird hunger: " << bird1.GetHunger() << std::endl;
    std::cout << "Hamster hunger: " << hamster1.GetHunger() << std::endl;
    std::cout << "Snake hunger: " << snake1.GetHunger() << std::endl;

    std::cout << std::endl;

    cat1.Speak();
    dog1.Speak();
    bird1.Speak();
    hamster1.Speak();
    snake1.Speak();

    std::cout << std::endl;

    std::cout << "Cat thirst: " << cat1.GetThirst() << std::endl;
    std::cout << "Dog thirst: " << dog1.GetThirst() << std::endl;
    std::cout << "Bird thirst: " << bird1.GetThirst() << std::endl;
    std::cout << "Hamster thirst: " << hamster1.GetThirst() << std::endl;
    std::cout << "Snake thirst: " << snake1.GetThirst() << std::endl;

    std::cout << std::endl;

    cat1.Drink(drink_amount);
    dog1.Drink(drink_amount);
    bird1.Drink(drink_amount);
    hamster1.Drink(drink_amount);
    snake1.Drink(drink_amount);

    std::cout << "Cat thirst: " << cat1.GetThirst() << std::endl;
    std::cout << "Dog thirst: " << dog1.GetThirst() << std::endl;
    std::cout << "Bird thirst: " << bird1.GetThirst() << std::endl;
    std::cout << "Hamster thirst: " << hamster1.GetThirst() << std::endl;
    std::cout << "Snake thirst: " << snake1.GetThirst() << std::endl;

    return 0;
}