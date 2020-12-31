/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File critsect.h
// class CWizCriticalSection
//
// 29/05/1995 13:08                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizCriticalSection_H
#define __CWizCriticalSection_H

/////////////////////////////////////////////////////////////////////////////
// class CWizCriticalSection
class CWizCriticalSection
{
public:
// Constructors:
	CWizCriticalSection (BOOL bInit = TRUE);
// Destructor:
	~CWizCriticalSection ();
public:
// Operations:
	void Begin() 
		{ 
		if (!m_bInited)
			Init();
		::EnterCriticalSection (&m_cCriticalSection); 
		}
	void End  () { ::LeaveCriticalSection (&m_cCriticalSection); }
protected:
// Implementation
	void	Init();
// Members:
	BOOL			m_bInited;
	CRITICAL_SECTION	m_cCriticalSection;
};

/////////////////////////////////////////////////////////////////////////////
class CWizCritSect
{
public:
// Constructors:
	CWizCritSect (CWizCriticalSection& rCriticalSection)
		: m_rCriticalSection (rCriticalSection),
		  m_bStillIn(TRUE)
			{
			m_rCriticalSection.Begin();
			}
// Destructor:
	~CWizCritSect()
			{
			if (m_bStillIn)
				m_rCriticalSection.End();
			}
	void Enough()
			{
			if (m_bStillIn)
				m_rCriticalSection.End();
			m_bStillIn = FALSE;
			}
protected:
// Members:
	CWizCriticalSection&	m_rCriticalSection;
	BOOL					m_bStillIn;
};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizCriticalSection_H


