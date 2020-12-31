// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dibmanager.h"
#include "MainFrm.h"
#include "ImportDlg.h"

#include "oxbmpfle.h"
#include "oxjpgfle.h"
#include "oxjpgcom.h"
#include "oxjpgdom.h"
#include "oxjpgexp.h"

#include "path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog


CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent),
	m_cbFileName(COXHistoryCombo::TBPHorizontalRightCenter,TRUE)
{
	//{{AFX_DATA_INIT(CImportDlg)
	m_bColors = FALSE;
	m_bGrayscale = FALSE;
	m_bNoSmooth = FALSE;
	m_bOnePass = FALSE;
	m_sFileName = _T("");
	m_nColors = 0;
	//}}AFX_DATA_INIT
}


void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDlg)
	DDX_Control(pDX, IDC_COLORS, m_ctlEditColors);
	DDX_Control(pDX, IDC_SPIN_COLORS, m_ctlSpinColors);
	DDX_Control(pDX, IDC_FILENAME, m_cbFileName);
	DDX_Check(pDX, IDC_CHECK_COLORS, m_bColors);
	DDX_Check(pDX, IDC_CHECK_GRAYSCALE, m_bGrayscale);
	DDX_Check(pDX, IDC_CHECK_NO_SMOOTH, m_bNoSmooth);
	DDX_Check(pDX, IDC_CHECK_ONE_PASS, m_bOnePass);
	DDX_Text(pDX, IDC_FILENAME, m_sFileName);
	DDX_Text(pDX, IDC_COLORS, m_nColors);
	DDV_MinMaxInt(pDX, m_nColors, 8, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_CHECK_ONE_PASS, OnCheckOnePass)
	ON_BN_CLICKED(IDC_CHECK_COLORS, OnCheckColors)
	ON_BN_CLICKED(IDC_CHECK_GRAYSCALE, OnCheckGrayscale)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers

