#include "Player.h"

std::ostream& operator << (std::ostream& o, const Player& p) {
    o << (p.name);
    o.put(' ');
    o << p.coins;
    o << " coins";
    for (int i = 0; i < p.getNumChains(); i++) {
        Chain_Base* currentChain = p.chain.at(i);
        o << *currentChain;
    }
    int numEmptyFields = p.getMaxNumChains() - p.getNumChains();
    for (int i = 0; i < numEmptyFields; i++) {
        o << "Empty Field" << "\n";
    }
    return o;
}



bool canAddCardFromTradeArea(const TradeArea& t, const Player& p)
{
    if (t.getTradeArea().size() == 0) {
        return false;
    }

    //mn azout sa la
    if (((p.getMaxNumChains()) - (p.getNumChains())) > 0) {
        return true;
    }

    std::unordered_map<std::string, int> map = t.getMap();
    for (const auto& pair : map) {
        if (pair.second != 0) {
            for (int i = 0; i < p.getNumChains(); i++) {
                Chain_Base* target = (p.chain).at(i);
                if (pair.first == (target->getChainType())) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool canAddCardFromTradeArea(const Player& p, std::string cardName)
{

    //mn azout sa la
    if (((p.getMaxNumChains()) - (p.getNumChains())) > 0) {
        return true;
    }


    for (int i = 0; i < p.getNumChains(); i++) {
        Chain_Base* target = (p.chain).at(i);
        if (cardName == (target->getChainType())) {
             return true;
        }
    }
    std::cout << "You have no fields with beans matching with type " << cardName << std::endl;
    return false;
}

void Player::addCardToChain(Card* card, int t)
{
    std::string cardName = card->getName();

    //This loop checks if it is possible to add a card to a field which already has the same card
    for (Chain_Base* c : chain) {
        if (c->getChainType() == cardName) {
            if (cardName == "Blue") {
                Chain<Blue*>* chainToAdd = dynamic_cast<Chain<Blue*>* >(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;
            }
            if (cardName == "Black") {
                Chain<Black*>* chainToAdd = dynamic_cast<Chain<Black*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Red") {
                Chain<Red*>* chainToAdd = dynamic_cast<Chain<Red*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Stink") {
                Chain<Stink*>* chainToAdd = dynamic_cast<Chain<Stink*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Soy") {
                Chain<Soy*>* chainToAdd = dynamic_cast<Chain<Soy*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Garden") {
                Chain<Garden*>* chainToAdd = dynamic_cast<Chain<Garden*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Green") {
                Chain<Green*>* chainToAdd = dynamic_cast<Chain<Green*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
            if (cardName == "Chili") {
                Chain<Chili*>* chainToAdd = dynamic_cast<Chain<Chili*>*>(c);
                for (int i = 0; i < t; i++) {
                    (*chainToAdd) += card;
                }
                return;

            }
        }
    }
    //If we reach here then it means there was no matching field with card type. We try to add it to an empty field if there is one.
    //This if checks if there are empty fields
    if ((getMaxNumChains() - getNumChains()) > 0) {
        if (cardName == "Blue") {
            Chain<Blue*>* chainToAdd = new Chain<Blue*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Black") {
            Chain<Black*>* chainToAdd = new Chain<Black*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Red") {
            Chain<Red*>* chainToAdd = new Chain<Red*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Stink") {
            Chain<Stink*>* chainToAdd = new Chain<Stink*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Soy") {
            Chain<Soy*>* chainToAdd = new Chain<Soy*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Garden") {
            Chain<Garden*>* chainToAdd = new Chain<Garden*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Green") {
            Chain<Green*>* chainToAdd = new Chain<Green*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
        if (cardName == "Chili") {
            Chain<Chili*>* chainToAdd = new Chain<Chili*>();
            for (int i = 0; i < t; i++) {
                (*chainToAdd) += card;
            }
            chain.push_back(chainToAdd);
            return;

        }
    }
}

std::vector<Chain_Base*>& Player::getChain()
{
    return chain;
}

void Player::sellChain(std::string fieldType)
{
    int coinsGained = 0;
    for (int i = 0; i < chain.size(); i++) {
        Chain_Base* target = chain.at(i);
        if (target->getChainType() == fieldType) {
            coinsGained = target->sell();
            chain.erase(chain.begin() + i);
        }
    }
    coins += coinsGained;
}

void Player::setHand(Hand& h)
{
    this->hand = h;
}


Player::Player(std::istream& i, const CardFactory* cf) {
    std::string n;
    std::getline(i, n, ' ');
    name = n;
    std::string c;
    std::getline(i, c);
    coins =std::stoi(c);
}


Player::Player(std::string& n) {
    name = n;
    coins = 0;
    thirdChain = false;
    active = false;
}


std::string Player::getName() {
    return name;
}

Player& Player::operator+=(int i) {
    coins += i;
    return *this;
}
int Player::getNumCoins() {
    return coins;
}

int Player::getMaxNumChains() const {
    if (thirdChain==true) {
        return 3;
    }
    return 2;
}

int Player::getNumChains() const{
    return chain.size();
}

Chain_Base& Player::operator[](int i) {
    return *(chain.at(i));
}

void Player::buyThirdChain() {
    if (chain.size() >= 3) {
        std::cout << "You already have three chains" << std::endl;
        return;
    }
    else if (coins >= 3) {
        coins = coins - 3;
        thirdChain = true;
        //mon tir sa veks check n kout thx
       // chain[2] = nullptr;
        return;
    }
    else {
        throw NotEnoughCoinsException("Not enough coins to buy third chain");
    }
}

void Player::printHand(std::ostream& o, bool b) {
    if (!b) {
        o << *(hand.top());
    }
    else {
        o << hand;
    }
}


//added by us
void Player::addCardToHand(Card* c) {
    hand += c;
}

bool Player::isActive()
{
    return active;
}

void Player::setActive(bool b)
{
    active = b;
}

Hand& Player::getHand()
{
    return hand;
}

