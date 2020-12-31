#ifndef _FUNCTIOINS_
#define _FUNCTIOINS_

#include <vector>
void unkwn();
void testatol();
bool fun( int a[], int n );
void foo(void);
void myswap( int* p1,int* p2 );
char * mystrcpy( char *strDest, const char *strSrc );
int mystrlen( const char *str ) ;


void Order(std::vector<int>& data);
void insortout();


void getMemory(char **p, int num);
void getMemory1( char *p );
char *getMemory2(void);
void testgetmm(void);
void testgetmm2(void);
void testgetmm3(void);

int find_sec_max( int data[] , int count);
void numseq();
void comparechar();
void compareint();
int func(int x);
int fn1();
int fn2();
int fn3();
int fn4();

int itoafun();
void inputgenes();
unsigned int binary_gcd(unsigned int x, unsigned int y);
void testgcd();

void shellsort(register int v[], int n);
void testshellsort();

void testunion();

int testecc( );//ECC.cpp
bool IsSymmetry(const char * p);
void revwords();
int teststrreverse( );
int testreverse( );
int testNSquare(void );

int namedloop(void);
void memdetect(void);
void MoveConstructor();
void foometa();

//void eightqueen1( );//..\src\8queen\eightqueen1.cpp
#endif /* _FUNCTIOINS_ */