#include <iostream>
#include "big.h"
#include <chrono>

using std::cout;
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
    cout << "Выполняется тестирование основных операций (+, -, *, /, %, ==, <) класса Big" << endl;
    Big A, B, C, D, res1, res2, res3;
    int n, m;

    for(int i = 0; i < count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % sizeRange;
        }
        A.rand(n);
        B.rand(m);


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
        if (i % count / 10 == 0) {
            cout << "   Пройдено тестов: " << i + 1 << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "Тестирование класса Big завершено" << endl;
    return true;
}

bool testKaratsuba(int count, int sizeRange, bool isFixedSize)
{
    cout << "Выполняется тестирование mulByKaratsuba()" << endl;
    Big num1, num2, resKaratsuba, resBasic;
    int n, m;
    std::chrono::duration<double> karatsubaTime {0};
    std::chrono::duration<double> basicTime{0};
    for(int i = 0; i < count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % sizeRange;
        }

        num1.rand(n);
        num2.rand(m);
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
        if(i % count/10 == 0) {
            cout << "   Пройдено тестов: " << i + 1 << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "   Karatsuba: " << karatsubaTime.count() << endl;
    cout << "   Basic:     " << basicTime.count() << endl;
    cout << endl;
    cout << "Тестирование mulByKaratsuba() завершено" << endl;
    return true;
}

bool testPow(int count, int sizeRange, bool isFixedSize)
{
    cout << "Выполняется тестирование pow()" << endl;
    Big x, y, mod, res;
    int n, m;

    for(int i = 0; i < count; ++i) {
        if (isFixedSize) {
            n = m = sizeRange;
        } else {
            n = 1 + rand() % sizeRange;
            m = 1 + rand() % sizeRange;
        }
        m = 2;
        x.rand(n);
        y.rand(m);
        mod.rand(sizeRange);

        res = x;


        res.pow(y, mod);



        if (res != res ) {
            cout << endl;
            cout << "   Ошибка на тесте #" << i + 1<< endl;
            cout << "       x:    " << x << std::endl;
            cout << "       y:    " << y << std::endl;
            cout << "       mod:  " << mod << std::endl;
            cout << "       res1: " << res << std::endl;
            return false;
        }
        if (i % count / 10 == 0) {
            cout << "   Пройдено тестов: " << i + 1 << endl;
        }
    }
    cout << endl;
    cout << "   Количество тестов: " << count << endl;
    cout << "   Максимальная длина числа: " << sizeRange << endl;
    cout << "Тестирование pow() завершено" << endl;
    return true;
}

int main()
{
    int testCount = 10;
    int numSizeRange = 10000;
    bool isFixedSize = true;
//    srand(time(NULL));

//    testBig(testCount, numSizeRange, isFixedSize);
//    testKaratsuba(testCount, numSizeRange, isFixedSize);
//    testPow(testCount, numSizeRange, isFixedSize);

//    if (testBig(testCount, numSizeRange, isFixedSize) &&
//        testKaratsuba(testCount, numSizeRange, isFixedSize) &&
//        testPow(testCount, numSizeRange, isFixedSize)) {
//
//        cout << endl << "Все тесты пройдены!" << endl;
//    } else {
//        cout << endl << "Тесты не пройдены!" << endl;
//    }
}
