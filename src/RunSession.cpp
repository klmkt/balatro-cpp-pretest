#include "RunSession.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

RunSession::RunSession() : currentRound(1), score(0) {
    initDeck();
    scoringSystem = new ScoringSystem(new StandardScoringStrategy());
    shopSystem = new ShopSystem(); // Inisialisasi Shop
}

RunSession::~RunSession() {
    delete scoringSystem;
    delete shopSystem;
    // Bersihkan memori dari modifier yang udah dibeli
    for (auto mod : activeModifiers) {
        delete mod;
    }
    activeModifiers.clear();
}

void RunSession::initDeck() {
    deck.clear();
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    // Bikin 52 kartu
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 13; ++j) {
            deck.push_back({suits[i], ranks[j], values[j]});
        }
    }

    // Kocok kartu (Shuffle)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void RunSession::drawHand(int count) {
    hand.clear();
    for(int i = 0; i < count; ++i) {
        if(!deck.empty()) {
            hand.push_back(deck.back());
            deck.pop_back();
        }
    }
}

void RunSession::startRun() {
    std::cout << "=== Starting New Run ===" << std::endl;
}

void RunSession::playHand() {
    std::cout << "\n--- Round " << currentRound << " ---" << std::endl;
    
    // Tarik 8 kartu ke tangan
    drawHand(8);
    playedCards.clear();
    
    std::cout << "Your Hand:" << std::endl;
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << "[" << i << "] " << hand[i].rank << " of " << hand[i].suit 
                  << " (Val: " << hand[i].value << ")" << std::endl;
    }

    int numToPlay;
    std::cout << "\nHow many cards do you want to play? (1-5): ";
    std::cin >> numToPlay;
    
    // Validasi input
    if (numToPlay < 1) numToPlay = 1;
    if (numToPlay > 5) numToPlay = 5;
    if (numToPlay > hand.size()) numToPlay = hand.size();

    std::cout << "Enter the index number of the cards you want to play one by one:" << std::endl;
    for (int i = 0; i < numToPlay; ++i) {
        int index;
        std::cout << "Card " << i + 1 << " index: ";
        std::cin >> index;
        
        if (index >= 0 && index < hand.size()) {
            playedCards.push_back(hand[index]);
        } else {
            std::cout << "Invalid index! Skipping..." << std::endl;
        }
    }
    
    std::cout << "\nPlaying hand with " << playedCards.size() << " cards..." << std::endl;
}

void RunSession::calculateScore() {
    std::cout << "\nCalculating score..." << std::endl;
    
    // 1. Dapatkan Base Score dari Scoring System (Strategy)
    int roundScore = scoringSystem->evaluateScore(playedCards);
    std::cout << "Base Score from cards & combos: " << roundScore << std::endl;

    // 2. Terapkan efek modifier satu per satu (Decorator/Pipeline)
    if (!activeModifiers.empty()) {
        std::cout << "Applying Modifiers..." << std::endl;
        for (auto mod : activeModifiers) {
            roundScore = mod->apply(roundScore); // Timpa skor dengan skor yang udah dimodif
            std::cout << "  -> " << mod->getName() << " applied. Score becomes: " << roundScore << std::endl;
        }
    }

    // 3. Masukkan ke total skor game
    score += roundScore;
    
    std::cout << "Final Score for Round " << currentRound << ": " << roundScore << std::endl;
    std::cout << "Current Total Game Score: " << score << std::endl;
}

void RunSession::enterShop() {
    // Panggil shop dan tangkap modifier yang dibeli
    IModifier* boughtModifier = shopSystem->openShop();
    
    // Kalau user beli (nggak skip), masukin ke list modifier aktif
    if (boughtModifier != nullptr) {
        activeModifiers.push_back(boughtModifier);
    }
}

void RunSession::endRun() {
    std::cout << "\n=== Run Ended ===" << std::endl;
    std::cout << "Final Score: " << score << std::endl;
}

void RunSession::gameLoop() {
    startRun();
    while (currentRound <= maxRounds) {
        playHand();
        calculateScore();
        enterShop();
        currentRound++;
    }
    endRun();
    
}