#include "ShopSystem.h"
#include "ModifierFactory.h"
#include <iostream>

IModifier* ShopSystem::openShop() {
    std::cout << "\n=== Welcome to the Modifier Shop! ===" << std::endl;
    std::cout << "1. Buy 'Flat Boost' (+50 points) - Type 1" << std::endl;
    std::cout << "2. Buy 'Double Power' (x2 multiplier) - Type 2" << std::endl;
    std::cout << "3. Skip Shop - Type 3" << std::endl;
    std::cout << "Choose an option (1-3): ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "-> You bought Flat Boost!" << std::endl;
        // Panggil Factory buat nyiptain modifiernya
        return ModifierFactory::createModifier("Flat", "Flat Boost", 50);
    } else if (choice == 2) {
        std::cout << "-> You bought Double Power!" << std::endl;
        return ModifierFactory::createModifier("Mult", "Double Power", 2);
    } else {
        std::cout << "-> You skipped the shop." << std::endl;
        return nullptr;
    }
}