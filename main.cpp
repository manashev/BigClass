#include <iostream>
#include "big.h"
#include <chrono>
#include <utility>

using std::cout;
using std::cin;
using std::endl;

/*
 * возведение в степень
 * карацуба
 * приведение по модулю баррет
 * тест миллера рабина
 * генератор простого (вход - длина в битах)
 */


bool testBig(int count, int sizeRange, bool isFixedSize)
{
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Начато тестирование основных операций (+, -, *, /, %, ==, <) класса Big" << endl;
    Big A, B, C, D, res1, res2, res3;
    int n, m;

    for(int i = 1; i <= count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % sizeRange;
        }
        A.randBlocks(n);
        B.randBlocks(m);


        C = A / B;
        D = A % B;

        res1 = B * C;
        res1 = res1 + D;
        res2 = A - D;
        res3 = B * C;

        /*
         * A == B * C + D &&
         * A - D == B * C &&
         * D < B
         */
        if (!((res1 == A) && (res2 == res3) && (D < B))) {
            cout << endl;
            cout << "   Ошибка на тесте #" << i + 1<< endl;
            cout << "       A:                " << A << std::endl;
            cout << "       B:                " << B << std::endl;
            cout << "       C = A / B:        " << C << std::endl;
            cout << "       D = A % B:        " << D << std::endl;
            cout << "       res1 = B * C + D: " << res1 << std::endl;
            cout << "       res2 = A - D:     " << res2<< std::endl;
            cout << "       res3 = B * C:     " << res2<< std::endl;
            return false;
        }
        if (i % (count / 10) == 0) {
            cout << "   Пройдено тестов: " << i << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "Завершено тестирование класса Big" << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    return true;
}

bool testKaratsuba(int count, int sizeRange, bool isFixedSize)
{
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Начато тестирование mulByKaratsuba()" << endl;
    Big num1, num2, resKaratsuba, resBasic;
    int n, m;
    std::chrono::duration<double> karatsubaTime {0};
    std::chrono::duration<double> basicTime{0};

    for(int i = 1; i <= count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % sizeRange;
        }

        num1.randBlocks(n);
        num2.randBlocks(m);
        auto begin = std::chrono::high_resolution_clock::now();
        resBasic = num1 * num2;
        auto end = std::chrono::high_resolution_clock::now();
        basicTime += end - begin;

        begin = std::chrono::high_resolution_clock::now();
        resKaratsuba = mulByKaratsuba(num1, num2);
        end = std::chrono::high_resolution_clock::now();
        karatsubaTime += end - begin;


        if (resBasic != resKaratsuba) {
            cout << endl;
            cout << "   Ошибка на тесте #" << i + 1 << endl;
            cout << "       num1:      " << num1 << endl;
            cout << "       num2:      " << num2 << endl;
            cout << "       basic:     " << resBasic << endl;
            cout << "       karatsuba: " << resKaratsuba << endl;
            return false;
        }
        if(i % (count / 10) == 0) {
            cout << "   Пройдено тестов: " << i << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "   Karatsuba: " << karatsubaTime.count() << endl;
    cout << "   Basic:     " << basicTime.count() << endl;
    cout << endl;
    cout << "Завершено тестирование mulByKaratsuba()" << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    return true;
}

bool testPow(int count, int sizeRange, bool isFixedSize)
{
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Начато тестирование pow()" << endl;
    Big x, y, mod, res;
    int n, m;

    for(int i = 1; i <= count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % (sizeRange / 10);
        }
        m = 1;
        x.randBlocks(n);
        y.randBlocks(m);
        mod.randBlocks(sizeRange);

        res = x.pow(y, mod);

        if (res != res ) {
            cout << endl;
            cout << "   Ошибка на тесте #" << i + 1<< endl;
            cout << "       x:    " << x << std::endl;
            cout << "       y:    " << y << std::endl;
            cout << "       mod:  " << mod << std::endl;
            cout << "       res1: " << res << std::endl;
            return false;
        }
        if (i % (count / 10) == 0) {
            cout << "   Пройдено тестов: " << i << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "Завершено тестирование pow()" << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    return true;
}

bool testBarrett(int count, int sizeRange, bool isFixedSize)
{
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Начато тестирование moduloByBarrett()" << endl;
    Big x, mod, barrettNum, resBarrett, resBasic;
    int xLength, modLength;
    std::chrono::duration<double> barrettTime{0};
    std::chrono::duration<double> basicTime{0};

    for(int i = 1; i <= count; ++i) {
        if (isFixedSize) {
            modLength = sizeRange;
        } else {
            modLength = 1 + rand() % sizeRange;
        }
        mod.randBlocks(modLength);
        xLength = 1 + rand() % (2 * mod.getLength());
        x.randBlocks(xLength);

        barrettNum = getBarrettNum(mod);

        auto begin = std::chrono::high_resolution_clock::now();
        resBarrett = x.moduloByBarrett(mod, barrettNum);
        auto end = std::chrono::high_resolution_clock::now();
        barrettTime += end - begin;

        begin = std::chrono::high_resolution_clock::now();
        resBasic = x % mod;
        end = std::chrono::high_resolution_clock::now();
        basicTime += end - begin;

        if (resBarrett != resBasic) {
            cout << endl;
            cout << "   Ошибка на тесте #" << i + 1<< endl;
            cout << "       x:          " << x << std::endl;
            cout << "       mod         " << mod << std::endl;
            cout << "       barrettNum: " << barrettNum << std::endl;
            cout << "       barrett:    " << resBarrett << std::endl;
            cout << "       basic:      " << resBasic << std::endl;
            return false;
        }
        if (i % (count / 10) == 0) {
            cout << "   Пройдено тестов: " << i << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "   Barrett: " << barrettTime.count() << endl;
    cout << "   Basic:   " << basicTime.count() << endl;
    cout << endl;
    cout << "Завершено тестирование moduloByBarrett()" << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;
    return true;
}


int main()
{
    int testCount = 1000;
    int numSizeRange = 10000;
    bool isFixedSize = true;
    srand(time(NULL));

// Генерация простых с разным количеством бит
    for(int i = 990; i < 1020; ++i) {
        Big prime{generatePrime(i, 500)};
        cout << "bit: " << i << endl;
        cout << prime << endl << endl;
    }

// Генерация простого числа
//    Big prime{generatePrime(1001, 500)};
//        cout << prime << endl;

//  Проверка на известных значениях
//    Big b{"db7"};
//    Big c{"1b02761f9c6b100f64e1b27a78330195da1f6902cdeaf4c71c71c7"};
//    Big d{"1b02761f9c6b100f64e1b27a78330195da1f6902cdeaf4c71c71c61b02761f9c6b100f64e1b27a78330195da1f6902cdeaf4c71c71c6"};
//
//    cout << "b: " << b << endl;
//    cout << "c: " << c << endl;
//    cout << "d: " << d << endl;
//
//    cout << "b.isPrime: " << b.isPrime(500) << endl;
//    cout << "c.isPrime: " << c.isPrime(500) << endl;
//    cout << "d.isPrime: " << d.isPrime(500) << endl;

//    testBig(testCount, numSizeRange, isFixedSize);
//    testKaratsuba(testCount, numSizeRange, isFixedSize);
//    testPow(testCount, numSizeRange, isFixedSize);
//    testBarrett(testCount, numSizeRange, isFixedSize);
}
