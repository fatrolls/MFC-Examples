#pragma  once
class Randint
{
    unsigned long randx;
public:
    Randint(long s=0){    randx=s;}
    void seed(long s){    randx=s;}
    long abs(long x) {    return x&0x7fffffff;}
    static double maxint(){ return 2147483648.0;}
    long draw(){  return randx=randx*1103515245+12345;}//?!
    double fdraw(){ return abs(draw())/maxint();}
    long operator()(){    return abs(draw());}

};


class Urand:public Randint
{
    long n;
public:
    Urand(long nn){        n=nn;}
    long operator()()
    {   long r=n*fdraw();   return (r==n)?n-1:r;    }

};
class Erand:public Randint
{
    long mean;
public:
    Erand(long m){        mean=m;}
    long operator()(){    return -mean*log((maxint()-draw())/maxint()+0.5);}
};
