// ColourPickDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColourPickDemo.h"
#include "ColourPickDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColourPickDemoDlg dialog

CColourPickDemoDlg::CColourPickDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CColourPickDemoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CColourPickDemoDlg)
	m_nMode = 1;
	m_bTrack = FALSE;
	m_bDisable = FALSE;
	m_strDefaultText = _T("Automatic");
	m_strCustomText = _T("More Colours...");
	//}}AFX_DATA_INIT
    m_crColour = RGB(0,0,255); // blue
}

void CColourPickDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CColourPickDemoDlg)
    DDX_Control(pDX, IDC_COLOURPICKER, m_ColourBox);
	DDX_Radio(pDX, IDC_MODE1, m_nMode);
	DDX_Check(pDX, IDC_TRACK, m_bTrack);
	DDX_Check(pDX, IDC_DISABLE, m_bDisable);
	DDX_Text(pDX, IDC_DEFAULT_EDIT, m_strDefaultText);
	DDX_Text(pDX, IDC_CUSTOM_EDIT, m_strCustomText);
	//}}AFX_DATA_MAP
    DDX_ColourPicker(pDX, IDC_COLOURPICKER, m_crColour);
}

BEGIN_MESSAGE_MAP(CColourPickDemoDlg, CDialog)
    //{{AFX_MSG_MAP(CColourPickDemoDlg)
	ON_BN_CLICKED(IDC_MODE1, OnModeChange)
	ON_BN_CLICKED(IDC_TRACK, OnTrackColour)
	ON_BN_CLICKED(IDC_DISABLE, OnDisable)
	ON_BN_CLICKED(IDC_MODE2, OnModeChange)
	ON_EN_CHANGE(IDC_CUSTOM_EDIT, OnChangeEdit)
	ON_EN_CHANGE(IDC_DEFAULT_EDIT, OnChangeEdit)
	//}}AFX_MSG_MAP
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
    ON_MESSAGE(CPN_SELENDCANCEL, OnSelEndCancel)
    ON_MESSAGE(CPN_SELCHANGE,    OnSelChange)
    ON_MESSAGE(CPN_CLOSEUP,         OnCloseUp)
    ON_MESSAGE(CPN_DROPDOWN,     OnDropDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourPickDemoDlg message handlers

BOOL CColourPickDemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	UpdateData(FALSE);
	OnModeChange();
	OnTrackColour();

    return TRUE;                // return TRUE  unless you set the focus to a control
}


/////////////////////////////////////////////////////////////////////////////
// CColourPicker message handlers

LONG CColourPickDemoDlg::OnSelEndOK(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Selection ended OK\n");
    return TRUE;
}

LONG CColourPickDemoDlg::OnSelEndCancel(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Selection cancelled\n");
    return TRUE;
}

LONG CColourPickDemoDlg::OnSelChange(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Selection changed\n");
    return TRUE;
}

LONG CColourPickDemoDlg::OnCloseUp(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Colour picker close up\n");
    return TRUE;
}

LONG CColourPickDemoDlg::OnDropDown(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Colour picker drop down\n");
    return TRUE;
}


void CColourPickDemoDlg::OnModeChange() 
{
	UpdateData(TRUE); 
	m_ColourBox.SetSelectionMode(m_nMode? CP_MODE_BK: CP_MODE_TEXT);
}

void CColourPickDemoDlg::OnTrackColour() 
{
	UpdateData(TRUE); 
	m_ColourBox.SetTrackSelection(m_bTrack);
}

void CColourPickDemoDlg::OnDisable() 
{
	UpdateData(TRUE); 
    m_ColourBox.ModifyStyle(m_bDisable? 0 : WS_DISABLED, m_bDisable? WS_DISABLED : 0);
    m_ColourBox.Invalidate();
}

void CColourPickDemoDlg::OnChangeEdit() 
{
    CString str;

    GetDlgItemText(IDC_DEFAULT_EDIT, str);
    m_ColourBox.SetDefaultText(str);
    GetDlgItemText(IDC_CUSTOM_EDIT, str);
    m_ColourBox.SetCustomText(str);
}
