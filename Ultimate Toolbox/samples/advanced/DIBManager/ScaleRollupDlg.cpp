// ScaleRollupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dibmanager.h"
#include "mainfrm.h"
#include "ScaleRollupDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleRollupDlg dialog


CScaleRollupDlg::CScaleRollupDlg(CWnd* pParent /*=NULL*/)
	: COXRollup(CScaleRollupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleRollupDlg)
	m_nScaledHeight = 0;
	m_nScaledWidth = 0;
	m_nZoomLevel = 0;
	//}}AFX_DATA_INIT
	m_nOrigHeight=0;
	m_nOrigWidth=0;
}


void CScaleRollupDlg::DoDataExchange(CDataExchange* pDX)
{
	COXRollup::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleRollupDlg)
	DDX_Control(pDX, IDC_ZOOM_LEVEL, m_ctlZoomLevel);
	DDX_Control(pDX, IDC_SPIN_ZOOM_LEVEL, m_ctlSpinZoom);
	DDX_Control(pDX, IDC_PICTURE, m_ctlPicture);
	DDX_Text(pDX, IDC_SCALED_HEIGHT, m_nScaledHeight);
	DDX_Text(pDX, IDC_SCALED_WIDTH, m_nScaledWidth);
	DDX_Text(pDX, IDC_ZOOM_LEVEL, m_nZoomLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleRollupDlg, COXRollup)
	//{{AFX_MSG_MAP(CScaleRollupDlg)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_EN_CHANGE(IDC_ZOOM_LEVEL, OnChangeZoomLevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleRollupDlg message handlers

void CScaleRollupDlg::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	
	if(m_nZoomLevel<ID_MIN_ZOOM_LEVEL)
	{
		m_nZoomLevel=ID_MIN_ZOOM_LEVEL;
		UpdateData(FALSE);
	}


	// notify current recipient window 
	// that we have to change zoom level
	RUpdateData(TRUE);
	Send2MR(ID_APPLY);

	ShowControls();
}

void CScaleRollupDlg::OnChangeZoomLevel() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	ShowControls();
}

BOOL CScaleRollupDlg::OnInitDialog() 
{
	COXRollup::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinZoom.SetBuddy(&m_ctlZoomLevel);
	m_ctlSpinZoom.SetRange(ID_MIN_ZOOM_LEVEL,ID_MAX_ZOOM_LEVEL);
	m_ctlSpinZoom.SetPos(m_nZoomLevel);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_ctlSpinZoom.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScaleRollupDlg::ShowControls() 
{
	if(m_nZoomLevel>ID_MAX_ZOOM_LEVEL)
		m_nZoomLevel=ID_MAX_ZOOM_LEVEL;

	CRect rectPicture, rectNewPicture;
	CPoint ptPictureCenter;

	m_nScaledWidth=((long)m_nOrigWidth*(long)m_nZoomLevel)/(100L);
	m_nScaledHeight=((long)m_nOrigHeight*(long)m_nZoomLevel)/(100L);

	m_ctlPicture.GetWindowRect(&rectPicture);
	ScreenToClient(&rectPicture);
	
	ptPictureCenter.x=rectPicture.left+rectPicture.Width()/2;
	ptPictureCenter.y=rectPicture.top+rectPicture.Height()/2;

	// we chose this formula because it let the picture control
	// to go from 10% to 1000%
	int nPictureWidth=(3*(int)sqrt((float)m_nZoomLevel)-(int)sqrt((float)m_nZoomLevel)/2)*2;
	
	rectNewPicture.left=ptPictureCenter.x-nPictureWidth/2;
	rectNewPicture.top=ptPictureCenter.y-nPictureWidth/2;
	rectNewPicture.right=rectNewPicture.left+nPictureWidth;
	rectNewPicture.bottom=rectNewPicture.top+nPictureWidth;

	if(rectNewPicture.left-rectPicture.left!=0)
	{
		m_ctlPicture.MoveWindow(rectNewPicture.left, rectNewPicture.top, 
			rectNewPicture.Width(), rectNewPicture.Height());
	}

	UpdateData(FALSE);
}


