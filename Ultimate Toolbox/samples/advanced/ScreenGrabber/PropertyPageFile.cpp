// PropertyPageFile.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenGrabber.h"
#include "PropertyPageFile.h"

#include "oxdirdlg.h"
#include "path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageFile property page

//IMPLEMENT_DYNCREATE(CPropertyPageFile, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPageFile::m_nHelpIDs[] = 
{
	IDC_STATIC_FILE_NAME, IDH_STATIC_FILE_NAME,
	IDC_COMBO_FILE_NAME, IDH_COMBO_FILE_NAME,
	IDC_STATIC_FILE_TYPE, IDH_STATIC_FILE_TYPE,
	IDC_COMBO_FILE_TYPE, IDH_COMBO_FILE_TYPE,
	IDC_CHECK_AUTOMATIC_NAMING, IDH_CHECK_AUTOMATIC_NAMING,
	IDC_BUTTON_CAPTURE_DIR, IDH_BUTTON_CAPTURE_DIR,
	IDC_STATIC_CAPTURE_DIR, IDH_STATIC_CAPTURE_DIR,
	0, 0
};


CPropertyPageFile::CPropertyPageFile() : 
	COXContextHelpPropertyPage(CPropertyPageFile::IDD),
	m_ctlComboFileName(COXHistoryCombo::TBPHorizontalRightCenter,FALSE)
{
	//{{AFX_DATA_INIT(CPropertyPageFile)
	m_bAutomaticNaming = FALSE;
	m_sFileName = _T("");
	m_sFileType = _T("");
	m_sCaptureDir = _T("");
	//}}AFX_DATA_INIT
	m_bInitialized=FALSE;
}

CPropertyPageFile::~CPropertyPageFile()
{
}

void CPropertyPageFile::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageFile)
	DDX_Control(pDX, IDC_COMBO_FILE_NAME, m_ctlComboFileName);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_ctlComboFileType);
	DDX_Control(pDX, IDC_STATIC_FILE_TYPE, m_ctlStaticFileType);
	DDX_Control(pDX, IDC_STATIC_FILE_NAME, m_ctlStaticFileName);
	DDX_Control(pDX, IDC_STATIC_CAPTURE_DIR, m_ctlStaticCaptureDir);
	DDX_Control(pDX, IDC_CHECK_AUTOMATIC_NAMING, m_ctlCheckAutomaticNaming);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE_DIR, m_ctlButtonDir);
	DDX_CBString(pDX, IDC_COMBO_FILE_NAME, m_sFileName);
	DDX_CBString(pDX, IDC_COMBO_FILE_TYPE, m_sFileType);
	DDX_Text(pDX, IDC_STATIC_CAPTURE_DIR, m_sCaptureDir);
	DDX_Check(pDX, IDC_CHECK_AUTOMATIC_NAMING, m_bAutomaticNaming);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPageFile, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageFile)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_DIR, OnButtonCaptureDir)
	ON_BN_CLICKED(IDC_CHECK_AUTOMATIC_NAMING, OnCheckAutomaticNaming)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageFile message handlers

