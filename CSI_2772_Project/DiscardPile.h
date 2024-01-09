#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include "Card.h"
#include "CardFactory.h"
#include <vector>


class DiscardPile {
    std::vector<Card*> discardPile;
public:
    DiscardPile() {};
    DiscardPile& operator+=(Card*);
    Card* pickUp();
    Card* top() const;
    void print(std::ostream&);
    DiscardPile(std::istream&, const CardFactory*);
    friend std::ostream& operator << (std::ostream & o, const DiscardPile& d);
    int size();
    void display();
};


#endif