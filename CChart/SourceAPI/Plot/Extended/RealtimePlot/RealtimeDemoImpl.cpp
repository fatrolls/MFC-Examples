/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#include "Stdafx.h"
#include "RealtimeDemoImpl.h"

#include "mmsystem.h"  //head file
#pragma comment(lib,"winmm")  //lib file

CRealtimeDemoImpl::CRealtimeDemoImpl(HWND hWnd) : CRealtimePlotImpl(hWnd)
{
//	m_pPlot = new CRealtimePlotImpl(hWnd);

	m_pTimerFcn = TimerHandler;
}

CRealtimeDemoImpl::~CRealtimeDemoImpl()
{
//	delete m_pPlot;
	if( IsRunning() )Stop();
}

void CALLBACK CRealtimeDemoImpl::TimerHandler(UINT id, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    CRealtimeDemoImpl *pThis = (CRealtimeDemoImpl*)dwUser;
	
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	// You can modify code in this range as your need
	// Firstly, get the value
	// then call SetCurrentValue()
	
	if( pThis->GetNumOfDatas() <= 0 ) return;
	
	double value;
	for( int i = 0; i < pThis->GetNumOfDatas(); i++ )
	{
		if(i == 0)
			value = 2*sin((double)pThis->GetCounters()[i]*pThis->GetTimePeriod()/1000.0);
		else
			value = cos(pThis->GetCounters()[i] * pThis->GetTimePeriod()/1000.0);
		pThis->SetCurrentValue( i, value );
	}
	
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	
	pThis->OnInsertData();
}

UINT CRealtimeDemoImpl::Restart()
{
	ResetPlot();
	return Start();
}

/******************************************************************\
  function
    name : CreateTimer
    desc : create a realtime timer
  argument
    void
  ret code
    [HANDLE] ,the handle of the timer
\******************************************************************/
UINT CRealtimeDemoImpl::CreateTimer()
{
    //create the timer
    
    // Create a periodic timer
    timeBeginPeriod(m_nTimeResolution);
    m_nTimerID = timeSetEvent(
        GetTimePeriod(),
        m_nTimeResolution, 
        m_pTimerFcn,
        (DWORD)this,
        TIME_PERIODIC);

    m_bRun = true;

    return m_nTimerID;
}

/******************************************************************\
  function
    name : DestroyTimer
    desc : destroy the timer created by calling CreateTimer
  argument
    void
  ret code
    void
\******************************************************************/
void CRealtimeDemoImpl::DestroyTimer()
{

    if ( m_bRun )
    {
        timeKillEvent(m_nTimerID);
        timeEndPeriod(m_nTimeResolution);

        m_bRun = false;
    }


}