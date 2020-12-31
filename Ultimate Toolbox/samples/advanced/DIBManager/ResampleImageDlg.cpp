// ResampleImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dibmanager.h"
#include "ResampleImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResampleImageDlg dialog


CResampleImageDlg::CResampleImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResampleImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResampleImageDlg)
	m_bMaintainRatio = FALSE;
	m_bMatchZoomLevel = FALSE;
	m_sHeightOrig = _T("");
	m_sWidthOrig = _T("");
	m_nWidthPercents = 0;
	m_nWidthPixels = 0;
	m_nHeightPercents = 0;
	m_nHeightPixels = 0;
	m_bConvertTo = FALSE;
	m_nConvertTo = -1;
	//}}AFX_DATA_INIT
	m_nCurrentZoomLevel=0;
	m_bCanConvert=FALSE;
	m_bCanResize=FALSE;
	m_nOrigHeight=0;
	m_nOrigWidth=0;
}


void CResampleImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResampleImageDlg)
	DDX_Control(pDX, IDC_CHECK_MATCH_ZOOM_LEVEL, m_ctlCheckMatchZoomLevel);
	DDX_Control(pDX, IDC_CHECK_CONVERT_TO, m_ctlCheckConvertTo);
	DDX_Control(pDX, IDC_WIDTH_PIXELS, m_ctlEditWidthPixels);
	DDX_Control(pDX, IDC_WIDTH_PERCENTS, m_ctlEditWidthPercents);
	DDX_Control(pDX, IDC_SPIN_WIDTH_PIXELS, m_ctlSpinWidthPixels);
	DDX_Control(pDX, IDC_SPIN_WIDTH_PERCENTS, m_ctlSpinWidthPercents);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_PIXELS, m_ctlSpinHeightPixels);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_PERCENTS, m_ctlSpinHeightPercents);
	DDX_Control(pDX, IDC_HEIGHT_PIXELS, m_ctlEditHeightPixels);
	DDX_Control(pDX, IDC_HEIGHT_PERCENTS, m_ctlEditHeightPercents);
	DDX_Control(pDX, IDC_COMBO_CONVERT_TO, m_ctlComboConvertTo);
	DDX_Control(pDX, IDC_CHECK_MAINTAIN_RATIO, m_ctlCheckMaintainRatio);
	DDX_Check(pDX, IDC_CHECK_MAINTAIN_RATIO, m_bMaintainRatio);
	DDX_Check(pDX, IDC_CHECK_MATCH_ZOOM_LEVEL, m_bMatchZoomLevel);
	DDX_Text(pDX, IDC_HEIGHT_ORIG, m_sHeightOrig);
	DDX_Text(pDX, IDC_WIDTH_ORIG, m_sWidthOrig);
	DDX_Text(pDX, IDC_WIDTH_PERCENTS, m_nWidthPercents);
	DDX_Text(pDX, IDC_WIDTH_PIXELS, m_nWidthPixels);
	DDX_Text(pDX, IDC_HEIGHT_PERCENTS, m_nHeightPercents);
	DDX_Text(pDX, IDC_HEIGHT_PIXELS, m_nHeightPixels);
	DDX_Check(pDX, IDC_CHECK_CONVERT_TO, m_bConvertTo);
	DDX_CBIndex(pDX, IDC_COMBO_CONVERT_TO, m_nConvertTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResampleImageDlg, CDialog)
	//{{AFX_MSG_MAP(CResampleImageDlg)
	ON_BN_CLICKED(IDC_CHECK_CONVERT_TO, OnCheckConvertTo)
	ON_BN_CLICKED(IDC_CHECK_MAINTAIN_RATIO, OnCheckMaintainRatio)
	ON_BN_CLICKED(IDC_CHECK_MATCH_ZOOM_LEVEL, OnCheckMatchZoomLevel)
	ON_EN_CHANGE(IDC_HEIGHT_PERCENTS, OnChangeHeightPercents)
	ON_EN_CHANGE(IDC_HEIGHT_PIXELS, OnChangeHeightPixels)
	ON_EN_CHANGE(IDC_WIDTH_PERCENTS, OnChangeWidthPercents)
	ON_EN_CHANGE(IDC_WIDTH_PIXELS, OnChangeWidthPixels)
	ON_BN_CLICKED(ID_BUTTON_RESET, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResampleImageDlg message handlers

BOOL CResampleImageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// Define array of possible types of convertion
	m_ctlComboConvertTo.AddString(_T("256 color (8-bit)"));
	m_nConvertTo=0;

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinWidthPixels.SetBuddy(&m_ctlEditWidthPixels);
	m_ctlSpinWidthPixels.SetRange(0,32767);
	m_ctlSpinWidthPixels.SetPos(m_nWidthPixels);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_ctlSpinWidthPixels.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinHeightPixels.SetBuddy(&m_ctlEditHeightPixels);
	m_ctlSpinHeightPixels.SetRange(0,32767);
	m_ctlSpinHeightPixels.SetPos(m_nHeightPixels);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_ctlSpinHeightPixels.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinWidthPercents.SetBuddy(&m_ctlEditWidthPercents);
	m_ctlSpinWidthPercents.SetRange(0,32767);
	m_ctlSpinWidthPercents.SetPos(m_nWidthPercents);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_ctlSpinWidthPercents.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinHeightPercents.SetBuddy(&m_ctlEditHeightPercents);
	m_ctlSpinHeightPercents.SetRange(0,32767);
	m_ctlSpinHeightPercents.SetPos(m_nHeightPercents);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_ctlSpinHeightPercents.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);


	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResampleImageDlg::ShowControls(BOOL bHeightChanged) 
{
	UpdateData(TRUE);

	if(!m_bCanConvert)
	{
		// enable convertion controls only if we can do convertion
		m_bConvertTo=FALSE;
		m_ctlCheckConvertTo.EnableWindow(FALSE);
	}
	m_nConvertTo=0;
	m_ctlComboConvertTo.EnableWindow(m_bConvertTo);

	if(m_bMaintainRatio)
	{
		if(bHeightChanged)
		{
			// if we are going to maintain aspect ratio then
			// recalculate width of image based on height
			m_nWidthPercents=m_nHeightPercents;
			m_nWidthPixels=((long)m_nOrigWidth*
				(long)m_nHeightPixels)/((long)m_nOrigHeight);
		}
		else
		{
			// if we are going to maintain aspect ratio then
			// recalculate height of image based on width
			m_nHeightPercents=m_nWidthPercents;
			m_nHeightPixels=((long)m_nOrigHeight*
				(long)m_nWidthPixels)/((long)m_nOrigWidth);
		}
	}

	if(m_bMatchZoomLevel)
	{
		// set height and width corresponding to current zoom level
		m_bMaintainRatio=TRUE;
		m_nWidthPercents=m_nCurrentZoomLevel;
		m_nHeightPercents=m_nCurrentZoomLevel;
		m_nWidthPixels=((long)m_nOrigWidth*(long)m_nCurrentZoomLevel)/(100L);
		m_nHeightPixels=((long)m_nOrigHeight*(long)m_nCurrentZoomLevel)/(100L);
	}
	// set controls enable on/off
	m_ctlCheckMatchZoomLevel.EnableWindow(m_bCanResize);
	m_ctlCheckMaintainRatio.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlEditWidthPixels.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlSpinWidthPixels.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlEditHeightPixels.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlSpinHeightPixels.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlEditWidthPercents.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlSpinWidthPercents.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlEditHeightPercents.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);
	m_ctlSpinHeightPercents.EnableWindow(!m_bMatchZoomLevel && m_bCanResize);

	UpdateData(FALSE);
}

