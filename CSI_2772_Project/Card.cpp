#include "Card.h"

std::ostream& operator<< (std::ostream& o,const Card& c)
{
    c.print(o);
    return o;
}

//Black
int Black::getCardsPerCoin(int coins) const{
    switch (coins)
    {
    case 1:
        return 2;
        break;
    case 2:
        return 4;
        break;
    case 3:
        return 5;
        break;
    case 4:
        return 6;
        break;
    default:
        return 0;
        break;
    }
}

std::string Black::getName() const{ return "Black"; }

void Black::print(std::ostream& out) const{
    out << 'b';
}

//Blue
int Blue::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 4;
        break;
    case 2:
        return 6;
        break;
    case 3:
        return 8;
        break;
    case 4:
        return 10;
        break;
    default:
        return 0;
        break;
    }
}

std::string Blue::getName() const { return "Blue"; }

void Blue::print(std::ostream& out) const {
    out << 'B';
}

//Chili
int Chili::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 3;
        break;
    case 2:
        return 6;
        break;
    case 3:
        return 8;
        break;
    case 4:
        return 9;
        break;
    default:
        return 0;
        break;
    }
}

std::string Chili::getName() const { return "Chili"; }

void Chili::print(std::ostream& out) const {
    out << 'C';
}

//Garden
int Garden::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 1000;   //This is so that selling Garden chain with 1 element will return 0 in sell chains
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    case 4:
        return 1000;
        break;
    default:
        return 0;
        break;
    }
}

std::string Garden::getName() const { return "Garden"; }

void Garden::print(std::ostream& out) const {
    out << 'g';
}

//Green
int Green::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 3;
        break;
    case 2:
        return 5;
        break;
    case 3:
        return 6;
        break;
    case 4:
        return 7;
        break;
    default:
        return 0;
        break;
    }
}

std::string Green::getName() const { return "Green"; }

void Green::print(std::ostream& out) const {
    out << 'G';
}

//Red
int Red::getCardsPerCoin(int coins) const{
    switch (coins)
    {
    case 1:
        return 2;
        break;
    case 2:
        return 3;
        break;
    case 3:
        return 4;
        break;
    case 4:
        return 5;
        break;
    default:
        return 0;
        break;
    }
}
std::string Red::getName() const{ return "Red"; }

void Red::print(std::ostream& out) const{
    out << 'R';
}

//Soy
int Soy::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 2;
        break;
    case 2:
        return 4;
        break;
    case 3:
        return 6;
        break;
    case 4:
        return 7;
        break;
    default:
        return 0;
        break;
    }
}
std::string Soy::getName() const { return "Soy"; }

void Soy::print(std::ostream& out) const {
    out << 's';
}

//Stink
int Stink::getCardsPerCoin(int coins) const {
    switch (coins)
    {
    case 1:
        return 3;
        break;
    case 2:
        return 5;
        break;
    case 3:
        return 7;
        break;
    case 4:
        return 8;
        break;
    default:
        return 0;
        break;
    }
}
std::string Stink::getName() const { return "Stink"; }

void Stink::print(std::ostream& out) const {
    out << 'S';
}







