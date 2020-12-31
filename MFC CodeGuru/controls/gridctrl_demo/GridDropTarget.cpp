// GridDropTarget.cpp : implementation file
//
// CGridDropTarget is an OLE drop target for CGridCtrl. All it does
// is handle the drag and drop windows messages and pass them
// directly onto the grid control.
//
// Written by Chris Maunder 
//        mailto:Chris.Maunder@cbr.clw.csiro.au)
//
// Copyright (c) 1998.

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridDropTarget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridDropTarget

CGridDropTarget::CGridDropTarget()
{
    m_pGridCtrl = NULL;
    m_bRegistered = FALSE;
}

CGridDropTarget::~CGridDropTarget()
{
}

// Overloaded Register() function performs the normal COleDropTarget::Register
// but also serves to connect this COleDropTarget with the parent grid control,
// where all drop messages will ultimately be forwarded.
BOOL CGridDropTarget::Register(CGridCtrl *pGridCtrl)
{
    if (m_bRegistered) return FALSE;

    ASSERT(pGridCtrl->IsKindOf(RUNTIME_CLASS(CGridCtrl)));
    ASSERT(pGridCtrl);

    if (!pGridCtrl || !pGridCtrl->IsKindOf(RUNTIME_CLASS(CGridCtrl)))
        return FALSE;

    m_pGridCtrl = pGridCtrl;

    m_bRegistered = COleDropTarget::Register(pGridCtrl);
    return m_bRegistered;
}

void CGridDropTarget::Revoke()
{
    m_bRegistered = FALSE;
    COleDropTarget::Revoke();
}

BEGIN_MESSAGE_MAP(CGridDropTarget, COleDropTarget)
    //{{AFX_MSG_MAP(CGridDropTarget)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDropTarget message handlers

DROPEFFECT CGridDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint /*point*/)
{
//    TRACE("In CGridDropTarget::OnDragScroll\n");
    if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
    {
        if (dwKeyState & MK_CONTROL)
            return DROPEFFECT_COPY;
        else
            return DROPEFFECT_MOVE;
    } else
        return DROPEFFECT_NONE;
}

DROPEFFECT CGridDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, 
                                        DWORD dwKeyState, CPoint point)
{
    TRACE(_T("In CGridDropTarget::OnDragEnter\n"));
    ASSERT(m_pGridCtrl);

    if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
        return m_pGridCtrl->OnDragEnter(pDataObject, dwKeyState, point);
    else
        return DROPEFFECT_NONE;
}

void CGridDropTarget::OnDragLeave(CWnd* pWnd)
{
    TRACE(_T("In CGridDropTarget::OnDragLeave\n"));
    ASSERT(m_pGridCtrl);

    if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
        m_pGridCtrl->OnDragLeave();
}

DROPEFFECT CGridDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, 
                                       DWORD dwKeyState, CPoint point)
{
//    TRACE("In CGridDropTarget::OnDragOver\n");
    ASSERT(m_pGridCtrl);

    if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
        return m_pGridCtrl->OnDragOver(pDataObject, dwKeyState, point);
    else
        return DROPEFFECT_NONE;
}

BOOL CGridDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
                             DROPEFFECT dropEffect, CPoint point)
{
    TRACE(_T("In CGridDropTarget::OnDrop\n"));
    ASSERT(m_pGridCtrl);

    if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
        return m_pGridCtrl->OnDrop(pDataObject, dropEffect, point);
    else
        return FALSE;
}