#ifndef EXP_H_
#define EXP_H_

#include <exception>

class EXP : public std::exception
{
private:
    const char *message;
public:
    EXP(const char *msg) : message(msg) {}

    const char *what() const throw() { return message; }
};


#endif