#ifndef NOTENOUGHCOINSEXCEPTION_H
#define NOTENOUGHCOINSEXCEPTION_H

#include <string>

class NotEnoughCoinsException : public std::exception {
    std::string message;
public:
    NotEnoughCoinsException(const std::string& msg) : message(msg) {};
    const char* what() const noexcept override { return message.c_str(); }
};

#endif