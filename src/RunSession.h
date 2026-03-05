#ifndef RUNSESSION_H
#define RUNSESSION_H

#include "Card.h"
#include "ScoringSystem.h"
#include <vector>
#include <string>



class RunSession {
private:
    int currentRound;
    const int maxRounds = 3;
    int score;
    ScoringSystem* scoringSystem;
    
    // Tambahan untuk sistem kartu
    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> playedCards; // Kartu yang dipilih user
    
    void initDeck();
    void drawHand(int count);

public:
    RunSession();
    ~RunSession();
     
    void startRun();
    void playHand();
    void calculateScore();
    void enterShop();
    void endRun();
    
    void gameLoop(); 
};

#endif