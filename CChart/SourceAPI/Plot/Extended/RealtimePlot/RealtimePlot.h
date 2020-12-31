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

#ifndef  __REALTIMEPLOT_H_122333444455555__
#define __REALTIMEPLOT_H_122333444455555__

//#include "../../Basics/Origin.h"
#include <vector>
using namespace std;
//static UINT WM_INSERTSINGLEDATA = RegisterWindowMessage("DataInsert");

class CRealtimePlot
{
public:
	CRealtimePlot();
	virtual ~CRealtimePlot();

protected:

	double			m_fTimeSpan;//in second
	int				m_nTimePeriod;//in milsecond	
	
	int				m_nDatas;
	vector<double>	m_vfMax,m_vfMin;
	vector<double>	m_vfValue;
	vector<bool>	m_vbArrival;

	bool			m_bHoldXValue;
	vector<__int64>	m_vnCounters;
	
public:
	inline	double			GetTimeSpan() { return m_fTimeSpan; }
	inline	void			SetTimeSpan( double span ) { m_fTimeSpan = span; }
	inline	int				GetTimePeriod() { return m_nTimePeriod; }
	inline	void			SetTimePeriod( int period ) { m_nTimePeriod = period; }
	
	inline	bool			GetHoldXValue() { return m_bHoldXValue; }
	inline	void			SetHoldXValue( bool hold ) { m_bHoldXValue = hold; }
	
	inline	int				GetNumOfDatas() { return m_nDatas; }
	virtual void			SetNumOfDatas( int num ) = 0;

	inline	vector<double>	&GetValueMax() { return m_vfMax; }
	inline	vector<double>	&GetValueMin() { return m_vfMin; }
	inline	vector<double>	&GetValue() { return m_vfValue; }
	inline	vector<bool>	&GetArrival() { return m_vbArrival; }
	inline	vector<__int64>	&GetCounters() { return m_vnCounters; }
	inline	__int64			GetMaxCounter(){__int64 count=-1; for(int i=0; i<m_nDatas; i++){if(m_vnCounters[i]>count)count=m_vnCounters[i];}return count;}
	
	inline	void			SetCurrentValue( int idx, double value ) { if(idx<0 || idx>=m_nDatas)return; m_vfValue[idx] = value; m_vbArrival[idx] = true; m_vnCounters[idx]++; }
	
};

#endif