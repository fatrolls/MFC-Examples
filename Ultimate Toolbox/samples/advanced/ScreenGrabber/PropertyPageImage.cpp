// PropertyPageImage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScreenGrabber.h"
#include "PropertyPageImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImage property page

//IMPLEMENT_DYNCREATE(CPropertyPageImage, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPageImage::m_nHelpIDs[] = 
{
	IDC_CHECK_RESIZE, IDH_CHECK_RESIZE,
	IDC_STATIC_WIDTH, IDH_STATIC_WIDTH,
	IDC_EDIT_WIDTH, IDH_EDIT_WIDTH,
	IDC_SPIN_WIDTH, IDH_SPIN_WIDTH,
	IDC_STATIC_HEIGHT, IDH_STATIC_HEIGHT,
	IDC_EDIT_HEIGHT, IDH_EDIT_HEIGHT,
	IDC_SPIN_HEIGHT, IDH_SPIN_HEIGHT,
	IDC_CHECK_MAINTAIN_RATIO, IDH_CHECK_MAINTAIN_RATIO,
	0, 0
};


CPropertyPageImage::CPropertyPageImage() : 
	COXContextHelpPropertyPage(CPropertyPageImage::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageImage)
	m_bMaintainRatio = FALSE;
	m_bResize = FALSE;
	m_nHeight = 0;
	m_nWidth = 0;
	//}}AFX_DATA_INIT
}

CPropertyPageImage::~CPropertyPageImage()
{
}

void CPropertyPageImage::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageImage)
	DDX_Control(pDX, IDC_STATIC_WIDTH, m_ctlStaticWidth);
	DDX_Control(pDX, IDC_STATIC_HEIGHT, m_ctlStaticHeight);
	DDX_Control(pDX, IDC_SPIN_WIDTH, m_ctlSpinWidth);
	DDX_Control(pDX, IDC_SPIN_HEIGHT, m_ctlSpinHeight);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_ctlEditWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_ctlEditHeight);
	DDX_Control(pDX, IDC_CHECK_RESIZE, m_ctlCheckResize);
	DDX_Control(pDX, IDC_CHECK_MAINTAIN_RATIO, m_ctlCheckMaintainRatio);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDV_MinMaxUInt(pDX, m_nHeight, 1, 16384);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 1, 16384);
	DDX_Check(pDX, IDC_CHECK_MAINTAIN_RATIO, m_bMaintainRatio);
	DDX_Check(pDX, IDC_CHECK_RESIZE, m_bResize);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPageImage, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageImage)
	ON_BN_CLICKED(IDC_CHECK_RESIZE, OnCheckResize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImage message handlers

BOOL CPropertyPageImage::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlStaticWidth,
		_T("Define the width of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlStaticHeight,
		_T("Define the height of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlSpinWidth,
		_T("Change the width of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlSpinHeight,
		_T("Change the height of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlEditWidth,
		_T("Change the width of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlEditHeight,
		_T("Change the height of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckResize,
		_T("Lets customize the height and width of captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckMaintainRatio,
		_T("Maintains aspect ratio of captured image"));
	ASSERT(result != 0) ;

	return result;
}



BOOL CPropertyPageImage::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_RESIZING)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_RESIZING, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_RESIZING, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_CHECK_MAINTAIN_RATIO)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_CHECK_MAINTAIN_RATIO, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);

	// check if all variables are correct
	CheckVars();

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinWidth.SetBuddy(&m_ctlEditWidth);
	m_ctlSpinWidth.SetRange(ID_MIN_WIDTH,ID_MAX_WIDTH);
	m_ctlSpinWidth.SetPos(m_nWidth);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinWidth.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinHeight.SetBuddy(&m_ctlEditHeight);
	m_ctlSpinHeight.SetRange(ID_MIN_HEIGHT,ID_MAX_HEIGHT);
	m_ctlSpinHeight.SetPos(m_nHeight);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinHeight.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	UpdateData(FALSE);
	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageImage::OnCheckResize() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	ShowControls();
}

void CPropertyPageImage::ShowControls() 
{
	if(m_bResize)
	{
		m_ctlEditWidth.EnableWindow(TRUE);
		m_ctlSpinWidth.EnableWindow(TRUE);
		m_ctlEditHeight.EnableWindow(TRUE);
		m_ctlSpinHeight.EnableWindow(TRUE);
		m_ctlCheckMaintainRatio.EnableWindow(TRUE);
	}
	else
	{
		m_ctlEditWidth.EnableWindow(FALSE);
		m_ctlSpinWidth.EnableWindow(FALSE);
		m_ctlEditHeight.EnableWindow(FALSE);
		m_ctlSpinHeight.EnableWindow(FALSE);
		m_ctlCheckMaintainRatio.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CPropertyPageImage::CheckVars() 
{
	if(m_nWidth<ID_MIN_WIDTH || m_nWidth>ID_MAX_WIDTH)
	{
		m_nWidth=::GetSystemMetrics(SM_CXSCREEN);
	}
	if(m_nHeight<ID_MIN_HEIGHT || m_nHeight>ID_MAX_HEIGHT)
	{
		m_nHeight=::GetSystemMetrics(SM_CYSCREEN);
	}
}

