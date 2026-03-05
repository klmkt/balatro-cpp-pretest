#include "Multiplier.h"

Multiplier::Multiplier(std::string modifierName, int value)
    : name(modifierName), multiplierValue(value) {}

int Multiplier::apply(int currentScore) {
    return currentScore * multiplierValue;
}

std::string Multiplier::getName() {
    return name + " (x" + std::to_string(multiplierValue) + " Multiplier)";
}