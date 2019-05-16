#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED
#include <exception>



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

class invalid_avl_tree : public std::exception
{
public:
	const char *what() const throw() { return "Serulnek az AVL fa tulajdonsagok!"; }
};

class invalid_iterator : public std::exception
{
public:
    const char *what() const throw() { return "NULL elemre mutat az iterator!"; }
};

class copy_not_implemented : public std::exception
{
public:
    const char *what() const throw() { return "Masolas nincs implementalva!"; }
};

#endif // EXCEPTIONS_HPP_INCLUDED

