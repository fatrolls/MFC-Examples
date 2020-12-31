// example.cpp : implementation file
//

#include "stdafx.h"

#include "Roll32.h"
#include "example.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample dialog


CExample::CExample(CWnd* pParent /*=NULL*/)
	: COXRollup(CExample::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExample)
	m_strTestEdit = _T("");
	//}}AFX_DATA_INIT
}


void CExample::DoDataExchange(CDataExchange* pDX)
{
	COXRollup::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExample)
	DDX_Text(pDX, IDC_TEST_EDIT, m_strTestEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExample, COXRollup)
	//{{AFX_MSG_MAP(CExample)
	ON_BN_CLICKED(IDC_BTN_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExample message handlers

void CExample::OnApply() 
{
	RUpdateData(TRUE);
	Send2MR(ID_APPLY);
}
