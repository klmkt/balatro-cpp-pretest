#include "ScoringSystem.h"
#include <iostream>
#include <map>

// Logika skor buatan kita
int StandardScoringStrategy::calculateBaseScore(const std::vector<Card>& playedCards) {
    int totalValue = 0;
    std::map<std::string, int> suitCounts;
    std::map<std::string, int> rankCounts;

    for (const auto& card : playedCards) {
        totalValue += card.value;
        suitCounts[card.suit]++;
        rankCounts[card.rank]++;
    }

    int comboBonus = 0;

    // Custom Combo 1: "Color Sync" (Pengganti konsep Flush)
    if (playedCards.size() > 1) {
        bool allSameSuit = false;
        for (const auto& pair : suitCounts) {
            if (pair.second == playedCards.size()) {
                allSameSuit = true;
                break;
            }
        }
        if (allSameSuit) {
            std::cout << "  -> Combo Activated: Color Sync! (+50 points)\n";
            comboBonus += 50;
        }
    }

    // Custom Combo 2: "Duplicate Power" (Pengganti konsep Pair)
    bool hasPair = false;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 2) {
            hasPair = true;
            break;
        }
    }
    if (hasPair) {
        std::cout << "  -> Combo Activated: Duplicate Power! (+20 points)\n";
        comboBonus += 20;
    }

    return totalValue + comboBonus;
}

// Implementasi Context Class
ScoringSystem::ScoringSystem(IScoringStrategy* initialStrategy) : strategy(initialStrategy) {}

ScoringSystem::~ScoringSystem() {
    delete strategy;
}

void ScoringSystem::setStrategy(IScoringStrategy* newStrategy) {
    delete strategy;
    strategy = newStrategy;
}

int ScoringSystem::evaluateScore(const std::vector<Card>& playedCards) {
    if (!strategy) return 0;
    return strategy->calculateBaseScore(playedCards);
}