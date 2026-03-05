#include "FlatBonus.h"

FlatBonus::FlatBonus(std::string modifierName, int bonusValue) 
    : name(modifierName), bonus(bonusValue) {}

int FlatBonus::apply(int currentScore) {
    return currentScore + bonus;
}

std::string FlatBonus::getName() {
    return name + " (+" + std::to_string(bonus) + " Points)";
}