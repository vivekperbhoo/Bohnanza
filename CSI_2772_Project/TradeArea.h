#ifndef TRADEAREA_H
#define TRADEAREA_H

#include "CardFactory.h"
#include "Card.h"
#include "Chain_Base.h"
#include <list>
#include <unordered_map>
#include <string>


class TradeArea {
private:
    std::unordered_map<std::string, int> map;
    std::list<Card*> tradeArea;
public:
    void updateMap();
    TradeArea() {};
    TradeArea(std::istream&, const CardFactory*);
    TradeArea& operator+=(Card*);
    bool legal(Card*);
    Card* trade(std::string);
    int numCards();
    friend std::ostream& operator << (std::ostream&,const TradeArea&);

    //added 
    Card* removeCard();
    std::unordered_map<std::string, int> getMap() const;
    std::list<Card*> getTradeArea() const;
    void displayTradeArea();
    int getNumChains();
};

#endif