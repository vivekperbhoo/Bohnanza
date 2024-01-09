#include "DiscardPile.h"

std::ostream& operator<< (std::ostream& o, const DiscardPile& d)
{
    o << (*(d.top()));
    return o;
}

DiscardPile& DiscardPile::operator+=(Card* card) {
    discardPile.push_back(card);
    return *this;
}

Card* DiscardPile::pickUp() {
    if (discardPile.empty()) {
        return nullptr;
    }
    Card* top = discardPile.back();
    discardPile.pop_back();
    return top;
}

Card* DiscardPile::top() const{
    if (discardPile.empty()) {
        return nullptr;
    }
    Card* top = discardPile.back();
    return top;
}


void DiscardPile::print(std::ostream& out) {
    for (int i = 0; i < discardPile.size(); i++)
    {
        Card* current = discardPile.at(i);
        out << (*current);
    }
}

DiscardPile::DiscardPile(std::istream& i, const CardFactory* cf)
{
    std::ifstream* discardFile = dynamic_cast<std::ifstream*>(&i);

    if (!discardFile->is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    std::string line;
    if (std::getline(*discardFile, line)) {

        for (char c : line) {
            discardPile.push_back(cf->createCard(std::string(1, c)));
        }
    }
    else {
        std::cout << "Empty file" << std::endl;
    }
    discardFile->close();
}

int DiscardPile::size()
{
    return discardPile.size();
}

void DiscardPile::display()
{
    for (int i = 0; i < discardPile.size(); i++) {
        std::cout << *(discardPile.at(i));
    }
}
