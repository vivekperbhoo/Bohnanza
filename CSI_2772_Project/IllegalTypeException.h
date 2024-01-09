#ifndef ILLEGALTYPEEXCEPTION_H
#define ILLEGALTYPEEXCEPTION_H

#include <string>

class IllegalTypeException : public std::exception {
    std::string message;
public:
    IllegalTypeException(const std::string& msg): message(msg) {};
    const char* what() const noexcept override { return message.c_str(); }
};

#endif