#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "Card.h"
#include <fstream>
#include <string>

class CardFactory;

class Deck : public std::vector<Card*> {
public:
    Deck() {};
    friend std::ostream& operator << (std::ostream& o, const Deck& d);
    Deck(std::istream&, const CardFactory*);
    Card* draw();
};


#endif