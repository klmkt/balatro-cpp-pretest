#ifndef SCORINGSYSTEM_H
#define SCORINGSYSTEM_H

#include <vector>
#include "Card.h"

// Behavioral Pattern: Strategy Interface
class IScoringStrategy {
public:
    virtual ~IScoringStrategy() = default;
    virtual int calculateBaseScore(const std::vector<Card>& playedCards) = 0;
};

// Concrete Strategy: Aturan skor buatan kita sendiri (Bukan Balatro)
class StandardScoringStrategy : public IScoringStrategy {
public:
    int calculateBaseScore(const std::vector<Card>& playedCards) override;
};

// Context Class
class ScoringSystem {
private:
    IScoringStrategy* strategy;

public:
    ScoringSystem(IScoringStrategy* initialStrategy);
    ~ScoringSystem();

    void setStrategy(IScoringStrategy* newStrategy);
    int evaluateScore(const std::vector<Card>& playedCards);
};

#endif