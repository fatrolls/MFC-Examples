// DlgRotate.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgRotate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************/
// DlgRotate dialog


DlgRotate::DlgRotate(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRotate::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRotate)
	m_angle = 0.0f;
	//}}AFX_DATA_INIT
}


void DlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRotate)
	DDX_Text(pDX, IDC_EDIT1, m_angle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRotate, CDialog)
	//{{AFX_MSG_MAP(DlgRotate)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**************************************/
// DlgRotate message handlers
