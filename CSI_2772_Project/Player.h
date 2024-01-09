#ifndef PLAYER
#define PLAYER

#include "Hand.h"
#include <iostream>
#include "Chain.h"
#include "Chain_Base.h"
#include "NotEnoughCoinsException.h"
#include "TradeArea.h"
#include "CardFactory.h"

class Player {
private:
    bool active;
    bool thirdChain;
    Hand hand;
    int coins;
    std::vector<Chain_Base*> chain;
    std::string name;
public:
    Player(): coins(0), active(false),thirdChain(false),name("") {};
    Player(std::string&);
    std::string getName();
    int getNumCoins();
    Player& operator+=(int);
    int getMaxNumChains() const;
    int getNumChains() const;
    Chain_Base& operator[](int i);
    void buyThirdChain();
    void printHand(std::ostream&, bool);
    friend std::ostream& operator << (std::ostream& o, const Player& p);
    Player(std::istream&, const CardFactory*);

    //
    void addCardToHand(Card*);
    bool isActive();
    void setActive(bool);
    Hand& getHand();
    friend bool canAddCardFromTradeArea(const TradeArea& t, const Player& p);
    friend bool canAddCardFromTradeArea(const Player& p, std::string cardName);
    void addCardToChain(Card* , int );
    std::vector<Chain_Base*>& getChain();
    void sellChain(std::string fieldType);
    void setHand(Hand&);
};

#endif