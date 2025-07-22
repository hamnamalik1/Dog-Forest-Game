//
// Created by Hamna Malik on 9/17/24.
#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <string>

class Dog {
    friend class Board; // Allows Board class to access Dog's private fields

private:
    std::string name; // Dog's name
    int strength;     // Dog's current strength
    int x;            // x coordinate of dog on the board
    int y;            // y coordinate of dog on the board

public:
    // Constructors
    Dog(std::string n);
    Dog();

    // Methods
    bool changeStrength(int amt); // Modifies strength, checks if strength is > 0
    void die();                   // Message when dog dies
    void printDog();               // Prints dog info
    void won();                    // Message when dog wins
    void reset();                  // Resets dog's state for a new game
};

#endif // DOG_HPP