// BCGToolbarDropSource.cpp : implementation file
//

#include "stdafx.h"
#include "BCGToolbarDropSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropSource

CBCGToolbarDropSource::CBCGToolbarDropSource()
{
	m_bDeleteOnDrop = TRUE;
	m_bEscapePressed = FALSE;
	m_bDragStarted = FALSE;

	m_hcurDelete = NULL;
}

CBCGToolbarDropSource::~CBCGToolbarDropSource()
{
}


BEGIN_MESSAGE_MAP(CBCGToolbarDropSource, COleDropSource)
	//{{AFX_MSG_MAP(CBCGToolbarDropSource)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropSource message handlers

SCODE CBCGToolbarDropSource::GiveFeedback(DROPEFFECT dropEffect) 
{
	HCURSOR hcur = NULL;

	switch (dropEffect)
	{
	case DROPEFFECT_MOVE:
	case DROPEFFECT_COPY:
		break;

	default:
		hcur = m_hcurDelete;
		break;
	}

	if (hcur == NULL)
	{
		return COleDropSource::GiveFeedback(dropEffect);
	}

	::SetCursor (hcur);
	return NOERROR;
}

SCODE CBCGToolbarDropSource::QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState) 
{
	if (m_bDeleteOnDrop && m_hcurDelete != NULL)
	{
		::SetCursor (m_hcurDelete);
	}

	m_bEscapePressed = bEscapePressed;
	return COleDropSource::QueryContinueDrag(bEscapePressed, dwKeyState);
}

BOOL CBCGToolbarDropSource::OnBeginDrag(CWnd* pWnd) 
{
	m_bDragStarted = TRUE;
	return COleDropSource::OnBeginDrag(pWnd);
}
