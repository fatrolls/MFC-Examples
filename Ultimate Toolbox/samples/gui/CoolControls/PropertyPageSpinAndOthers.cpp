// PropertyPageSpinAndOthers.cpp : implementation file
//

#include "stdafx.h"
#include "CoolControls.h"
#include "PropertyPageSpinAndOthers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSpinAndOthers property page

IMPLEMENT_DYNCREATE(CPropertyPageSpinAndOthers, CPropertyPage)

CPropertyPageSpinAndOthers::CPropertyPageSpinAndOthers() : CPropertyPage(CPropertyPageSpinAndOthers::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageSpinAndOthers)
	m_bDisable = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageSpinAndOthers::~CPropertyPageSpinAndOthers()
{
}

void CPropertyPageSpinAndOthers::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageSpinAndOthers)
	DDX_Control(pDX, IDC_SPIN_VERT2, m_spinVert2);
	DDX_Control(pDX, IDC_SPIN_VERT1, m_spinVert1);
	DDX_Control(pDX, IDC_SPIN_HORZ, m_spinHorz);
	DDX_Control(pDX, IDC_SLIDER_VERT_RIGHT, m_sliderVertRight);
	DDX_Control(pDX, IDC_SLIDER_VERT_LEFT, m_sliderVertLeft);
	DDX_Control(pDX, IDC_SLIDER_VERT_BOTH, m_sliderVertBoth);
	DDX_Control(pDX, IDC_SLIDER_HORZ_TOP, m_sliderHorzTop);
	DDX_Control(pDX, IDC_SLIDER_HORZ_BOTTOM, m_sliderHorzBottom);
	DDX_Control(pDX, IDC_SLIDER_HORZ_BOTH, m_sliderHorzBoth);
	DDX_Control(pDX, IDC_SCROLLBAR_VERT, m_scrollVert);
	DDX_Control(pDX, IDC_SCROLLBAR_HORZ, m_scrollHorz);
	DDX_Control(pDX, IDC_PROGRESS_HORZ, m_progressHorz);
	DDX_Control(pDX, IDC_CHECK_DISABLE_ALL, m_btnDisable);
	DDX_Check(pDX, IDC_CHECK_DISABLE_ALL, m_bDisable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageSpinAndOthers, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageSpinAndOthers)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ALL, OnCheckDisableAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSpinAndOthers message handlers

void CPropertyPageSpinAndOthers::OnCheckDisableAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CWnd* pChildWnd=GetWindow(GW_CHILD);
	while(pChildWnd!=NULL)
	{
		if(pChildWnd!=&m_btnDisable)
			pChildWnd->EnableWindow(!m_bDisable);
		pChildWnd=pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CPropertyPageSpinAndOthers::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	SCROLLINFO si={ sizeof(SCROLLINFO) };
	si.fMask=SIF_ALL;
	si.nMin=0;
	si.nMax=20;
	si.nPage=3;
	si.nPos=7;
	si.nTrackPos=0;
	m_scrollHorz.SetScrollInfo(&si);
	m_scrollVert.SetScrollInfo(&si);

	m_progressHorz.SetRange(0,100);
	m_progressHorz.SetPos(60);

	m_sliderHorzBoth.SetRange(0,100);
	m_sliderHorzBoth.SetSelection(20,40);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
