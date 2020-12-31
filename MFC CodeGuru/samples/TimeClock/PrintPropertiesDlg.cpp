// PrintPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"		// main symbols

#include "PrintPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintPropertiesDlg dialog


CPrintPropertiesDlg::CPrintPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintPropertiesDlg)
	m_strFri = _T("");
	m_strMon = _T("");
	m_strSat = _T("");
	m_strThu = _T("");
	m_strTue = _T("");
	m_strWed = _T("");
	m_strSun = _T("");
	//}}AFX_DATA_INIT
}


void CPrintPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintPropertiesDlg)
	DDX_Text(pDX, IDC_FRI, m_strFri);
	DDX_Text(pDX, IDC_MON, m_strMon);
	DDX_Text(pDX, IDC_SAT, m_strSat);
	DDX_Text(pDX, IDC_THU, m_strThu);
	DDX_Text(pDX, IDC_TUE, m_strTue);
	DDX_Text(pDX, IDC_WED, m_strWed);
	DDX_Text(pDX, IDC_SUN, m_strSun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintPropertiesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintPropertiesDlg message handlers
