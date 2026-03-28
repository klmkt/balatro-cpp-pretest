#ifndef MODIFIERFACTORY_H
#define MODIFIERFACTORY_H

#include "modifiers/IModifier.h"
#include <string>

// Creational Pattern: Factory Class
class ModifierFactory {
public:
    // Fungsi statis untuk mencetak/membuat modifier baru
    static IModifier* createModifier(const std::string& type, const std::string& name, int value);
};

#endif