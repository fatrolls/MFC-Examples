// ComboBoxEx.cpp : implementation file
//
// Copyright (c) Chris Maunder 1997.
// Please feel free to use and distribute.

#include "stdafx.h"
#include "ComboBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx

CComboBoxEx::CComboBoxEx()
{
	m_bAutoComplete = TRUE;
}

CComboBoxEx::~CComboBoxEx()
{
}


BEGIN_MESSAGE_MAP(CComboBoxEx, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxEx)
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx message handlers

BOOL CComboBoxEx::PreTranslateMessage(MSG* pMsg)
{
	// Need to check for backspace/delete. These will modify the text in
	// the edit box, causing the auto complete to just add back the text
	// the user has just tried to delete. 

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboBoxEx::OnEditUpdate() 
{
	// if we are not to auto update the text, get outta here
	if (!m_bAutoComplete) return;

	// Get the text in the edit box
	CString str;
	GetWindowText(str);
	int nLength = str.GetLength();

	// Search for, and select in, and string in the combo box that is prefixed
	// by the text in the edit box
	if (SelectString(-1, str) == CB_ERR) 
		SetWindowText(str);		// No text selected, so restore what was there before

	// Set the text selection as the additional text that we have added
	SetEditSel(nLength,-1);
}
