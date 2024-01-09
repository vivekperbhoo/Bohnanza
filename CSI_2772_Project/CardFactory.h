#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <string>


class CardFactory {
private:
    static CardFactory* cardFactory;
    std::string dFileName;
    CardFactory();
public:
    static CardFactory* getFactory();
    Deck getDeck();
    Card* createCard(std::string card) const;
};

#endif