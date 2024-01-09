#include "Hand.h"

std::ostream& operator<< (std::ostream& o,const Hand& h) {
    for (Card* cardPtr: h.hand) {
        o << *cardPtr;
    }
    return o;
}

void Hand::displayHand()
{
    std::cout << "[ ";
    for (const Card* cardPtr : hand) {
        std::cout << cardPtr->getName() << " ";
    }
    std::cout << "]" << std::endl;
}

Card* Hand::removeCard(int pos)
{
    auto it = hand.begin();
    std::advance(it, pos);
    Card* removed = *it;

    hand.erase(it);
    return removed;
}

Hand& Hand:: operator+=(Card* card) {

    hand.push_back(card);
    return *this;
}

Card* Hand::play() {
    if (hand.empty()) {
        return nullptr;
    }
    Card* top = hand.front();
    hand.pop_front();
    return top;
}

Card* Hand::top() {
    if (hand.empty()) {
        return nullptr;
    }
    return hand.front();
}

Card* Hand::operator[](int pos) {
    std::list<Card*>::iterator it = hand.begin();
    advance(it, pos);
    Card* card =  *it;
    hand.erase(it);
    return card;
}

Hand::Hand(std::istream& i, const CardFactory* cf){

    std::ifstream* handFile = dynamic_cast<std::ifstream*>(&i);

    if (!handFile->is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    std::string line;
    if (std::getline(*handFile, line)) {

        for (char c : line) {
            hand.push_back(cf->createCard(std::string(1,c)));
        }
    }
    else {
        std::cout << "Empty file" << std::endl;
    }
    handFile->close();
}

int Hand::getSize()
{
    return hand.size();
}
