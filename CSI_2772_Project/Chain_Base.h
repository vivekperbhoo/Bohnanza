#ifndef CHAINBASE_H
#define CHAINBASE_H

#include <iostream>

class Chain_Base {
public:
    friend std::ostream& operator << (std::ostream& o, const Chain_Base& cb);
    virtual int sell() const = 0;
    virtual void print(std::ostream& o) const = 0;

    //added
    virtual int size() const = 0;
    virtual std::string getChainType() const = 0;

};

inline std::ostream& operator<< (std::ostream& o, const Chain_Base& b)
{
    b.print(o);
    return o;
}

#endif