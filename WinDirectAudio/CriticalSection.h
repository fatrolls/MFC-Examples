#include "stdafx.h"

#ifndef INCLUDE_CRITICALSECTION
#define INCLUDE_CRITICALSECTION

/************************************************************************/
/* CCriticalSection                                                     */
/************************************************************************/
class CCriticalSection
{
protected:
	CRITICAL_SECTION m_cs;
public:
	CCriticalSection() { InitializeCriticalSection(&m_cs); }
	~CCriticalSection() { DeleteCriticalSection(&m_cs); }

	void Enter() { EnterCriticalSection(&m_cs); }
	void Leave() { LeaveCriticalSection(&m_cs); }
};

#endif
