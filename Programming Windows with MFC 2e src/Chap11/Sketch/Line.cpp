// Line.cpp : implementation file
//

#include "stdafx.h"
#include "Sketch.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLine

IMPLEMENT_SERIAL (CLine, CCmdTarget, 1)

CLine::CLine()
{
}

CLine::CLine (POINT from, POINT to)
{
	m_ptFrom = from;
	m_ptTo = to;
}

CLine::~CLine()
{
}

BEGIN_MESSAGE_MAP(CLine, CCmdTarget)
	//{{AFX_MSG_MAP(CLine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLine message handlers

void CLine::Serialize(CArchive& ar) 
{
    if (ar.IsStoring())
    {
        ar << m_ptFrom << m_ptTo;
    }
    else
    {
        ar >> m_ptFrom >> m_ptTo;
    }
}

void CLine::Draw(CDC *pDC)
{
    pDC->SelectStockObject (BLACK_PEN);
    pDC->MoveTo (m_ptFrom);
    pDC->LineTo (m_ptTo);
}
