// TypeAheadCombo.cpp : implementation file
//

#include "stdafx.h"
#include "cas.h"
#include "TypeAheadCombo.h"
#include "SingTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo

CTypeAheadCombo::CTypeAheadCombo()
{
}

CTypeAheadCombo::~CTypeAheadCombo()
{
}


BEGIN_MESSAGE_MAP(CTypeAheadCombo, CComboBox)
	//{{AFX_MSG_MAP(CTypeAheadCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo message handlers

void CTypeAheadCombo::PreSubclassWindow() 
{
	m_xEdit.SubclassDlgItem(1001, this);	
	CComboBox::PreSubclassWindow();
}
