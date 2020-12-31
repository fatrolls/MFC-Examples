// MMIO.cpp
#include "StdAfx.h"
#include "MMIO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


void CMMIO::Open(const char* pszFileName, DWORD dwOpenFlags)
{
	ASSERT(AfxIsValidString(pszFileName));
	m_hmmio = ::mmioOpen((char*)pszFileName, NULL, dwOpenFlags);
}

void CMMIO::Open(CMMMemoryIOInfo &mmioinfo)
{
	m_hmmio = ::mmioOpen(NULL, &mmioinfo, MMIO_READWRITE);
}
