#include <iostream>
#include "big_number.h"
//#include <ctime>

using std::cout;
using std::endl;

/*
 * возведение в степень
 * приведение по модулю баррет
 * карацуба
 * тест миллера рабина
 * генератор простого вход длина в битах
 */

/*
bool mainTest(int T, int M)
{
    Big A, B, C, D;
    do{
        int n {1 + rand() % M};
        int m {1 + rand() % M};
//        int n,m;
//        n = m = M;

        A.rand(n);
        B.rand(m);


        C = A / B;
        D = A % B;

//        std::cout << "A = " << A << std::endl
//                  << "B = " << B << std::endl
//                  << "C = " << C << std::endl
//                  << "D = " << D << std::endl << std::endl;
        if(T % 5 == 0) {
            std::cout << T << std::endl;
        }
    } while (A == B * C + D &&
             A - D == B * C &&
             D < B &&
             --T);
    if(T)
    {
        std::cout << "-----Error-----" << std::endl
                  << "A = " << A << std::endl
                  << "B = " << B << std::endl
                  << "C = " << C << std::endl
                  << "D = " << D << std::endl
                  << "T = " << T << std::endl;
        return false;
    }
    std::cout << "Good" << std::endl;
    return true;
}
*/


int main()
{
    srand(time(NULL));

    //test for big number
/*
//    Big a,b,c,d,result_1, result_2, result_3;
//    int T = 1000, M =1000;
//    do{
//        int n = 1 + rand() % M;
//        int m = 1 + rand() % M;
//        a.Rand(n);
//        b.rand(m);
//        c = a/b;
//        d = a%b;
//        result_1 = b*c;
//        result_2 = result_1 + d;
//        result_3 = a - d;
//        std::cout << T << std::endl;
//    }
//    while(a==result_2 && result_3==result_1 && d<b && --T);
//    if (T) std::cout<< a << b << c << d <<std::endl;
    */

    //test for pow
/*
    Big x,y,m;
    x.rand(10);
    std::cin >> y >> m;
    std::cout << "x = " << x << " y = " << y << " m = " << m <<std::endl;
    x.pow(y, m);
    std::cout << "x = " << x;*/

    //test for mulByKaratsuba
    Big a,b, standart, karatsuba;
    a.rand(50), b.rand(50);
//    std::cin >> a >> b;
    cout << "a = " << a << "\nb = " << b << endl << endl;
    standart = a * b;

    karatsuba = mulByKaratsuba(a, b);
    cout << standart << endl << ((karatsuba == standart)? "==" : "!=") << endl << karatsuba << endl;

//    Big a;
//    a = 1;
//    a.shiftLeft(2);
//    std::cout << "a = " << a;

}
