//
// Created by Hamna Malik on 9/17/24.
//
#include "Dog.hpp"

// Constructor that takes a name and sets initial values
Dog::Dog(std::string n) : name(n), strength(50), x(0), y(0) {}


Dog::Dog() : name("Fluffy"), strength(50), x(0), y(0) {}

// Changes the dog's strength by the given amount and checks if it dies
bool Dog::changeStrength(int amt) {
    strength += amt;
   // printDog();

    // Check if dog's strength is zero or less, call die method if true
    if (strength <= 0) {
        strength=0;
        printDog();
        die();
        return false; // The dog has died
    }
    return true; // The dog is still alive
}

// Prints the death message
void Dog::die() {
    std::cout << "AHH!!! The dog " << name << " has died! You monster!\n";
}

// Prints dog's name and current strength
void Dog::printDog() {
    std::cout << "Dog Name: " << name << ", Strength: " << strength << "\n";
}

// Prints winning message when dog reaches the end
void Dog::won() {
    std::cout << "Congratulations! The dog " << name << " has successfully navigated the forest and won!\n";
}

// Resets the dog to its initial state for a new game
void Dog::reset() {
    strength = 50;
    x = 0;
    y = 0;
    std::cout << "The dog " << name << " has been reset to its starting position with full strength.\n";
}