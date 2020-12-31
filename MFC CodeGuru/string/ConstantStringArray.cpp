/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File ConstantStringArray.cpp
// class CWizConstantStringArray
//
// 14/04/1996 11:57                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "ConstantStringArray.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
#define new DEBUG_NEW

CWizDefaultTypedLocalHeap CWizConstantStringArray::m_cHeap;

///////////////////////////////////////////////////////////////////
// class CWizConstantStringArray
//*****************************************************************
void CWizConstantStringArray::Cleanup()
{
	if (m_pPointers != NULL)
		m_cHeap.Free(m_pPointers);
	m_pPointers = NULL;

	if (m_pData != NULL)
		m_cHeap.Free(m_pData);
	m_pData     = NULL;
	m_nPtrsSize = m_nDataSize = 0;
}
//*****************************************************************
void CWizConstantStringArray::Alloc()
{
	ASSERT(m_pPointers  == NULL);
	ASSERT(m_pData		== NULL);

	m_pPointers = (int *)m_cHeap.Alloc(m_nPtrsSize*sizeof(*m_pPointers));
	try
		{
		m_pData		= (LPTSTR)m_cHeap.Alloc(m_nDataSize*sizeof(*m_pData));
		}
	catch(...)
		{
		if (m_pPointers != NULL)
			m_cHeap.Free(m_pPointers);
		m_pPointers = NULL;

		throw;
		}
	ASSERT(m_pPointers  != NULL);
	ASSERT(m_pData		!= NULL);
}
//*****************************************************************
void CWizConstantStringArray::ReAlloc()
{
	m_pPointers = (int *)m_cHeap.ReAlloc(m_pPointers, m_nPtrsSize*sizeof(*m_pPointers));
	m_pData		= (LPTSTR)m_cHeap.ReAlloc(m_pData,m_nDataSize*sizeof(*m_pData));
	ASSERT(m_pPointers  != NULL);
	ASSERT(m_pData		!= NULL);
}
//*****************************************************************
void CWizConstantStringArray::Init(const CWizConstantStringArray& T)
{
	m_nPtrsSize = T.m_nPtrsSize;
	m_nDataSize = T.m_nDataSize;
	if (m_nPtrsSize > 0 && m_nDataSize > 0)
		{
		Alloc();
		memcpy(m_pData, T.m_pData, m_nDataSize*sizeof(*m_pData));
		memcpy(m_pPointers, T.m_pPointers, m_nPtrsSize*sizeof(*m_pPointers));
		}
	else
		{
		ASSERT(m_nPtrsSize == 0 && m_nDataSize == 0);
		}
}
//*****************************************************************
int CWizConstantStringArray::Add(LPCTSTR str)
{
	const int len = strlen(str) + 1;
	register int		i = 0, j = 0;
	if (m_pPointers == NULL || m_pData == NULL)
		{
		ASSERT(m_pPointers == NULL && m_pData == NULL);
		m_nPtrsSize = 1;
		m_nDataSize = len;
		Alloc();
		}
	else
		{
		i = m_nPtrsSize;
		j = m_nDataSize;
		m_nDataSize += len;
		m_nPtrsSize++;
		ReAlloc();
		}
	m_pPointers[i] = j;
	memcpy(&m_pData[j], str, len);
	return i;
}
//*****************************************************************
void CWizConstantStringArray::Add(const CWizConstantStringArray& T)
{
	if (m_pPointers == NULL || m_pData == NULL)
		{
		ASSERT(m_pPointers == NULL && m_pData == NULL);
		Init(T);
		}
	else
		{
		register int i = m_nPtrsSize;
		register int j = m_nDataSize;
		m_nPtrsSize += T.m_nPtrsSize;
		m_nDataSize += T.m_nDataSize;
		ReAlloc();
		for (register int ii = 0; ii < T.m_nPtrsSize; ii++)
			m_pPointers[i + ii] = T.m_pPointers[ii] + j;
		memcpy(m_pData + j, T.m_pData,T.m_nDataSize*sizeof(*m_pData));
		}
}
//*****************************************************************
