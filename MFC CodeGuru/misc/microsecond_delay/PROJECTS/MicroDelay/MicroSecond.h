// MicroSecond.h: interface for the CMicroSecond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MICROSECOND_H__D7406E7C_9B3A_11D1_94DB_00400540824C__INCLUDED_)
#define AFX_MICROSECOND_H__D7406E7C_9B3A_11D1_94DB_00400540824C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMicroSecond  
{
public:
    int n;
    DWORD GetLoopCounter1(){return m_dwLoopCounter1;}
    int TweekLoopPerMicrosecond(double dTweek);

    int GetLoopPerMicrosecond(){return m_nLoopCountPerMicroSecond; }
    
    inline void MicroDelay( int uSec ) 
    { 
        n=0;
        for(int i = 0; i < uSec*m_nLoopCountPerMicroSecond; i++)
        {
            n++;
            _asm{nop} 
        } 
    }

    void Initialize();
    
    CMicroSecond();
	virtual ~CMicroSecond();

private:
	DWORD m_dwLoopCounter1;
	int m_nLoopCountPerMicroSecond;
};

#endif // !defined(AFX_MICROSECOND_H__D7406E7C_9B3A_11D1_94DB_00400540824C__INCLUDED_)