void CResampleImageDlg::OnCheckConvertTo() 
{
	// TODO: Add your control notification handler code here
	ShowControls();	
}

void CResampleImageDlg::OnCheckMaintainRatio() 
{
	// TODO: Add your control notification handler code here
	ShowControls();	
}

void CResampleImageDlg::OnCheckMatchZoomLevel() 
{
	// TODO: Add your control notification handler code here
	ShowControls();	
}

void CResampleImageDlg::OnChangeHeightPercents() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nHeightPixels=((long)m_nOrigHeight*
		(long)m_nHeightPercents)/((long)100);
	UpdateData(FALSE);
	ShowControls(TRUE);	
}

void CResampleImageDlg::OnChangeHeightPixels() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nHeightPercents=((long)100*(long)m_nHeightPixels)/
		((long)m_nOrigHeight);
	UpdateData(FALSE);
	ShowControls(TRUE);	
}

void CResampleImageDlg::OnChangeWidthPercents() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nWidthPixels=((long)m_nOrigWidth*
		(long)m_nWidthPercents)/((long)100);
	UpdateData(FALSE);
	ShowControls();	
}

void CResampleImageDlg::OnChangeWidthPixels() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nWidthPercents=((long)100*(long)m_nWidthPixels)/
		((long)m_nOrigWidth);
	UpdateData(FALSE);
	ShowControls();	
}

void CResampleImageDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	// set size of image to original
	m_nWidthPercents=m_nCurrentZoomLevel;
	m_nHeightPercents=m_nCurrentZoomLevel;
	m_nWidthPixels=((long)m_nOrigWidth*(long)m_nCurrentZoomLevel)/(100L);
	m_nHeightPixels=((long)m_nOrigHeight*(long)m_nCurrentZoomLevel)/(100L);
	m_bMatchZoomLevel=FALSE;
	UpdateData(FALSE);
	ShowControls();	
}
