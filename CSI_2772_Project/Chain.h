#ifndef CHAIN
#define CHAIN

#include "Card.h"
#include "CardFactory.h"
#include "Chain_Base.h"
#include "IllegalTypeException.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>


template <typename T>
class Chain : public Chain_Base {
    std::vector<T> chainCards;
public:
    Chain() {};
    Chain<T>& operator+=(Card*);
    int sell() const override;
    Chain<T>(std::istream&, const CardFactory*);
    void print(std::ostream& o) const override;
    int size() const override;
    std::string getChainType() const;
};

template <typename T>
void Chain<T>::print(std::ostream& o) const {
    Card* card = (Card*) chainCards.front();
    std::string cardName = card->getName();
    o << "\n" << cardName;
    o.put(' ');
    for (int i = 0; i < (chainCards).size(); i++) {
        o << *(card);
    }
}

template<typename T>
int Chain<T>::size() const 
{
    return chainCards.size();
}

template<typename T>
inline std::string Chain<T>::getChainType() const
{
    Card* card = (Card*) chainCards.front();
    return (card->getName());
}

template <typename T>
int Chain<T>::sell() const {
    if (chainCards.size() >= ((chainCards.front())->getCardsPerCoin(1)) && chainCards.size() < ((chainCards.front())->getCardsPerCoin(2))) {
        return 1;
    }
    if (chainCards.size() >= ((chainCards.front())->getCardsPerCoin(2)) && chainCards.size() < ((chainCards.front())->getCardsPerCoin(3))) {
        return 2;
    }
    if (chainCards.size() >= ((chainCards.front())->getCardsPerCoin(3)) && chainCards.size() < ((chainCards.front())->getCardsPerCoin(4))) {
        return 3;
    }
    if (chainCards.size() >= ((chainCards.front())->getCardsPerCoin(4))) {
        return 4;
    }
    return 0;
}

template <typename T>
Chain<T>& Chain<T>:: operator+=(Card* card) {
    T typedCard = dynamic_cast<T>(card);
    if (chainCards.size()==0) {
        chainCards.push_back(typedCard);
        return *this;
    }
    Card* cardPtr = (Card*) chainCards.front();
    if (cardPtr->getName() != card->getName()) {
        throw IllegalTypeException("Card is not of the same type as chain!");
    }
    else {
        chainCards.push_back(typedCard);
    }
    return *this;
}

template <typename T>
Chain<T>::Chain(std::istream& i, const CardFactory* cf) {
    std::ifstream* chainFile = dynamic_cast<std::ifstream*>(&i);

    if (!chainFile.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    std::string cardName;
    std::string line;
    if (std::getline(chainFile, line)) {
        std::istringstream iss(line);
        std::string word;
        std::list<char> charList;

        iss >> cardName;

        while (iss >> word) {
            for (char c : word) {
                charList.push_back(c);
            }
        }
    }
    else {
        std::cout << "Empty file" << std::endl;
    }

    (*chainFile).close();

}

#endif
