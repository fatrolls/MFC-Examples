// ==========================================================================
// 							Class Implementation : COXDiffProgress
// ==========================================================================

// Source file : progress.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "progress.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXDiffProgress, CObject)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:
	// LONG m_MinVal;
	// --- The minimum value of the progress bar (specified with Init())

	// LONG m_MaxVal;
	// --- The maximumvalue of the progress bar (specified with Init())

	// LONG m_CurPos;
	// --- The current value of the progress bar

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXDiffProgress::COXDiffProgress()
	:
	m_MinVal(0),
	m_MaxVal(0),
	m_CurPos(0)
	{
	}

void COXDiffProgress::Init(LONG minVal, LONG maxVal, LPCTSTR pszMessage)
	{     
	 
	_tprintf(_T("%s\r\n"),pszMessage);
	_tprintf(_T("________________________________________\r"));

	if (maxVal == minVal)
		maxVal = minVal + 1;

	m_MinVal = minVal;
	m_MaxVal = maxVal;
	m_CurPos = 0;
	}

BOOL COXDiffProgress::Adjust(LONG curVal)
	{
	// ... Must have initialized first
	ASSERT( ! (m_MinVal == 0 &&	m_MaxVal == 0 && m_CurPos == 0) );


	LONG pos;

	pos = 40 * (curVal - m_MinVal) / (m_MaxVal - m_MinVal);
	while (pos > m_CurPos)
		{
		_tprintf(_T("#"));
		m_CurPos++;
		}

	return TRUE;
	}

void COXDiffProgress::Abort(LPCTSTR pszMessage)
	{
	TRACE(_T("COXDiffProgress::Abort : %s\n"), pszMessage);
	_ftprintf(stderr,_T("%s\n"),pszMessage);
	exit(-1);
	}

void COXDiffProgress::Close()
	{
	Adjust(m_MaxVal);
	_tprintf(_T("\r\n"));

	m_MinVal = 0;
	m_MaxVal = 0;
	m_CurPos = 0;
	}

#ifdef _DEBUG
void COXDiffProgress::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << TEXT("\nm_MinVal : ") << m_MinVal;
	dc << TEXT("\nm_MaxVal : ") << m_MaxVal;
	dc << TEXT("\nm_CurPos : ") << m_CurPos;
	}

void COXDiffProgress::AssertValid() const
	{
	CObject::AssertValid();
	ASSERT(m_MinVal <= m_MaxVal);
	ASSERT(m_MinVal <= m_CurPos);
	ASSERT(m_CurPos <= m_MaxVal);
	}
#endif

COXDiffProgress::~COXDiffProgress()
	{
	}

// protected:
// private:
// ==========================================================================

