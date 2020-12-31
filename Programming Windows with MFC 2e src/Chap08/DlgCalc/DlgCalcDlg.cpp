// DlgCalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgCalc.h"
#include "DlgCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcDlg dialog

CDlgCalcDlg::CDlgCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hAccel = ::LoadAccelerators (AfxGetInstanceHandle (),
        MAKEINTRESOURCE (IDR_ACCEL));

    m_bFixPending = FALSE;
    m_bErrorFlag = FALSE;
    m_bDecimalInString = FALSE;
    m_bStackLiftEnabled = FALSE;
    m_bNewX = TRUE;

	for (int i=0; i<4; i++)
		m_dblStack[i] = 0.0;
	m_dblMemory = 0.0;
	m_strFormat = _T ("%0.2f");
}

void CDlgCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgCalcDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SUBTRACT, OnSubtract)
	ON_BN_CLICKED(IDC_MULTIPLY, OnMultiply)
	ON_BN_CLICKED(IDC_DIVIDE, OnDivide)
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_BN_CLICKED(IDC_CHGSIGN, OnChangeSign)
	ON_BN_CLICKED(IDC_EXP, OnExponent)
	ON_BN_CLICKED(IDC_STO, OnStore)
	ON_BN_CLICKED(IDC_RCL, OnRecall)
	ON_BN_CLICKED(IDC_FIX, OnFix)
	ON_BN_CLICKED(IDC_CLX, OnClear)
	ON_BN_CLICKED(IDC_DECIMAL, OnDecimal)
	ON_BN_CLICKED(IDC_DEL, OnDelete)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE (BN_CLICKED, IDC_0, IDC_9, OnDigit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcDlg message handlers

BOOL CDlgCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	// Set the application's icon.
	//
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	//
	// Remove the Size and Maximize commands from the system menu.
	//
	CMenu* pMenu = GetSystemMenu (FALSE);
	pMenu->DeleteMenu (SC_SIZE, MF_BYCOMMAND);
	pMenu->DeleteMenu (SC_MAXIMIZE, MF_BYCOMMAND);

	//
	// Initialize m_rect with the coordinates of the control representing
	// the calculator's output window. Then destroy the control.
	//
	CWnd* pWnd = GetDlgItem (IDC_DISPLAYRECT);
	pWnd->GetWindowRect (&m_rect);
	pWnd->DestroyWindow ();
	ScreenToClient (&m_rect);

	//
	// Initialize m_cxChar and m_cyChar with the average character width
	// and height.
	//
    TEXTMETRIC tm;
    CClientDC dc (this);
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight - tm.tmDescent;

	//
	// Initialize the calculator's output window and return.
	//
    DisplayXRegister ();
	return TRUE;
}

void CDlgCalcDlg::OnPaint() 
{
	CPaintDC dc (this);
	dc.DrawEdge (m_rect, EDGE_SUNKEN, BF_RECT);
	UpdateDisplay (m_strDisplay);
}

BOOL CDlgCalcDlg::PreTranslateMessage(MSG* pMsg) 
{
    if (m_hAccel != NULL)
        if (::TranslateAccelerator (m_hWnd, m_hAccel, pMsg))
            return TRUE;
    
    return CDialog::PreTranslateMessage (pMsg);
}

BOOL CDlgCalcDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    int nID = (int) LOWORD (wParam);

    if (m_bErrorFlag && (nID != IDC_CLX)) {
        ::MessageBeep (MB_ICONASTERISK);
        return TRUE;
    }

    if (m_bFixPending &&
        ((nID < IDC_0) || (nID > IDC_9)) &&
        (nID != IDC_CLX)) {
        ::MessageBeep (MB_ICONASTERISK);
        return TRUE;
    }
    return CDialog::OnCommand (wParam, lParam);
}

void CDlgCalcDlg::OnDigit(UINT nID) 
{
    TCHAR cDigit = (char) nID;

    if (m_bFixPending) {
        m_strFormat.SetAt (3, cDigit - IDC_0 + 0x30);
        DisplayXRegister ();
        m_bFixPending = FALSE;
        m_bStackLiftEnabled = TRUE;
        m_bNewX = TRUE;
        return;
    }

    if (m_bNewX) {
        m_bNewX = FALSE;
        if (m_bStackLiftEnabled) {
            m_bStackLiftEnabled = FALSE;
            LiftStack ();
        }
        m_bDecimalInString = FALSE;
        m_strDisplay.Empty ();
    }

    int nLength = m_strDisplay.GetLength ();
    if ((nLength == MAXCHARS) ||
        ((nLength == (MAXCHARS - 10)) && !m_bDecimalInString))
        ::MessageBeep (MB_ICONASTERISK);
    else {
        m_strDisplay += (cDigit - IDC_0 + 0x30);
        UpdateDisplay (m_strDisplay);
        m_dblStack[0] = _tcstod (m_strDisplay.GetBuffer (0), NULL);
    }
}

