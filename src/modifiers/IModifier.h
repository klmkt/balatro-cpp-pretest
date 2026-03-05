#ifndef IMODIFIER_H
#define IMODIFIER_H

#include <string>

class IModifier {
public:
    virtual ~IModifier() = default;
    
    // Fungsi untuk memanipulasi skor
    virtual int apply(int currentScore) = 0;
    
    // Fungsi untuk mendapatkan nama modifier
    virtual std::string getName() = 0;
};

#endif