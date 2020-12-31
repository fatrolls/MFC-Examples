#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "DlgShadeButtonST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_WEBADDR		_T("http://www.softechsoftware.it")

CDlgShadeButtonST::CDlgShadeButtonST(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShadeButtonST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShadeButtonST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgShadeButtonST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShadeButtonST)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_BTNSHADE1, m_btnButtons[0]);
	DDX_Control(pDX, IDC_BTNSHADE2, m_btnButtons[1]);
	DDX_Control(pDX, IDC_BTNSHADE3, m_btnButtons[2]);
	DDX_Control(pDX, IDC_BTNSHADE4, m_btnButtons[3]);
	DDX_Control(pDX, IDC_BTNSHADE5, m_btnButtons[4]);
	DDX_Control(pDX, IDC_BTNSHADE6, m_btnButtons[5]);
	DDX_Control(pDX, IDC_BTNSHADE7, m_btnButtons[6]);
	DDX_Control(pDX, IDC_BTNSHADE8, m_btnButtons[7]);
	DDX_Control(pDX, IDC_BTNSHADE9, m_btnButtons[8]);
}

BEGIN_MESSAGE_MAP(CDlgShadeButtonST, CDialog)
	//{{AFX_MSG_MAP(CDlgShadeButtonST)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgShadeButtonST::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_btnButtons[0].SetShade(CShadeButtonST::SHS_METAL);
	m_btnButtons[0].SetIcon(IDI_RAZOR);
	//
	m_btnButtons[1].SetShade(CShadeButtonST::SHS_HARDBUMP);
	m_btnButtons[1].SetIcon(IDI_HELP);
	m_btnButtons[1].SetAlign(CButtonST::ST_ALIGN_VERT);
	//
	m_btnButtons[2].SetShade(CShadeButtonST::SHS_SOFTBUMP);
	m_btnButtons[2].SetIcon(IDI_SEARCH1, (int)BTNST_AUTO_GRAY);
	//
	m_btnButtons[3].SetShade(CShadeButtonST::SHS_NOISE, 33);
	m_btnButtons[3].SetIcon(IDI_OK3);
	m_btnButtons[3].SetAlign(CButtonST::ST_ALIGN_VERT);
	//
	m_btnButtons[4].SetShade(CShadeButtonST::SHS_VBUMP,8,20,5,RGB(55,55,255));
	m_btnButtons[4].SetIcon(IDI_HELP2);
	//
	m_btnButtons[5].SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnButtons[5].SetIcon(IDI_WEB2);
	m_btnButtons[5].SetBtnCursor(IDC_HAND2);
	m_btnButtons[5].SetURL(IDS_WEBADDR);
	m_btnButtons[5].SetTooltipText(IDS_WEBADDR);
	//
	m_btnButtons[6].SetShade(CShadeButtonST::SHS_VSHADE,8,20,5,RGB(55,55,255));
	m_btnButtons[6].SetIcon(IDI_CANCEL3);
	m_btnButtons[6].SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	//
	m_btnButtons[7].SetShade(CShadeButtonST::SHS_HSHADE,8,20,5,RGB(55,55,255));
	m_btnButtons[7].SetIcon(IDI_RUN);
	m_btnButtons[7].DrawFlatFocus(TRUE);
	//
	m_btnButtons[8].SetShade(CShadeButtonST::SHS_DIAGSHADE,8,10,5,RGB(55,255,55));
	m_btnButtons[8].SetIcon(IDI_IEDOCUMENT);
	m_btnButtons[8].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 178, 0));
	m_btnButtons[8].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));

	return TRUE;
} // End of OnInitDialog

void CDlgShadeButtonST::OnOK()
{
} // End of OnOK

void CDlgShadeButtonST::OnCancel()
{
} // End of OnCancel
