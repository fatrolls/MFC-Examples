#include "node.hpp"
#include "astring.hpp"
#include "consdes.hpp"
#include "functions.hpp"
#include "virtualbase.hpp"
#include "atl.hpp"
#include "mystr.hpp"
#include "abc.hpp"
#include "add.hpp"
#include "bin_tree.hpp"
#include "countobj.hpp"
#include "doubledispatch.hpp"
#include "final1.hpp"
#include "final2.hpp"
#include "myalloc.hpp"
#include "null.hpp"
#include "traits.hpp"
#include "ocp.hpp"
#include "refcount.hpp"
#include "refcount2.hpp"
#include "refcount3.hpp"
#include "cycle.h"
#include "ttime.hpp"
#include "ctimer.hpp"
#include "calendar.h"
#include "randint.hpp"
#include "d3des.h"
extern "C"{
	#include"set.h"
}
#include "bigint.h"
#include "bigfp.h"
#include "MemFuncPtr.hpp"
#include "MemFuncPtr2.hpp"
#include  "templ_nest.hpp"
//#include "FiniteFieldElement.hpp"
#include  "cowptr.hpp"
#include  "crtp.hpp"
#include  "number.hpp"
#include  "nocopyable.hpp"
#include <iostream>
using namespace std;


//not include--
//quine.c 
//quine2.c 
//winmain2.cpp 
//Carfieldlee.cpp
//pth.cpp 
//line.cpp
//--not include
int main()
{
   namedloop( );
   memdetect();
   //eightqueen1();
   //unkwn();
   //testatol();
   //itoafun();
   //testunion();
   //testshellsort();
   //testgcd();
      //revwords();//??
      //teststrreverse( );//??
      //testreverse( );//??
    //foo();
    //testgetmm();
    //testgetmm2();

    //testgetmm3();

    //comparechar();
    //compareint();
    //testB1(5);
    //testB2(15);
    //testC1();

    //testvirtualbase();
    //testatl();
	 //testecc();
    //testset();

      //templnest();
    char aa;
    std::cin>>aa;


    _onexit( fn1 );
    _onexit( fn2 );
    _onexit( fn3 );
    _onexit( fn4 );
    printf( "This is executed first.\n" );
}


//当类中含有 const 、reference 成员变量、基类的构造函数 都需要初始化列表。