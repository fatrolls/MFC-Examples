// HMS.H

#include "StdAfx.h"

class CHMS
{
private:
	int m_nHr, m_nMn, m_nSc;
	CCriticalSection m_cs;
public:
	CHMS() : m_nHr(0), m_nMn(0), m_nSc(0) {}

	~CHMS() {}

	void SetTime(int nSecs)
	{
		m_cs.Lock();
		m_nSc = nSecs % 60;
		m_nMn = (nSecs / 60) % 60;
		m_nHr = nSecs / 3600;
		m_cs.Unlock();
	}
    
	int GetTotalSecs()
	{
		int nTotalSecs;
		m_cs.Lock();
		nTotalSecs = m_nHr * 3600 + m_nMn * 60 + m_nSc;
		m_cs.Unlock();
		return nTotalSecs;
	}
    
	void IncrementSecs()
	{
		m_cs.Lock();
		SetTime(GetTotalSecs() + 1);
		m_cs.Unlock();
	}
};
