// ComboGridCtrl.cpp: implementation of the CComboGridCtrl class.
//
// This is a demo of how to override CGridCtrl in order to offer
// other editing capabilities such as a drop down list
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComboGridCtrl.h"
#include "InPlaceList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CComboGridCtrl, CGridCtrl)
    //{{AFX_MSG_MAP(CComboGridCtrl)
    //}}AFX_MSG_MAP
    ON_NOTIFY(GVN_ENDLABELEDIT, IDC_IPLIST, OnEndInPlaceEdit)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComboGridCtrl::CComboGridCtrl()
{
}

CComboGridCtrl::~CComboGridCtrl()
{
}

//////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////

void CComboGridCtrl::OnEditCell(int nRow, int nCol, UINT nChar)
{
    CCellID cell(nRow, nCol);
    if (!m_bEditable ||!IsCellVisible(nRow, nCol) || !IsValid(cell)) 
        return;

    if (GetItemState(nRow, nCol) & GVIS_READONLY)
        return;

    CRect rect;
    if (!GetCellRect(cell, rect)) return;

    // Send message to parent letting it know we are about to edit
    NM_GRIDVIEW nmgv;
    nmgv.iRow    = nRow;
    nmgv.iColumn = nCol;
    nmgv.hdr.hwndFrom = m_hWnd;
    nmgv.hdr.idFrom = GetDlgCtrlID();
    nmgv.hdr.code = GVN_BEGINLABELEDIT;

    CWnd* pParent = GetOwner();
    if (pParent)
        pParent->SendMessage(WM_NOTIFY, nmgv.hdr.idFrom, (LPARAM)&nmgv);

	CString text = GetItemText(nRow, nCol);
	CStringArray Items;
    Items.Add("Choice 1");
    Items.Add("Choice 2");
    Items.Add("Choice 3");
    Items.Add("Choice 4");
    Items.Add("Choice 5");

	// InPlaceList and auto-deletes itself
	new CInPlaceList(this, rect, nRow, nCol, Items, text, nChar);
}