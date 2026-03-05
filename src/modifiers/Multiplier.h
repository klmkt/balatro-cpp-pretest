#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "IModifier.h"
#include <string>

class Multiplier : public IModifier {
private:
    int multiplierValue;
    std::string name;

public:
    Multiplier(std::string modifierName, int value);
    int apply(int currentScore) override;
    std::string getName() override;
};

#endif