BOOL CImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_nColors = 256;
	CheckRadioButton(IDC_RADIO_DM_FLOYD_STEIN,IDC_RADIO_DM_NONE,
		IDC_RADIO_DM_FLOYD_STEIN);
	CheckRadioButton(IDC_RADIO_ONE_TO_ONE,IDC_RADIO_ONE_TO_EIGHT,
		IDC_RADIO_ONE_TO_ONE);
	CheckRadioButton(IDC_RADIO_ONE_TO_ONE,IDC_RADIO_ONE_TO_EIGHT,
		IDC_RADIO_ONE_TO_ONE);
	CheckRadioButton(IDC_RADIO_DCT_INT,IDC_RADIO_DCT_FLOAT,
		IDC_RADIO_DCT_INT);

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinColors.SetBuddy(&m_ctlEditColors);
	m_ctlSpinColors.SetRange(8,256);
	m_ctlSpinColors.SetPos(m_nColors);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinColors.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	// Use auto persistence
	m_cbFileName.SetAutoPersistent(_T("History - Import"));
	m_cbFileName.SetFileDialogParams(TRUE,_T("*.jpg"),NULL,
		OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
		_T("JPEG Images (*.jpg)|*.jpg|All Files (*.*)|*.*||"));
	// set toolbar on the right with a little gap
	COXHistoryCombo::EToolbarPosition eToolbarPosition=m_cbFileName.GetToolbarPosition();
	// unimited number of items in combobox are could be saved 
	m_cbFileName.PositionToolbar(eToolbarPosition, TRUE);
	m_cbFileName.SetMaxHistoryCount(-1);

	UpdateData(FALSE);
	
	ShowButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportDlg::OnOK() 
{
	// TODO: Add extra validation here

	if(UpdateData()==0 || !CheckFileName())
		return;
 
	// operation of exporting JPEG to DIB
	// could be time-consuming
	BeginWaitCursor();

	COXBMPFile BMPFile(&m_tmpBMPFile);
	COXJPEGFile jpgFile(m_sFileName);	
	COXJPEGDecompressor JDecompr;

	JDecompr.SetGrayScale(m_bGrayscale);
	JDecompr.SetNoSmooth(m_bNoSmooth);
	JDecompr.SetOnePass(m_bOnePass);

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
	JDecompr.SetDisCosTranf(DCT);

	EDitherMethod DM;
	switch(GetCheckedRadioButton(IDC_RADIO_DM_FLOYD_STEIN,IDC_RADIO_DM_NONE))
	{
	case IDC_RADIO_DM_FLOYD_STEIN:
		{
			DM=DM_FloydStein;
			break;
		}
	case IDC_RADIO_DM_ORDERED:
		{
			DM=DM_Ordered;
			break;
		}
	case IDC_RADIO_DM_NONE:
		{
			DM=DM_None;
			break;
		}
	default:
		{
			DM=DM_FloydStein;
			break;
		}
	}
	JDecompr.SetDitherMethod(DM);

	EDecompScale DS;
	switch(GetCheckedRadioButton(IDC_RADIO_ONE_TO_ONE,IDC_RADIO_ONE_TO_EIGHT))
	{
	case IDC_RADIO_ONE_TO_ONE:
		{
			DS=DS_OneOne;
			break;
		}
	case IDC_RADIO_ONE_TO_TWO:
		{
			DS=DS_OneHalf;
			break;
		}
	case IDC_RADIO_ONE_TO_FOUR:
		{
			DS=DS_OneFourth;
			break;
		}
	case IDC_RADIO_ONE_TO_EIGHT:
		{
			DS=DS_OneEight;
			break;
		}
	default:
		{
			DS=DS_OneOne;
			break;
		}
	}
	JDecompr.SetScale(DS);

	if(m_bColors)
	{
		JDecompr.SetColors(m_nColors);
	}

	short nReturn(1);
	TCHAR ErrorBuffer[SIZE_ERROR_BUF];
	TRY
	{
		// the only line of code that we need to decompress JPEG to bitmap file
		nReturn = JDecompr.DoDecompress(&jpgFile, &BMPFile);
		if (nReturn == 2)
			AfxMessageBox(JDecompr.GetWarningMessages());
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

void CImportDlg::OnCheckOnePass() 
{
	// TODO: Add your control notification handler code here
	
	ShowButtons();
}

void CImportDlg::OnCheckColors() 
{
	// TODO: Add your control notification handler code here
	
	ShowButtons();
}

void CImportDlg::OnCheckGrayscale() 
{
	// TODO: Add your control notification handler code here
	
	ShowButtons();
}

LRESULT CImportDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
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

void CImportDlg::ShowButtons() 
{
	// show buttons depending on some conditions

	UpdateData();
	ctlOnePass().EnableWindow(!m_bGrayscale && m_bColors);
	if(m_bGrayscale)
	{
		ctlOnePass().SetCheck(1);
		m_bOnePass=TRUE;
	}
	else
	{
		if(!m_bColors)
		{
			ctlOnePass().SetCheck(0);
			m_bOnePass=FALSE;
		}
	}
	if(!m_bOnePass)
	{
		CheckRadioButton(IDC_RADIO_DM_FLOYD_STEIN,IDC_RADIO_DM_NONE,
			IDC_RADIO_DM_NONE);
	}
	ctlDitherMethodFS().EnableWindow(m_bOnePass);
	ctlDitherMethodOrdered().EnableWindow(m_bOnePass);
	ctlDitherMethodNone().EnableWindow(m_bOnePass);
}

BOOL CImportDlg::CheckFileName()
{
	// check if typed file already opened
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(pMainFrame->CheckFileAlreadyOpened(m_sFileName,TRUE))
	{
		return FALSE;
	}

	// check if typed directory exist
	COXPathSpec path;
	path.SetPath(m_sFileName);
	if(path.IsEmpty() || !path.Exists())
	{
		AfxMessageBox(_T("Entered file doesn't exist!"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
