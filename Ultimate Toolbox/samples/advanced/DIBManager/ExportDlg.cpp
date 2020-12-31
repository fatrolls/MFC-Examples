// ExportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIBManager.h"
#include "ExportDlg.h"

#include "oxbmpfle.h"
#include "oxjpgfle.h"
#include "oxjpgcom.h"
#include "oxjpgdom.h"
#include "oxjpgexp.h"

#include "path.h"
#include "dir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog


CExportDlg::CExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDlg::IDD, pParent),
	m_cbFileName(COXHistoryCombo::TBPHorizontalRightCenter,TRUE)
{
	//{{AFX_DATA_INIT(CExportDlg)
	m_bBaseline = FALSE;
	m_bGrayscale = FALSE;
	m_bOptimize = FALSE;
	m_bProgressive = FALSE;
	m_bSmooth = FALSE;
	m_sFileName = _T("");
	m_nQuality = 0;
	m_nSmooth = 0;
	//}}AFX_DATA_INIT
}


void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDlg)
	DDX_Control(pDX, IDC_SMOOTH, m_ctlEditSmooth);
	DDX_Control(pDX, IDC_QUALITY, m_ctlEditQuality);
	DDX_Control(pDX, IDC_SPIN_SMOOTH, m_ctlSpinSmooth);
	DDX_Control(pDX, IDC_SPIN_QUALITY, m_ctlSpinQuality);
	DDX_Control(pDX, IDC_FILENAME, m_cbFileName);
	DDX_Check(pDX, IDC_CHECK_BASELINE, m_bBaseline);
	DDX_Check(pDX, IDC_CHECK_GRAYSCALE, m_bGrayscale);
	DDX_Check(pDX, IDC_CHECK_OPTIMIZE, m_bOptimize);
	DDX_Check(pDX, IDC_CHECK_PROGRESSIVE, m_bProgressive);
	DDX_Check(pDX, IDC_CHECK_SMOOTH, m_bSmooth);
	DDX_Text(pDX, IDC_FILENAME, m_sFileName);
	DDX_Text(pDX, IDC_QUALITY, m_nQuality);
	DDV_MinMaxUInt(pDX, m_nQuality, 0, 100);
	DDX_Text(pDX, IDC_SMOOTH, m_nSmooth);
	DDV_MinMaxUInt(pDX, m_nSmooth, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportDlg, CDialog)
	//{{AFX_MSG_MAP(CExportDlg)
	ON_BN_CLICKED(IDC_CHECK_PROGRESSIVE, OnCheckProgressive)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportDlg message handlers

BOOL CExportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinQuality.SetBuddy(&m_ctlEditQuality);
	m_ctlSpinQuality.SetRange(0,100);
	m_ctlSpinQuality.SetPos(m_nQuality);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinQuality.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinSmooth.SetBuddy(&m_ctlEditSmooth);
	m_ctlSpinSmooth.SetRange(1,100);
	m_ctlSpinSmooth.SetPos(m_nSmooth);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinQuality.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	m_nQuality = 75;
	m_nSmooth = 10;
	CheckRadioButton(IDC_RADIO_DCT_INT,IDC_RADIO_DCT_FLOAT,IDC_RADIO_DCT_INT);

	// Use auto persistence
	m_cbFileName.SetAutoPersistent(_T("History - Export"));
	m_cbFileName.SetFileDialogParams(FALSE,_T("*.jpg"),NULL,
		OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
		_T("JPEG Images (*.jpg)|*.jpg|All Files (*.*)|*.*||"));
	// set toolbar on the right with a little gap
	COXHistoryCombo::EToolbarPosition eToolbarPosition=m_cbFileName.GetToolbarPosition();
	m_cbFileName.PositionToolbar(eToolbarPosition, TRUE);
	// unimited number of items in combobox are could be saved 
	m_cbFileName.SetMaxHistoryCount(-1);

	UpdateData(FALSE);
	
	// show buttons depending on set properties
	ShowButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportDlg::OnCheckProgressive() 
{
	// TODO: Add your control notification handler code here
	
	ShowButtons();
}

void CExportDlg::OnOK() 
{
	// TODO: Add extra validation here

	// check if typed directory exists
	if(UpdateData()==0 || !CheckFileName())
		return;
 
	// operation of exporting from DIB to JPEG
	// could be time-consuming
	BeginWaitCursor();

	// create bitmap file on the base of current DIB image
	// m_tmpBMPFile we initialize when we run the export dialog
	COXBMPFile BMPFile(&m_tmpBMPFile);
	COXJPEGFile jpgFile(m_sFileName);	
	COXJPEGCompressor JCompr;

	JCompr.SetQuality(m_nQuality);
	if(m_bSmooth)
	{
		JCompr.SetSmooth(m_nSmooth);
	}

	JCompr.SetGrayScale(m_bGrayscale);
	JCompr.SetBaseLine(m_bBaseline);
	JCompr.SetProgressive(m_bProgressive);
	JCompr.SetOptimize(m_bOptimize);
	EDiscreteCosTransf DCT;
	switch(GetCheckedRadioButton(IDC_RADIO_DCT_INT,
		IDC_RADIO_DCT_FLOAT))
	{
	case IDC_RADIO_DCT_INT:
		{
			DCT=DC_Int;
			break;
		}
	case IDC_RADIO_DCT_FAST:
		{
			DCT=DC_FastInt;
			break;
		}
	case IDC_RADIO_DCT_FLOAT:
		{
			DCT=DC_Float;
			break;
		}
	default:
		{
			DCT=DC_Int;
			break;
		}
	}
	JCompr.SetDisCosTranf(DCT);

	short nReturn(1);
	TCHAR ErrorBuffer[SIZE_ERROR_BUF];
	TRY
	{
		// the only line of code that we need to compress bitmap file to JPEG
		nReturn = JCompr.DoCompress(&BMPFile, &jpgFile);
		if (nReturn == 2)
			AfxMessageBox(JCompr.GetWarningMessages());
	}
	CATCH(COXJPEGException, e)
	{
		// if something went wrong then notify about it
		e->GetErrorMessage(ErrorBuffer, SIZE_ERROR_BUF);
		AfxMessageBox(CString("Exception : ") + ErrorBuffer);

		TRACE((LPCTSTR)ErrorBuffer);
	}
	END_CATCH

	EndWaitCursor();

	if(nReturn!=0)
		return;

	CDialog::OnOK();
}

LRESULT CExportDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
	// we use this function to let buttons in HistoryCombo toolbar
	// to get some notification
	UNUSED(wParam);
	UNUSED_ALWAYS(lParam);
	ASSERT_VALID(this);
	ASSERT(wParam == MSGF_DIALOGBOX);
	BOOL bContinueIdle = TRUE;

	// Pass on to the history combo
	m_cbFileName.OnIdle();

	return bContinueIdle;
}

void CExportDlg::ShowButtons() 
{
	// TODO: Add your control notification handler code here

	// show buttons depending on some conditions

	UpdateData();
	ctlOptimize().EnableWindow(!m_bProgressive);
	if(m_bProgressive)
	{
		ctlOptimize().SetCheck(1);
	}
}

BOOL CExportDlg::CheckFileName()
{
	// check if typed directory exist
	COXPathSpec path;
	path.SetPath(m_sFileName);
	COXDirSpec dir(path.GetDirectory());
	if(dir.IsEmpty() || !dir.Exists())
	{
		AfxMessageBox(_T("Designated directory doesn't exist!"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

