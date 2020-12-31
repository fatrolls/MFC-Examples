// PhonesListBox.cpp : implementation file
//

#include "stdafx.h"
#include "Phones.h"
#include "PhonesListBox.h"
#include "PhoneEdit.h"
#include "EditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhonesListBox

CPhonesListBox::CPhonesListBox()
{
}

CPhonesListBox::~CPhonesListBox()
{
}

BEGIN_MESSAGE_MAP(CPhonesListBox, CListBox)
	//{{AFX_MSG_MAP(CPhonesListBox)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(LBN_DBLCLK, OnEditItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhonesListBox message handlers

int CPhonesListBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_font.CreatePointFont (80, _T ("MS Sans Serif"));
    SetFont (&m_font, FALSE);
    SetTabStops (128);
	return 0;
}

void CPhonesListBox::OnEditItem() 
{
    CEditDialog dlg;

    CString strItem;
    int nIndex = GetCurSel ();
    GetText (nIndex, strItem);
    int nPos = strItem.Find (_T ('\t'));

    dlg.m_strName = strItem.Left (nPos);
    dlg.m_strPhone = strItem.Right (strItem.GetLength () - nPos - 1);

    if (dlg.DoModal () == IDOK) {
        strItem = dlg.m_strName + _T ("\t") + dlg.m_strPhone;
        DeleteString (nIndex);
        AddString (strItem);
    }
    SetFocus ();
}

void CPhonesListBox::NewEntry()
{
    CEditDialog dlg;
    if (dlg.DoModal () == IDOK) {
        CString strItem = dlg.m_strName + _T ("\t") + dlg.m_strPhone;
        AddString (strItem);
    }
    SetFocus ();
}
