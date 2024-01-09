#include "Table.h"

std::ostream& operator<< (std::ostream& o, const Table& t) {
    o << t.player1;
    o << t.player2;
    o << t.discard;
    o << t.deck;
    o << t.trade;
    return o;
}

Table::Table(istream& i, const CardFactory* cf)
{
}

bool Table::win(std::string& name) {
    if (deck.size() == 0) {
        if (name == player1.getName()) {
            if (player1.getNumCoins() > player2.getNumCoins()) {
                return true;
            }
        }
        else if(name == player2.getName()){
            if (player2.getNumCoins() > player1.getNumCoins()) {
                return true;
            }
        }
        else {
            std::cout << "Incorrect player name" << std::endl;
        }
    }
    return false;
}

void Table::printHand(bool b) {
    if (player1.isActive()) {
        if (b) {
            cout << player1.getHand();
        }
        else {
            cout << *(player1.getHand().top());
        }
    }
    else {
        if (b) {
            cout << player2.getHand();
        }
        else {
            cout << *(player2.getHand().top());
        }
    }
}

TradeArea& Table::getTradeArea() {
    return trade;
}

void Table::displayTable() {
    trade.displayTradeArea();
}

Deck& Table::getDeck()
{
    return deck;
}

DiscardPile& Table::getDiscardPile()
{
    return discard;
}

Table::Table(Player p1, Player p2, Deck d, DiscardPile dp, TradeArea tA) {
    player1 = p1;
    player2 = p2;
    discard = dp;
    trade = tA;
    deck = d;
}