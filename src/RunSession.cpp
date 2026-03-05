#include "RunSession.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

RunSession::RunSession() : currentRound(1), score(0) {
    initDeck();
    scoringSystem = new ScoringSystem(new StandardScoringStrategy());
}

RunSession::~RunSession() {
    delete scoringSystem;
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
    std::cout << "\nCalculating base score..." << std::endl;
    
    // Panggil ScoringSystem buat ngitung (Ini namanya delegasi, ciri khas Strategy Pattern)
    int roundScore = scoringSystem->evaluateScore(playedCards);
    
    score += roundScore;
    
    std::cout << "Base Chips from cards and combos: " << roundScore << std::endl;
    std::cout << "Current Total Score: " << score << std::endl;
}

void RunSession::enterShop() {
    std::cout << "\n--- Shop ---" << std::endl;
    std::string choice;
    
    std::cout << "Welcome to the Shop! Buy a modifier? (y/n): ";
    std::cin >> choice;
    
    if (choice == "y" || choice == "Y") {
        std::cout << "Modifier bought! (Effect will be implemented later)" << std::endl;
    } else {
        std::cout << "Skipping shop." << std::endl;
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