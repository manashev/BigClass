#pragma once
#include <iostream>
#include <cstring>

typedef unsigned int base;
typedef unsigned long long d_base;

typedef int BigError;
namespace BigErrors {
static const BigError OK = 0;
static const BigError INCORRECT_SYMBOL = 1;
static const BigError INCOMPATIBLE_OPERANDS = 2;
static const BigError DIV_ZERO = 3;
}

//class Big {
//public:
//    Big();
//    Big(size_t capacity);
//    Big(const Big &rhs);
//    ~Big();
//
//    Big &operator =(const Big &rhs);
//    Big &operator =(int rhs);
//
//
//    int getCapacity() const;
//    int getLength() const;
//    int rand(int bound);
//    void compress();
//    void shiftLeft(int amount);
//
//
//    friend int compare(const Big &lhs, const Big &rhs);
//    friend int compareWithZero(const Big &rhs);
//    friend bool operator>(Big &lhs, Big &rhs);
//    friend bool operator<(Big &lhs, Big &rhs);
//    friend bool operator>=(Big &lhs, Big &rhs);
//    friend bool operator<=(Big &lhs, Big &rhs);
//    friend bool operator==(Big &lhs, Big &rhs);
//
//
//    friend Big operator+(Big &lhs, Big &rhs);
//    friend Big operator-(Big &lhs, Big &rhs);
//    friend Big operator*(Big &lhs, Big &rhs);
//    friend Big operator/(Big &lhs, Big &rhs);
//    friend Big operator%(Big &lhs, Big &rhs);
//
//
//    Big mulBase(base rhs);
//    friend Big mulByKaratsuba(Big &lhs, Big &rhs);
//
//    Big divBase(base rhs, base &remainder);
//    friend Big div(Big &e, Big &c, Big &remainder);
//
//    void pow(Big &y, Big &mod);
//
//
//    friend std::istream &operator >> (std::istream &in, Big &rhs);
//    friend std::ostream &operator << (std::ostream &out, Big &rhs);
//
//private:
//    Big(base* newHead, base* newTail);
//    void resize(int newCapacity);
//
//    base *head;
//    base *tail;
//    base *alloc;
//};

class Big {
public:
    enum struct Comp {
        LeftGreater,
        Equal,
        RightGreater
    };
    enum struct BigError {
        OK,
        INCORRECT_SYMBOL,
        INCOMPATIBLE_OPERANDS,
        DIV_ZERO
    };
    Big();
    Big(size_t capacity);
    Big(const Big &rhs);
    ~Big();

    Big& operator =(const Big &rhs);
    Big& operator =(int rhs);


    size_t getCapacity() const;
    size_t getLength() const;
    void rand(int bound);
    void compress();
    void shiftLeft(int amount);


    friend int compare(const Big &lhs, const Big &rhs);
    friend int compareWithZero(const Big &rhs);
    friend bool operator>(Big &lhs, Big &rhs);
    friend bool operator<(Big &lhs, Big &rhs);
    friend bool operator>=(Big &lhs, Big &rhs);
    friend bool operator<=(Big &lhs, Big &rhs);
    friend bool operator==(Big &lhs, Big &rhs);


    friend Big operator+(Big &lhs, Big &rhs);
    friend Big operator-(Big &lhs, Big &rhs);
    friend Big operator*(Big &lhs, Big &rhs);
    friend Big operator/(Big &lhs, Big &rhs);
    friend Big operator%(Big &lhs, Big &rhs);


    Big mulBase(base rhs);
    friend Big mulByKaratsuba(Big &lhs, Big &rhs);

    Big divBase(base rhs, base &remainder);
    friend Big div(Big &e, Big &c, Big &remainder);

    void pow(Big &y, Big &mod);


    friend std::istream &operator >> (std::istream &in, Big &rhs);
    friend std::ostream &operator << (std::ostream &out, Big &rhs);

private:
    Big(base* newHead, base* newTail);
    void resize(int newCapacity);

    base *head;
    base *tail;
    base *alloc;
};

