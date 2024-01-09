#include "TradeArea.h"

std::ostream& operator<< (std::ostream& o, const TradeArea& t) {
    for (const Card* cardPtr : t.tradeArea) {
        o << (*cardPtr);
    }
    return o;
}


TradeArea& TradeArea:: operator+=(Card* c) {
    tradeArea.push_back(c);
    updateMap();
    return *this;
}

bool TradeArea::legal(Card* c) {
    for (const Card* cPtr : tradeArea) {
        if ((cPtr->getName()) == (c->getName())) {
            return true;
        }
    }
    return false;
}

Card* TradeArea::trade(std::string s) {
    for (std::list<Card*>::iterator it = tradeArea.begin(); it != tradeArea.end(); ++it) {
        if ((*it)->getName() == s) {
            Card* removed = *it;
            tradeArea.erase(it);
            updateMap();
            return removed;
        }
    }
    return nullptr;
}

int TradeArea::numCards() {
    return tradeArea.size();
}

std::unordered_map<std::string, int> TradeArea::getMap() const{
    return map;
}

std::list<Card*> TradeArea::getTradeArea() const {
    return tradeArea;
}

void TradeArea::displayTradeArea() {
    updateMap();
    std::cout << "Trade Area: " << std::endl;
    for (const auto& pair : map) {
        if (pair.second != 0) {
            std::cout << pair.first << " : " << pair.second << " cards" << std::endl;
        }
    }
}

int TradeArea::getNumChains() {
    updateMap();
    int num = 0;
    for (const auto& pair : map) {
        if (pair.second != 0) {
            num++;
        }
    }
    return num;
}

void TradeArea::updateMap(){
    map.clear();

    for (const Card* card : tradeArea) {
        if (card->getName() == "Blue") {
            map["Blue"]++;
        }
        else if (card->getName() == "Chili") {
            map["Chili"]++;
        }
        else if (card->getName() == "Stink") {
            map["Stink"]++;
        }
        else if (card->getName() == "Green") {
            map["Green"]++;
        }
        else if (card->getName() == "Garden") {
            map["Garden"]++;
        }
        else if (card->getName() == "Soy") {
            map["Soy"]++;
        }
        else if (card->getName() == "Black") {
            map["Black"]++;
        }
        else if (card->getName() == "Red") {
            map["Red"]++;
        }
    }
}

TradeArea::TradeArea(std::istream& i, const CardFactory* cf) {
    std::ifstream* tradeFile = dynamic_cast<std::ifstream*>(&i);

    if (!tradeFile->is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    std::string line;
    if (std::getline(*tradeFile, line)) {

        for (char c : line) {
            tradeArea.push_front(cf->createCard(std::string(1, c)));
        }
    }
    else {
        std::cout << "Empty file" << std::endl;
    }
    tradeFile->close();
}

Card* TradeArea::removeCard() {
    if (tradeArea.size() == 0) {
        return nullptr;
    }
    Card* removed = tradeArea.back();
    tradeArea.pop_back();
    return removed;
}