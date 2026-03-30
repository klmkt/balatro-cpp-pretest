"# balatro-cpp-pretest" 
"# balatro-cpp-pretest" 
Architecture Overview

This project is a text-based card-run game prototype built in C++ to demonstrate the application of software design patterns. Below are the major classes and their roles:

    RunSession: The core controller of the game. It manages the main game loop (startRun, playHand, calculateScore, enterShop), holds the player's deck, hand, and current score, and acts as the client that integrates the Scoring, Shop, and Modifier systems.

    ScoringSystem & StandardScoringStrategy: Encapsulates the logic for calculating the base score of the cards played by the user, including custom combinations/combos.

    ShopSystem: Handles user interactions between rounds, allowing the player to purchase modifiers to boost their score.

    ModifierFactory: A centralized creator class responsible for instantiating different types of modifier objects based on user selection.

    IModifier (and concrete classes like FlatBonus, Multiplier): Represents the items/modifiers that alter the player's score. Each concrete class implements its own specific mathematical effect.

Pattern Usage

This project implements three primary design patterns as required:

    Creational Pattern (Factory Method): * Implemented in ModifierFactory.

        Usage: The ShopSystem does not instantiate FlatBonus or Multiplier directly. Instead, it calls ModifierFactory::createModifier("Flat", ...) which handles the object creation. This centralizes creation logic and makes the system easily extensible for new modifier types.

    Structural Pattern (Decorator Pattern): * Implemented in RunSession::calculateScore() using the IModifier interface.

        Usage: Modifiers act as decorators around the base score. Instead of modifying objects visually, they modify the integer score value in a pipeline. The score is passed through a list of active modifiers (activeModifiers), where each modifier sequentially applies its effect (e.g., adding a flat bonus, then multiplying the result) and passes it to the next.

    Behavioral Pattern (Strategy Pattern): * Implemented via the IScoringStrategy interface and ScoringSystem context.

        Usage: The rules for calculating points from played cards (base score) are extracted out of RunSession and put into StandardScoringStrategy. This allows the game to easily swap scoring rules (e.g., for a "Hard Mode") at runtime without changing the main game loop code.

Modification Log: Adding SquareScoreModifier

To demonstrate the extensibility of the Factory and Decorator patterns, a new modifier (SquareScoreModifier) was added to the game with minimal changes to existing code.
Steps taken:

    Created src/modifiers/SquareScoreModifier.h and src/modifiers/SquareScoreModifier.cpp which inherit from the IModifier interface.

    Implemented the apply(int currentScore) function to return currentScore * currentScore.

    Updated src/ModifierFactory.cpp by including the new header and adding a simple else if (type == "Square") condition to instantiate the new class.

    No changes were needed in RunSession or ShopSystem core logic, proving the Open/Closed Principle.

AI Usage Disclosure

Generative AI (Google Gemini) was used as an interactive tutor and coding assistant during the development of this project.

    What AI helped with: The AI assisted in structuring the C++ boilerplate code, explaining the conceptual differences between design patterns (Factory, Decorator, Strategy), resolving g++ compilation and Git tracking errors (e.g., removing binary files via .gitignore), and brainstorming generic modifier names/combos to strictly adhere to the assignment's anti-plagiarism policy regarding Balatro.