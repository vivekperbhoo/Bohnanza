#ifndef HAND_H
#define HAND_H


#include <iostream>
#include "CardFactory.h"
#include <list>
#include "Card.h"

class Hand {
    std::list<Card*> hand;
public:
    Hand() {};
    Hand& operator+=(Card*);
    Card* play();
    Card* top();
    Card* operator[](int);
    friend std::ostream& operator << (std::ostream& o,const Hand& h);
    Hand(std::istream&, const CardFactory*);
    int getSize();
    void displayHand();
    Card* removeCard(int pos);

};


#endif