#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <exception>

class copy_not_implemented : public std::exception
{
public:
    const char *what() const throw() { return "Masolas nincs implementalva!"; }
};

class internal_error : public std::exception
{
    const char *message;

public:
    internal_error(const char *msg = "Hiba van az implementacioban!") : message(msg) {}

    const char *what() const throw() { return message; }
};

class invalid_binary_search_tree : public std::exception
{
public:
    const char *what() const throw() { return "Serulnek a binaris keresofa kriteriumok!"; }
};

#endif // EXCEPTIONS_HPP_INCLUDED
