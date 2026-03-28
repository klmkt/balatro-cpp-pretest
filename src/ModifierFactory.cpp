#include "ModifierFactory.h"
#include "modifiers/FlatBonus.h"
#include "modifiers/Multiplier.h"
#include <iostream>

IModifier* ModifierFactory::createModifier(const std::string& type, const std::string& name, int value) {
    if (type == "Flat") {
        return new FlatBonus(name, value);
    } 
    else if (type == "Mult") {
        return new Multiplier(name, value);
    } 
    else {
        std::cout << "Error: Unknown modifier type!" << std::endl;
        return nullptr;
    }
}