void CDlgCalcDlg::OnAdd() 
{
    m_dblStack[0] += m_dblStack[1];
    DisplayXRegister ();
    DropStack ();
    m_bStackLiftEnabled = TRUE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnSubtract() 
{
    m_dblStack[0] = m_dblStack[1] - m_dblStack[0];
    DisplayXRegister ();
    DropStack ();
    m_bStackLiftEnabled = TRUE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnMultiply() 
{
    m_dblStack[0] *= m_dblStack[1];
    DisplayXRegister ();
    DropStack ();
    m_bStackLiftEnabled = TRUE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnDivide() 
{
    if (m_dblStack[0] == 0.0) {
        m_bErrorFlag = TRUE;
        ::MessageBeep (MB_ICONASTERISK);
        UpdateDisplay (CString (_T ("Divide by zero")));
    }
    else {
        m_dblStack[0] = m_dblStack[1] / m_dblStack[0];
        DisplayXRegister ();
        DropStack ();
        m_bStackLiftEnabled = TRUE;
        m_bNewX = TRUE;
    }
}

void CDlgCalcDlg::OnEnter() 
{
    LiftStack ();
    DisplayXRegister ();
    m_bStackLiftEnabled = FALSE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnChangeSign() 
{
    if (m_dblStack[0] != 0.0) {
        m_dblStack[0] = -m_dblStack[0];
        if (m_strDisplay[0] == _T ('-')) {
            int nLength = m_strDisplay.GetLength ();
            m_strDisplay = m_strDisplay.Right (nLength - 1);
        }
        else
            m_strDisplay = _T ("-") + m_strDisplay;
        UpdateDisplay (m_strDisplay);
    }
}

void CDlgCalcDlg::OnExponent() 
{
    if (((m_dblStack[1] == 0.0) && (m_dblStack[0] < 0.0)) ||
        ((m_dblStack[1] == 0.0) && (m_dblStack[0] == 0.0)) ||
        ((m_dblStack[1] < 0.0) &&
        (floor (m_dblStack[0]) != m_dblStack[0]))) {
        m_bErrorFlag = TRUE;
        ::MessageBeep (MB_ICONASTERISK);
        UpdateDisplay (CString (_T ("Invalid operation")));
    }
    else {
       m_dblStack[0] = pow (m_dblStack[1], m_dblStack[0]);
       DisplayXRegister ();
       DropStack ();
       m_bStackLiftEnabled = TRUE;
       m_bNewX = TRUE;
    }
}

void CDlgCalcDlg::OnStore() 
{
    DisplayXRegister ();
    m_dblMemory = m_dblStack[0];
    m_bStackLiftEnabled = TRUE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnRecall() 
{
    LiftStack ();
    m_dblStack[0] = m_dblMemory;
    DisplayXRegister ();
    m_bStackLiftEnabled = TRUE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnFix() 
{
    m_bFixPending = TRUE;
}

void CDlgCalcDlg::OnClear() 
{
    if (m_bFixPending) {
        m_bFixPending = FALSE;
        return;
    }

    m_bErrorFlag = FALSE;
    m_dblStack[0] = 0.0;
    DisplayXRegister ();
    m_bStackLiftEnabled = FALSE;
    m_bNewX = TRUE;
}

void CDlgCalcDlg::OnDecimal() 
{
    if (m_bNewX) {
        m_bNewX = FALSE;
        if (m_bStackLiftEnabled) {
            m_bStackLiftEnabled = FALSE;
            LiftStack ();
        }
        m_bDecimalInString = FALSE;
        m_strDisplay.Empty ();
    }

    int nLength = m_strDisplay.GetLength ();
    if ((nLength == MAXCHARS) || (m_bDecimalInString))
        ::MessageBeep (MB_ICONASTERISK);
    else {
        m_bDecimalInString = TRUE;
        m_strDisplay += (char) 0x2E;
        UpdateDisplay (m_strDisplay);
        m_dblStack[0] = strtod (m_strDisplay.GetBuffer (0), NULL);
    }
}

void CDlgCalcDlg::OnDelete() 
{
    int nLength = m_strDisplay.GetLength ();

    if (!m_bNewX && (nLength != 0)) {
        if (m_strDisplay[nLength - 1] == _T ('.'))
            m_bDecimalInString = FALSE;
        m_strDisplay = m_strDisplay.Left (nLength - 1);
        UpdateDisplay (m_strDisplay);
        m_dblStack[0] = strtod (m_strDisplay.GetBuffer (0), NULL);
    }
}

void CDlgCalcDlg::LiftStack()
{
    for (int i=3; i>0; i--)
        m_dblStack[i] = m_dblStack[i-1];
}

void CDlgCalcDlg::DropStack()
{
    for (int i=1; i<3; i++)
        m_dblStack[i] = m_dblStack[i+1];
}

void CDlgCalcDlg::DisplayXRegister()
{
    double dblVal = m_dblStack[0];

    if ((dblVal >= 1000000000000.0) || (dblVal <= -1000000000000.0)) {
        UpdateDisplay (CString (_T ("Overflow error")));
        m_bErrorFlag = TRUE;
        MessageBeep (MB_ICONASTERISK);
    }
    else {
        m_strDisplay.Format (m_strFormat, dblVal);
        UpdateDisplay (m_strDisplay);
    }
}

void CDlgCalcDlg::UpdateDisplay(LPCTSTR pszDisplay)
{
    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (GetFont ());
    CSize size = dc.GetTextExtent (pszDisplay);

    CRect rect = m_rect;
    rect.InflateRect (-2, -2);
    int x = rect.right - size.cx - m_cxChar;
    int y = rect.top + ((rect.Height () - m_cyChar) / 2);

    dc.ExtTextOut (x, y, ETO_OPAQUE, rect, pszDisplay, NULL);
    dc.SelectObject (pOldFont);
}
