#include "CardFactory.h"
#include <algorithm>
#include <ctime>
#include <random>


CardFactory* CardFactory::cardFactory = nullptr;

CardFactory::CardFactory() {
    dFileName = "Deck.txt";
    std::ofstream deckFile(dFileName);
    
    for (int i = 0; i < 10; ++i) deckFile << "b" << std::endl;
    for (int i = 0; i < 20; ++i) deckFile << "B" << std::endl;
    for (int i = 0; i < 18; ++i) deckFile << "C" << std::endl;
    for (int i = 0; i < 8; ++i) deckFile << "R" << std::endl;
    for (int i = 0; i < 14; ++i) deckFile << "G" << std::endl;
    for (int i = 0; i < 12; ++i) deckFile << "s" << std::endl;
    for (int i = 0; i < 16; ++i) deckFile << "S" << std::endl;
    for (int i = 0; i < 6; ++i) deckFile << "g" << std::endl;

    deckFile.close();
}


CardFactory* CardFactory::getFactory() {
    if (cardFactory == nullptr) {
        cardFactory = new CardFactory();
    }
    return cardFactory;
}

Deck CardFactory::getDeck()
{
    std::ifstream deckFile(dFileName);
    Deck deck(deckFile, this);

    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

    std::shuffle(deck.begin(), deck.end(), generator);
    return deck;
}

Card* CardFactory::createCard(std::string card) const {
    if (card == "Blue" || card=="B") {
        return (new Blue());
    }
    else if (card == "Black" || card == "b") {
        return (new Black());
    } 
    else if (card == "Chili" || card == "C") {
        return (new Chili());
    } 
    else if (card == "Red" || card == "R") {
        return (new Red());
    }
    else if (card == "Green" || card == "G") {
        return (new Green());
    }
    else if (card == "Garden" || card == "g") {
        return (new Garden());
    }
    else if (card == "Soy" || card == "s") {
        return (new Soy());
    }
    else if (card == "Stink" || card == "S") {
        return (new Stink());
    }
}