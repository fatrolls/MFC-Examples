#include "stdafx.h"
#include "HookApiCommon.h"
/////////////////////////////////////////////////////////////////////////////
// CShareMemory

IMPLEMENT_DYNCREATE(CShareMemory, CCmdTarget)

CShareMemory::CShareMemory(const char * pszMapName, int nFileSize, BOOL bServer)
{
	m_hMap = NULL;
	m_pBuffer = NULL;
	if (bServer)
		m_hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, nFileSize, pszMapName);
	else
		m_hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, pszMapName);
	if (m_hMap == NULL)
		return;
	m_pBuffer = MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

CShareMemory::~CShareMemory()
{
	if (m_pBuffer)
		UnmapViewOfFile(m_pBuffer);
	if (m_hMap)
		CloseHandle(m_hMap);
}


BEGIN_MESSAGE_MAP(CShareMemory, CCmdTarget)
	//{{AFX_MSG_MAP(CShareMemory)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShareMemory message handlers

LPVOID CShareMemory::GetBuffer() const
{
   return m_pBuffer;
}