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

#ifndef  __REALTIMEDEMOIMPL_H_122333444455555__
#define  __REALTIMEDEMOIMPL_H_122333444455555__

#include "RealtimeDemo.h"
#include "RealtimePlotImpl.h"
#include "../DblBufferPlot/DblBufferPlotImpl.h"

class CRealtimeDemoImpl : public CRealtimeDemo, public CRealtimePlotImpl
{
protected:
	HWND		m_hWnd;
public:
	CRealtimeDemoImpl(HWND hWnd);
	virtual ~CRealtimeDemoImpl();

	static void CALLBACK TimerHandler(UINT id, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);

	UINT		CreateTimer();
	void		DestroyTimer();
	
	UINT		Start() { return CreateTimer(); }
	void		Stop() { DestroyTimer(); }
	UINT		Restart();

};

template <typename RealtimeDemoImplT>
class CRealtimeDemoHandler : public CXYHandler<RealtimeDemoImplT>
{
public:
	virtual	bool		OnMouseDown( HWND hWnd, POINT point );
};

class CRealtimeDemoImplI : public CRealtimeDemoImpl, public CRealtimeDemoHandler<CRealtimeDemoImplI>
{
public:
	CRealtimeDemoImplI(HWND hWnd):CRealtimeDemoImpl(hWnd){};
};

//////////////////////////////////////////////////////////////////////////////////////
//
template <typename CRealtimeDemoImplT>
bool	CRealtimeDemoHandler<CRealtimeDemoImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	CRealtimeDemoImplT *pT=static_cast<CRealtimeDemoImplT *>(this);
	if(pT->IsRunning())
	{
		pT->Stop();
	}
	else
	{
		pT->Start();
	}
	return CXYHandler<CRealtimeDemoImplT>::OnMouseDown(hWnd, point);
}

#endif
