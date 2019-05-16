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

class invalid_column_name : public EXP
{
public:
    invalid_column_name() : EXP("invalid_column_name") {};
};

class invalid_index : public EXP
{
public:
    invalid_index() : EXP("invalid_index") {};
};

class invalid_value : public EXP
{
public:
    invalid_value() : EXP("invalid_value") {};
};

class invalid_condition : public EXP
{
public:
    invalid_condition() : EXP("invalid_condition") {};
};



#endif