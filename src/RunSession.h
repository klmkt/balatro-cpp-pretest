#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <vector>
#include <string>

// Struktur data untuk Kartu
struct Card {
    std::string suit;
    std::string rank;
    int value; // Nilai dasar kartu (contoh: K = 10, A = 11)
};

class RunSession {
private:
    int currentRound;
    const int maxRounds = 3;
    int score;
    
    // Tambahan untuk sistem kartu
    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> playedCards; // Kartu yang dipilih user
    
    void initDeck();
    void drawHand(int count);

public:
    RunSession();
    void startRun();
    void playHand();
    void calculateScore();
    void enterShop();
    void endRun();
    
    void gameLoop(); 
};

#endif