BOOL CPropertyPageFile::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlStaticFileType,
		_T("Define the type of file to save captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlStaticFileName,
		_T("Define the name of file to save captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlStaticCaptureDir,
		_T("The name of directory where the file will be saved"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlComboFileType,
		_T("Change the type of file to save captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlComboFileName,
		_T("Change the name of file to save captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckAutomaticNaming,
		_T("Automatically set a name of file to save captured image"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlButtonDir,
		_T("Change the name of directory where the file will be saved"));
	ASSERT(result != 0) ;

	return result;
}

BOOL CPropertyPageFile::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_DIR)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_DIR, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_DIR, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_COMBO_FILE_NAME)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_COMBO_FILE_NAME, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_COMBO_FILE_NAME, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_COMBO_FILE_TYPE)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_COMBO_FILE_TYPE, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_COMBO_FILE_TYPE, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_STATIC_CAPTURE_DIR)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_CAPTURE_DIR, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_CAPTURE_DIR, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_BUTTON_CAPTURE_DIR)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_BUTTON_CAPTURE_DIR, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);

	// Define array of possible types of file
	m_ctlComboFileType.AddString(_T("Windows Bitmap (*.bmp)"));
	m_ctlComboFileType.AddString(_T("JPEG Bitmap (*.jpg)"));
	// check if all variables are correct
	CheckVars();

	// Use auto persistence
	m_ctlComboFileName.SetAutoPersistent(_T("History - FileName"));
	m_ctlComboFileName.SetMaxHistoryCount(-1);
	m_ctlComboFileName.ShowButton(2,FALSE);
	m_ctlComboFileName.RefreshToolbar();
	COXHistoryCombo::EToolbarPosition eToolbarPosition=
		m_ctlComboFileName.GetToolbarPosition();
	m_ctlComboFileName.PositionToolbar(eToolbarPosition, TRUE);

	UpdateData(FALSE);
	ShowControls();

	m_bInitialized=TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageFile::OnButtonCaptureDir() 
{
	// TODO: Add your control notification handler code here
	
	TRY
	{
		// try to get new capture directory
		UpdateData(TRUE);

		DWORD flags = OFN_SHOWHELP | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		
		// Ask the user to select a directory
		COXDirectoryDialog dirDlg(m_sCaptureDir,_T("Pick Capture Directory"),TRUE,flags);
		if (dirDlg.DoModal()==IDOK)
		{
			m_sCaptureDir=dirDlg.GetDirectory();
			UpdateData(FALSE);
		}
	}
	CATCH_ALL(px)
	{
		// Catch all exception and NEVER pass them on to the calling
		// function (may not be MFC) !
		TRACE(_T("CPropertyPageFile::OnButtonCaptureDir() : Catching exception, aborting function\n"));
	}
	END_CATCH_ALL
}

void CPropertyPageFile::OnCheckAutomaticNaming() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CPropertyPageFile::ShowControls() 
{
	UpdateData(TRUE);
	if(m_bAutomaticNaming)
	{
		m_ctlComboFileName.EnableWindow(FALSE);
	}
	else
	{
		m_ctlComboFileName.EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CPropertyPageFile::CheckVars() 
{
	if(m_ctlComboFileType.FindStringExact(-1,m_sFileType)==CB_ERR)
	{
		if(m_ctlComboFileType.GetCount()>0)
		{
			m_ctlComboFileType.GetLBText(0,m_sFileType);
		}
	}

	// check if Capture Directory exists
	COXPathSpec pathSpec;
	if(!pathSpec.SetDirectory(m_sCaptureDir))
	{
		// if Capture Directory doesn't exist then
		// set it to Current Directory
		pathSpec.DoGetCurrentDir();
	}

	if(m_bAutomaticNaming)
	{
		// check if we are capable of automatically naming Capture File
		if(!pathSpec.MakeUnique())
		{
			m_bAutomaticNaming=FALSE;
		}
	}

	if(!m_bAutomaticNaming)
	{
		if(m_sFileName.IsEmpty())
		{
			m_sFileName=_T("ScreenShot");
		}
	}

}

LRESULT CPropertyPageFile::OnKickIdle(WPARAM wParam, LPARAM /*lParam*/)
{
	UNREFERENCED_PARAMETER(wParam);
	//use this function to let History Combo's toolbars to get messages
	ASSERT_VALID(this);
	ASSERT(wParam == MSGF_DIALOGBOX);
	BOOL bContinueIdle = TRUE;

	// Pass on to the history combo
	m_ctlComboFileName.OnIdle();

	return bContinueIdle;
}


void CPropertyPageFile::OnSize(UINT nType, int cx, int cy) 
{
	COXContextHelpPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	if(m_bInitialized && UpdateData())
	{
		m_ctlComboFileName.RefreshToolbar();
		UpdateData(FALSE);
	}
}

