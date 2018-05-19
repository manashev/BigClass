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
static const BigError INCORRECT_AMOUNT = 4;

}

/*
head - указатель на начало числа
tail - указатель на конец числа
alloc - количество выделенной памяти
length - мощность - количество блоков
capacity - емкость, количество выделенной памяти
*/

class Big {
public:
    Big();
    Big(int capacity);
    Big(const Big &rhs);
    ~Big();

    Big& operator =(const Big &rhs);
    Big& operator =(int rhs);


    int getCapacity() const;
    int getLength() const;
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
    friend bool operator!=(Big &lhs, Big &rhs);


    Big operator+(Big &rhs);
    Big operator-(Big &rhs);
    Big operator*(Big &rhs);
    Big operator/(Big &rhs);
    Big operator%(Big &rhs);


    Big mulBase(base rhs);
    friend Big mulByKaratsuba(Big &lhs, Big &rhs);

    Big divBase(base rhs, base &remainder);
    friend Big div(Big &e, Big &c, Big &remainder);
    Big moduloByBarrett(Big &mod, Big &barretNum);
    friend Big getBarrettNum(Big &mod);

    void pow(Big &degree, Big &mod);


    friend std::istream &operator >> (std::istream &in, Big &rhs);
    friend std::ostream &operator << (std::ostream &out, Big &rhs);

private:
    void resize(int newCapacity);

    base *head;
    base *tail;
    base *alloc;
};

Big mulByKaratsuba(Big &lhs, Big &rhs);
Big getBarrettNum(Big &mod);
