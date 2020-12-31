/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File critsect.cpp
// class CWizCriticalSection
//
// 29/05/1995 13:08                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "critsect.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
#define new DEBUG_NEW

///////////////////////////////////////////////////////////////////
// class CWizCriticalSection

//*****************************************************************
void	CWizCriticalSection::Init()
{
	ASSERT(m_bInited == FALSE);
	::InitializeCriticalSection(&m_cCriticalSection);
	m_bInited = TRUE;
}
//*****************************************************************
// Default Constructor
CWizCriticalSection::CWizCriticalSection(BOOL bInit)
	: m_bInited (FALSE)
{
	if (bInit)
		Init();
}
//*****************************************************************
// Destructor
CWizCriticalSection::~CWizCriticalSection()
{
	::DeleteCriticalSection(&m_cCriticalSection);
}
//*****************************************************************
