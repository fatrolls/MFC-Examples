// TriangleButtonDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TriangleButtonDemo.h"
#include "TriangleButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoDlg dialog

CTriangleButtonDemoDlg::CTriangleButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTriangleButtonDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTriangleButtonDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTriangleButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTriangleButtonDemoDlg)
	DDX_Control(pDX, IDC_BUTTONTEXT, buttontext);
	DDX_Control(pDX, IDTRI_F_7, trif7);
	DDX_Control(pDX, IDTRI_F_6, trif6);
	DDX_Control(pDX, IDTRI_3D_7, tri3d7);
	DDX_Control(pDX, IDTRI_3D_6, tri3d6);
	DDX_Control(pDX, IDTRI_F_5, trif5);
	DDX_Control(pDX, IDTRI_F_4, trif4);
	DDX_Control(pDX, IDTRI_F_3, trif3);
	DDX_Control(pDX, IDTRI_F_2, trif2);
	DDX_Control(pDX, IDTRI_F_1, trif1);
	DDX_Control(pDX, IDTRI_3D_5, tri3d5);
	DDX_Control(pDX, IDTRI_3D_4, tri3d4);
	DDX_Control(pDX, IDTRI_3D_3, tri3d3);
	DDX_Control(pDX, IDTRI_3D_2, tri3d2);
	DDX_Control(pDX, IDTRI_3D_1, tri3d1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTriangleButtonDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTriangleButtonDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_BUTTONTEXT, OnChangeButtontext)
	ON_BN_CLICKED(IDC_CH_DISABLE, OnChDisable)
	ON_BN_CLICKED(IDC_RA_DOWN, OnRaDown)
	ON_BN_CLICKED(IDC_RA_LEFT, OnRaLeft)
	ON_BN_CLICKED(IDC_RA_RIGHT, OnRaRight)
	ON_BN_CLICKED(IDC_RA_UP, OnRaUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoDlg message handlers

BOOL CTriangleButtonDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTriangleButtonDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTriangleButtonDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTriangleButtonDemoDlg::OnChangeButtontext() 
{
	CString text;
	buttontext.GetWindowText(text);	

	trif1.SetWindowText(text);
	trif2.SetWindowText(text);
	trif3.SetWindowText(text);
	trif4.SetWindowText(text);
	trif5.SetWindowText(text);
	trif6.SetWindowText(text);
	trif7.SetWindowText(text);

	tri3d1.SetWindowText(text);
	tri3d2.SetWindowText(text);
	tri3d3.SetWindowText(text);
	tri3d4.SetWindowText(text);
	tri3d5.SetWindowText(text);
	tri3d6.SetWindowText(text);
	tri3d7.SetWindowText(text);

}

void CTriangleButtonDemoDlg::OnChDisable() 
{
	trif1.EnableWindow(!trif1.IsWindowEnabled());
	trif2.EnableWindow(!trif2.IsWindowEnabled());
	trif3.EnableWindow(!trif3.IsWindowEnabled());
	trif4.EnableWindow(!trif4.IsWindowEnabled());
	trif5.EnableWindow(!trif5.IsWindowEnabled());
	trif6.EnableWindow(!trif6.IsWindowEnabled());
	trif7.EnableWindow(!trif7.IsWindowEnabled());

	tri3d1.EnableWindow(!tri3d1.IsWindowEnabled());
	tri3d2.EnableWindow(!tri3d2.IsWindowEnabled());
	tri3d3.EnableWindow(!tri3d3.IsWindowEnabled());
	tri3d4.EnableWindow(!tri3d4.IsWindowEnabled());
	tri3d5.EnableWindow(!tri3d5.IsWindowEnabled());
	tri3d6.EnableWindow(!tri3d6.IsWindowEnabled());
	tri3d7.EnableWindow(!tri3d7.IsWindowEnabled());
}


void CTriangleButtonDemoDlg::OnRaDown() 
{
	ChangeTriButtonDirection(CTriangleButton::POINT_DOWN);
}

void CTriangleButtonDemoDlg::OnRaLeft() 
{
	ChangeTriButtonDirection(CTriangleButton::POINT_LEFT);
}

void CTriangleButtonDemoDlg::OnRaRight() 
{
	ChangeTriButtonDirection(CTriangleButton::POINT_RIGHT);
}

void CTriangleButtonDemoDlg::OnRaUp() 
{
	ChangeTriButtonDirection(CTriangleButton::POINT_UP);
}


void CTriangleButtonDemoDlg::ChangeTriButtonDirection(CTriangleButton::POINTDIRECTION d)
{
	trif1.SetDirection(d);
	trif2.SetDirection(d);
	trif3.SetDirection(d);
	trif4.SetDirection(d);
	trif5.SetDirection(d);
	trif6.SetDirection(d);
	trif7.SetDirection(d);

	tri3d1.SetDirection(d);
	tri3d2.SetDirection(d);
	tri3d3.SetDirection(d);
	tri3d4.SetDirection(d);
	tri3d5.SetDirection(d);
	tri3d6.SetDirection(d);
	tri3d7.SetDirection(d);

	Invalidate();
}
