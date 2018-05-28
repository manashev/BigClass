#pragma once
#include <iostream>
#include <string>

typedef unsigned int base;
typedef unsigned long long d_base;
static const int bitsInBlock = sizeof(base) * 8;

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
    explicit Big(std::string hexNum);
    ~Big();

    Big& operator =(const Big &rhs);
    Big& operator =(int rhs);

    int getCapacity() const;
    int getLength() const;
    void compress();
    void shiftLeft(int amount);
    Big shiftRight(int amount);

    bool isPrime(int reliability);
    void randBits(int bits);
    void randBlocks(int blocks);
    friend Big generatePrime(int bit, int reliability);

    friend int compare(const Big &lhs, const Big &rhs);
    bool isZero();
    bool isEven();

    bool operator>(Big &rhs);
    bool operator<(Big &rhs);
    bool operator>=(Big &rhs);
    bool operator<=(Big &rhs);
    bool operator==(Big &rhs);
    bool operator!=(Big &rhs);

    bool operator>(base rhs);
    bool operator<(base rhs);
    bool operator>=(base rhs);
    bool operator<=(base rhs);
    bool operator==(base rhs);
    bool operator!=(base rhs);

    Big operator+(Big &rhs);
    Big operator-(Big &rhs);
    Big operator*(Big &rhs);
    Big operator/(Big &rhs);
    Big operator%(Big &rhs);

    Big pow(Big &degree, Big &mod);
    Big pow(Big &degree, Big &mod, Big &barrettNum);
    Big mulBase(base rhs);
    friend Big mulByKaratsuba(Big &lhs, Big &rhs);

    Big divBase(base rhs, base &remainder);
    friend Big div(Big &e, Big &c, Big &remainder);
    Big moduloByBarrett(Big &mod, Big &barretNum);
    friend Big getBarrettNum(Big &mod);

    friend std::istream& operator >> (std::istream &in, Big &rhs);
    friend std::ostream& operator << (std::ostream &out, Big &rhs);

private:
    void resize(int newCapacity);

    base *head;
    base *tail;
    base *alloc;
};

Big mulByKaratsuba(Big &lhs, Big &rhs);
Big getBarrettNum(Big &mod);
Big generatePrime(int bit, int reliability);
