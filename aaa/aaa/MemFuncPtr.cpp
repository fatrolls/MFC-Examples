#include"MemFuncPtr.hpp"
#include"MemFuncPtr2.hpp"
#include<iostream>
using namespace std;
class Wombat;
typedef int(Wombat::*PWMF)();
typedef int(Wombat::*PWMFC)() const;
typedef int(Wombat::*PWMF1)(int);
class Wombat
{
public:
    int dig() {
        cout << "Digging////..." << endl;
        return 1;
    }
    int sleep() {
        cout << "Sleeping////..." << endl;
        return 5;
    }
    int eat() const {
        cout << "Eatting////..." << endl;
        return 7;
    }
    int move(int op) {
        cout << "Moving////..." << endl;
        return 9;
    }
};

void testMFP()
{
    SP<Wombat> pw = new Wombat;
    PWMF pmf = &Wombat::dig;
    (pw->*pmf)();               // Digging////...
    PWMF pmf2 = &Wombat::sleep;
    (pw->*pmf2)();               // Sleeping////...
    PWMFC pmfc = &Wombat::eat;
    (pw->*pmfc)();              // Eatting////...
    PWMF1 pmf1 = &Wombat::move;
    (pw->*pmf1)(2);             // Eatting////...

    SP3<Wombat> pw3 = new Wombat;
    (pw3->*pmf)();               // Digging////...
    (pw3->*pmf2)();               // Sleeping////...
    (pw3->*pmfc)();              // Eatting////...
    (pw3->*pmf1)(2);             // Eatting////...
}
