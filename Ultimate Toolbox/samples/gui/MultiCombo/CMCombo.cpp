// CMCombo.cpp : implementation file
//

#include "stdafx.h"
#include "MCombo.h"
#include "CMCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCombo

CMCombo::CMCombo()
{
}

CMCombo::~CMCombo()
{
}


BEGIN_MESSAGE_MAP(CMCombo, CComboBox)
	//{{AFX_MSG_MAP(CMCombo)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCombo message handlers

void CMCombo::OnSelchange() 
{
	int x = 1;
	
}

void CMCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int z=1;
	
}

BOOL CMCombo::PreCreateWindow(CREATESTRUCT& cs) 
{
	
	
	return CComboBox::PreCreateWindow(cs);
}
