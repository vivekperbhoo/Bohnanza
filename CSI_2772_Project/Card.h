#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>

class Card {
public:
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator << (std::ostream& o, const Card& c);
};

class Black : public Card {
public:
    Black() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Blue : public Card {
public:
    Blue() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Chili : public Card {
public:
    Chili() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Garden : public Card {
public:
    Garden() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Green : public Card {
public:
    Green() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Red : public Card {
public:
    Red() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Soy : public Card {
public:
    Soy() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Stink : public Card {
public:
    Stink() {}
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

#endif  
