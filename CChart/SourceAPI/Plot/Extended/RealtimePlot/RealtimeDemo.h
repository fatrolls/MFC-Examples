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

#ifndef  __REALTIMEDEMO_H_122333444455555__
#define  __REALTIMEDEMO_H_122333444455555__

class CRealtimePlot;

class CRealtimeDemo
{
public:
	CRealtimeDemo();
	virtual ~CRealtimeDemo();

	void	SetDefaults();
	void	CopySettings(CRealtimeDemo *demo);
protected:
	//CRealtimePlot	*m_pPlot;

	void			(CALLBACK *m_pTimerFcn)(UINT id, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);

	int				m_nTimeResolution;
	int				m_nTimerID;
	bool			m_bRun;

public:
	int				GetTimeResolution() { return m_nTimeResolution; }
	void			SetTimeResolution( int res ) { m_nTimeResolution = res; }

	void			SetTimerFcn( void (CALLBACK *timerFcn)(UINT, UINT, DWORD, DWORD, DWORD)){ m_pTimerFcn = timerFcn; }

	bool			IsRunning(){ return m_bRun; }

	//CRealtimePlot	*GetPlot() { return m_pPlot; }
};

#endif
