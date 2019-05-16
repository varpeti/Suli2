/**
*
* @file heap_exceptions.hpp
* @author tekda
* Kupac manipuláló eljárások által használt kivételek leírása
*
*/

#ifndef HEAP_EXCEPTIONS_HPP
#define HEAP_EXCEPTIONS_HPP

class HeapException {};

class InvalidIterator : public HeapException {};
class InvalidIndex : public HeapException {};
class EmptyHeap : public HeapException {};
class NotFound : public HeapException {};
class NullPointer : public HeapException {};


#endif // HEAP_EXCEPTIONS_HPP
