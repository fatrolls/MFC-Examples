// BCGToolbarDropTarget.cpp : implementation file
//

#include "stdafx.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarDropTarget.h"
#include "BCGToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropTarget

CBCGToolbarDropTarget::CBCGToolbarDropTarget()
{
	m_pOwner = NULL;
}

CBCGToolbarDropTarget::~CBCGToolbarDropTarget()
{
}


BEGIN_MESSAGE_MAP(CBCGToolbarDropTarget, COleDropTarget)
	//{{AFX_MSG_MAP(CBCGToolbarDropTarget)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBCGToolbarDropTarget::Register (CBCGToolBar* pOwner)
{
	m_pOwner = pOwner;
	return COleDropTarget::Register (pOwner);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropTarget message handlers

DROPEFFECT CBCGToolbarDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	ASSERT (m_pOwner != NULL);

	if (!m_pOwner->m_bCustomizeMode ||
		!pDataObject->IsDataAvailable (CBCGToolbarButton::m_cFormat))
	{
		return DROPEFFECT_NONE;
	}

	return m_pOwner -> OnDragEnter(pDataObject, dwKeyState, point);
}

void CBCGToolbarDropTarget::OnDragLeave(CWnd* pWnd) 
{
	ASSERT (m_pOwner != NULL);
	m_pOwner -> OnDragLeave ();
}

DROPEFFECT CBCGToolbarDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	ASSERT (m_pOwner != NULL);

	if (!m_pOwner->m_bCustomizeMode ||
		!pDataObject->IsDataAvailable (CBCGToolbarButton::m_cFormat))
	{
		return DROPEFFECT_NONE;
	}

	return m_pOwner -> OnDragOver(pDataObject, dwKeyState, point);
}

DROPEFFECT CBCGToolbarDropTarget::OnDropEx(CWnd* pWnd, 
							COleDataObject* pDataObject, 
							DROPEFFECT dropEffect, 
							DROPEFFECT dropList, CPoint point) 
{
	ASSERT (m_pOwner != NULL);

	if (!m_pOwner->m_bCustomizeMode ||
		!pDataObject->IsDataAvailable (CBCGToolbarButton::m_cFormat))
	{
		return DROPEFFECT_NONE;
	}

	return m_pOwner -> OnDrop(pDataObject, dropEffect, point) ?
			dropEffect : DROPEFFECT_NONE;
}
