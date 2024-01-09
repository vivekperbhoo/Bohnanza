#include "Deck.h"
#include "CardFactory.h"

std::ostream& operator<< (std::ostream& o, const Deck& d) {
    for (int i = d.size()-1; i >= 0; i--)
    {
        o << *(d.at(i)) << "\n";
    }
    return o;
}

Deck::Deck(std::istream& i, const CardFactory* c) {
    std::ifstream* deckFile = dynamic_cast<std::ifstream*>(&i);

    if (deckFile->is_open()) {
        std::string line;
        while (std::getline(*deckFile, line)) {
            this->push_back(c->createCard(line));
        }
    }
    else {
        std::cout << "Could not properly open deck file" << std::endl;
    }

}

Card* Deck::draw() {
    if (this == nullptr) {
        return nullptr;
    }
    Card* top = this->back();
    this->pop_back();
    return top;
}

