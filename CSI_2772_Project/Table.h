#ifndef TABLE
#define TABLE


#include <iostream>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
using namespace std;


class Table {
    Player player1;
    Player player2;
    DiscardPile discard;
    Deck deck;
    TradeArea trade;
public:
    Table() {};
    Table(Player,Player,Deck,DiscardPile,TradeArea);
    Table(istream&, const CardFactory*);
    bool win(std::string&);
    void printHand(bool);
    friend ostream& operator << (ostream& o, const Table& p);

    //added
    TradeArea& getTradeArea();
    void displayTable();
    Deck& getDeck();
    DiscardPile& getDiscardPile();
};

#endif