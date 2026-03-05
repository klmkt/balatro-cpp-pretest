#ifndef FLATBONUS_H
#define FLATBONUS_H

#include "IModifier.h"
#include <string>

class FlatBonus : public IModifier {
private:
    int bonus;
    std::string name;

public:
    FlatBonus(std::string modifierName, int bonusValue);
    int apply(int currentScore) override;
    std::string getName() override;
};

#endif