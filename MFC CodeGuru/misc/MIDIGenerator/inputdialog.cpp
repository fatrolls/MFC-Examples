// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDialog dialog


CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDialog)
	m_InputLine1 = _T("");
	m_InputLine2 = _T("");
	m_InputLine3 = _T("");
	m_InputLine4 = _T("");
	m_InputLine5 = _T("");
	m_InputLine6 = _T("");
	m_InputLine7 = _T("");
	m_InputLine8 = _T("");
	m_Prompt1 = _T("");
	m_Prompt2 = _T("");
	m_Prompt3 = _T("");
	m_Prompt4 = _T("");
	m_Prompt5 = _T("");
	m_Prompt6 = _T("");
	m_Prompt7 = _T("");
	m_Prompt8 = _T("");
	//}}AFX_DATA_INIT
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDialog)
	DDX_Control(pDX, IDC_INPUTLINE1, m_InputCtrl1);
	DDX_Control(pDX, IDC_INPUTLINE2, m_InputCtrl2);
	DDX_Control(pDX, IDC_INPUTLINE3, m_InputCtrl3);
	DDX_Control(pDX, IDC_INPUTLINE4, m_InputCtrl4);
	DDX_Control(pDX, IDC_INPUTLINE5, m_InputCtrl5);
	DDX_Control(pDX, IDC_INPUTLINE6, m_InputCtrl6);
	DDX_Control(pDX, IDC_INPUTLINE7, m_InputCtrl7);
	DDX_Control(pDX, IDC_INPUTLINE8, m_InputCtrl8);
	DDX_Text(pDX, IDC_INPUTLINE1, m_InputLine1);
	DDX_Text(pDX, IDC_INPUTLINE2, m_InputLine2);
	DDX_Text(pDX, IDC_INPUTLINE3, m_InputLine3);
	DDX_Text(pDX, IDC_INPUTLINE4, m_InputLine4);
	DDX_Text(pDX, IDC_INPUTLINE5, m_InputLine5);
	DDX_Text(pDX, IDC_INPUTLINE6, m_InputLine6);
	DDX_Text(pDX, IDC_INPUTLINE7, m_InputLine7);
	DDX_Text(pDX, IDC_INPUTLINE8, m_InputLine8);
	DDX_Text(pDX, IDC_PROMPT1, m_Prompt1);
	DDX_Text(pDX, IDC_PROMPT2, m_Prompt2);
	DDX_Text(pDX, IDC_PROMPT3, m_Prompt3);
	DDX_Text(pDX, IDC_PROMPT4, m_Prompt4);
	DDX_Text(pDX, IDC_PROMPT5, m_Prompt5);
	DDX_Text(pDX, IDC_PROMPT6, m_Prompt6);
	DDX_Text(pDX, IDC_PROMPT7, m_Prompt7);
	DDX_Text(pDX, IDC_PROMPT8, m_Prompt8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialog)
	//{{AFX_MSG_MAP(CInputDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDialog message handlers


BOOL CInputDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int LastVisible = 1;
	if (m_Prompt8.GetLength() == 0)
		m_InputCtrl8.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 8);
	if (m_Prompt7.GetLength() == 0)
		m_InputCtrl7.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 7);
	if (m_Prompt6.GetLength() == 0)
		m_InputCtrl6.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 6);
	if (m_Prompt5.GetLength() == 0)
		m_InputCtrl5.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 5);
	if (m_Prompt4.GetLength() == 0)
		m_InputCtrl4.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 4);
	if (m_Prompt3.GetLength() == 0)
		m_InputCtrl3.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 3);
	if (m_Prompt2.GetLength() == 0)
		m_InputCtrl2.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 2);
	if (m_Prompt1.GetLength() == 0)
		m_InputCtrl1.ModifyStyle(WS_VISIBLE, 0);
	else
		LastVisible = max(LastVisible, 1);

	// Hier kann noch die Größe des Dialogs modifiziert werden
	CRect rc1;
	CRect rc2;
	CRect rect;
	GetWindowRect(&rect);
	m_InputCtrl1.GetWindowRect(&rc1);
	m_InputCtrl2.GetWindowRect(&rc2);
	ScreenToClient(&rc1);
	ScreenToClient(&rc2);
	rect.bottom -= (8-LastVisible) * (rc2.top-rc1.top);
	MoveWindow(&rect);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
