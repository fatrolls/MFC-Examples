// ScrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollTipDemo.h"
#include "ScrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog


CScrollDlg::CScrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollDlg)
	//}}AFX_DATA_INIT
}


void CScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollDlg)
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_HORZ_SCROLL_1, m_wndHorzScroll1);
	DDX_Control(pDX, IDC_HORZ_SCROLL_2, m_wndHorzScroll2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScrollDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg message handlers

BOOL CScrollDlg::OnInitDialog() 
	{
	CDialog::OnInitDialog();

	// Set initial values
	SCROLLINFO scrollInfo;
	::ZeroMemory(&scrollInfo, sizeof(scrollInfo));
	scrollInfo.cbSize = sizeof(scrollInfo);
	scrollInfo.fMask = SIF_ALL;

	m_wndHScrollTipOwner1.InterceptHorizontalScroll(&m_wndHorzScroll1);
	scrollInfo.nMin = 0; 
    scrollInfo.nMax = 99; 
    scrollInfo.nPage = 10; 
    scrollInfo.nPos = 0; 
	m_wndHorzScroll1.SetScrollInfo(&scrollInfo);
	m_wndHScrollTipOwner1.SetMask(_T("Page %p"));
	m_wndHScrollTipOwner1.SetLeftTop(TRUE);
	m_wndHScrollTipOwner1.SetPageAlign(TRUE);

	m_wndHScrollTipOwner2.InterceptHorizontalScroll(&m_wndHorzScroll2);
	scrollInfo.nMin = 0; 
    scrollInfo.nMax = 99; 
    scrollInfo.nPage = 10; 
    scrollInfo.nPos = 0; 
	m_wndHorzScroll2.SetScrollInfo(&scrollInfo);
	m_wndHScrollTipOwner2.SetMask(_T("Pos %a"));
	m_wndHScrollTipOwner2.SetLeftTop(TRUE);
	m_wndHScrollTipOwner2.SetPageAlign(FALSE);

	// ... Just attach a temporary CWnd to the vertical scrollbar
	//     without subclassing (this must work as well)
	CWnd* pWndVertScroll = GetDlgItem(IDC_VERT_SCROLL_1);
	ASSERT(pWndVertScroll != NULL);
	m_wndVScrollTipOwner1.InterceptVerticalScroll(pWndVertScroll);
	scrollInfo.nMin = 0; 
    scrollInfo.nMax = 99; 
    scrollInfo.nPage = 10; 
    scrollInfo.nPos = 0; 
	pWndVertScroll->SetScrollInfo(SB_CTL, &scrollInfo);
	m_wndVScrollTipOwner1.SetMask(_T("Page %p"));
	m_wndVScrollTipOwner1.SetLeftTop(TRUE);
	m_wndVScrollTipOwner1.SetPageAlign(TRUE);

	m_wndListScrollTipOwner.InterceptVerticalScroll(&m_wndList, TRUE);
	m_wndList.AddString(_T("One"));
	m_wndList.AddString(_T("Two"));
	m_wndList.AddString(_T("Three"));
	m_wndList.AddString(_T("Four"));
	m_wndList.AddString(_T("Five"));
	m_wndList.AddString(_T("Six"));
	m_wndList.AddString(_T("Seven"));
	m_wndList.AddString(_T("Eight"));
	m_wndList.AddString(_T("Nine"));
	m_wndList.AddString(_T("Ten"));
	m_wndListScrollTipOwner.SetMask(_T("Pos %a"));
	m_wndListScrollTipOwner.SetLeftTop(TRUE);
	m_wndListScrollTipOwner.SetPageAlign(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}
