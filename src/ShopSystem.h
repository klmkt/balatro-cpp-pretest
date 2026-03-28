#ifndef SHOPSYSTEM_H
#define SHOPSYSTEM_H

#include "modifiers/IModifier.h"

class ShopSystem {
public:
    // Mengembalikan pointer ke modifier yang dibeli, atau nullptr kalau skip
    IModifier* openShop(); 
};

#endif