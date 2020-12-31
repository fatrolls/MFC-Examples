// MicroSecond.cpp: implementation of the CMicroSecond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MicroDelay.h"
#include "MicroSecond.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMicroSecond::CMicroSecond()
{
   Initialize();
}

CMicroSecond::~CMicroSecond()
{

}

int  CMicroSecond::TweekLoopPerMicrosecond(double dTweek)
{
    double dVal = (double)m_nLoopCountPerMicroSecond ;
    double dWork = 0.0;

    dWork = dVal/100.0;
    if ( dTweek < 100.0 )
    {
       dVal -= (dWork * dTweek);
    }
    else
    {
       dVal += (dWork * dTweek);
    }
    m_nLoopCountPerMicroSecond = (int)dVal;
   
    return m_nLoopCountPerMicroSecond ;
}

void CMicroSecond::Initialize()
{
    DWORD dwStart = 0;
    DWORD dwStop = 0;
    
    int nLoopSeed = 100000;
    
    // make sure we get a seed count that will a millisecond value of about 100
    do{  
         m_dwLoopCounter1 = 0;

            dwStart = GetTickCount();
            for ( int i=0; i< nLoopSeed; i++)
            {
                m_dwLoopCounter1++;
                 _asm{nop}
            }
            dwStop = GetTickCount();
            nLoopSeed += 100000;
    }while ( dwStop - dwStart < 50 );


    m_dwLoopCounter1 = 0;
    dwStart = GetTickCount();
     for ( int i=0; i< nLoopSeed; i++)
     {
         m_dwLoopCounter1++;
          _asm{nop}
     }
    dwStop = GetTickCount();
    // loop counts per millisecond
    m_dwLoopCounter1 = m_dwLoopCounter1 / (dwStop - dwStart);

    m_nLoopCountPerMicroSecond = (int)m_dwLoopCounter1 / 1000;
 
}
