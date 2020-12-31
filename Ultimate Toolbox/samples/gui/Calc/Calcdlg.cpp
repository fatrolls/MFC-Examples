// calcdlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "calc.h"
#include "calcdlg.h"
#include "calckey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalculator dialog

CCalculator::CCalculator(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculator::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculator)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Note that LoadAccelerator does not require DestroyAcceleratorTable
	m_hAccel = LoadAccelerators(AfxGetResourceHandle(),MAKEINTRESOURCE(IDD));

	// Initialize the move variable
	m_bTrackMove = FALSE;
}

void CCalculator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculator)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCalculator Internal Methods

// Called to perform an operation - add, subtract, etc.
void CCalculator::PerformOperation()
{
	// Return if in an invalid state
	if (m_errorState != ErrNone)
		return;

	// If we can perform an operation...
	if (m_bOperandAvail)
	{
		// Perform the selected operation
		if (m_operator == OpNone)
			m_accum = m_operand;
		else if (m_operator == OpMultiply)
			m_accum *= m_operand;
		else if (m_operator == OpDivide)
		{
			if (m_operand == 0)
				m_errorState = ErrDivideByZero;
			else
				m_accum /= m_operand;
		}
		else if (m_operator == OpAdd)
			m_accum += m_operand;
		else if (m_operator == OpSubtract)
			m_accum -= m_operand;
	}

	// Set the next state
	m_bOperandAvail = FALSE;
	UpdateDisplay();
}

// Called to update the total display
void CCalculator::UpdateDisplay()
{
	// Display "Error" is an error occurs, otherwise display the total
	CString str;
	if (m_errorState != ErrNone)
		str = "Error";
	else
	{
		long lVal = (m_bOperandAvail) ? m_operand : m_accum;
		str.Format(_T("%ld"), lVal);
	}

	GetDlgItem(IDC_DISPLAY)->SetWindowText(str);
}

// Draws a tracking rectangle by inverting an area the size of the dialog
void CCalculator::InvertTracker(CPoint point)
{
	CRect rectFrame;
	GetWindowRect(&rectFrame);
	CDC dc;
	dc.Attach(::GetDC(NULL));

	// Create the frame with a reverse video effect
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y, rectFrame.Width(),
			2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x+rectFrame.Width(), point.y-m_ptMouse.y,
			2, rectFrame.Height(), PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+rectFrame.Height(),
			rectFrame.Width()+2, 2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+2, 2,
			rectFrame.Height()-2, PATINVERT);
	::ReleaseDC(NULL,dc.Detach());
}


BEGIN_MESSAGE_MAP(CCalculator, CDialog)
	//{{AFX_MSG_MAP(CCalculator)
	ON_COMMAND_RANGE(IDC_0,IDC_9,OnNumber)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_DIV, OnDiv)
	ON_BN_CLICKED(IDC_EQUAL, OnEqual)
	ON_BN_CLICKED(IDC_MUL, OnMul)
	ON_BN_CLICKED(IDC_SUB, OnSub)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculator message handlers

BOOL CCalculator::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString sCaption;
	sCaption.LoadString(IDR_MAINFRAME);
	SetWindowText(sCaption);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Set the rounded-corner calculator shape
	CPoint point(30,30);
	SetRoundRectShape(NULL,&point);

	// Make sure the starfield paints before everything else
	GetDlgItem(IDC_STARFIELD)->SetWindowPos(&wndTop,0,0,0,0,
						SWP_NOMOVE|SWP_NOSIZE);

	// Shape the number keys
	CCalcKey* pKey;
	int nID;

	for(nID = IDC_0; nID <= IDC_9; nID++)
	{
		pKey = (CCalcKey*) GetDlgItem(nID);
		ASSERT(pKey != NULL);

		// Make them star shaped
		pKey->SetStarShape();

		// Set color to yellow when not pressed, red when pressed
		pKey->SetColors(RGB(0,0,0),RGB(255,255,0),RGB(0,0,0),RGB(255,0,0));
	}

	// Shape the operation keys 
	for(nID = IDC_SUB; nID <= IDC_ADD; nID++)
	{
		pKey = (CCalcKey*) GetDlgItem(nID);
		ASSERT(pKey != NULL);
	
		// Make them round-corned rectangles
		CPoint point(20,20);
		pKey->SetRoundRectShape(NULL,&point);

		// Set color to light gray when not pressed, white when pressed
		pKey->SetColors(RGB(0,0,0),RGB(192,192,192),
										RGB(0,0,0),RGB(255,255,255));
	}

	// Set the total display's appearance
	pKey = (CCalcKey*) GetDlgItem(IDC_DISPLAY);
	ASSERT(pKey != NULL);

	// Make it a white ellipse
	pKey->SetEllipseShape(NULL);
	pKey->SetColors(RGB(0,0,0),RGB(255,255,255));

	// Set the close button's appearance
	pKey = (CCalcKey*) GetDlgItem(IDCANCEL);
	ASSERT(pKey != NULL);

	// Make it a light gray ellipse
	pKey->SetEllipseShape(NULL);
	pKey->SetColors(RGB(0,0,0),RGB(192,192,192));

		// Set the close button's appearance
	pKey = (CCalcKey*) GetDlgItem(IDC_ABOUT);
	ASSERT(pKey != NULL);

	// Make it a light gray ellipse
	pKey->SetEllipseShape(NULL);
	// Set color to light gray when not pressed, white when pressed
	pKey->SetColors(RGB(0,0,0),RGB(192,192,192),
										RGB(0,0,0),RGB(255,255,255));
	// Center the dialog on the screen
	CenterWindow();

	// Initialize the calculator's work variables
	OnClear();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Called when a number button is clicked
void CCalculator::ClickedNumber(long l)
{
	// Return if in an invalid state
	if (m_errorState != ErrNone)
		return;

	// If we can perform an operation...
	if (!m_bOperandAvail)
		m_operand = 0L;

	// Set the next state
	SetOperand(m_operand*10+l);
	UpdateDisplay();
}
void CCalculator::OnAbout(){
	CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	aboutDlg.DoModal();
}

// Called when the left mouse button is pressed
void CCalculator::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	// Save the starting point where the mouse was clicked
	m_ptMouse = point;

	// Save the point in screen coordinates too
	ClientToScreen(&point);
	m_ptLast = point;
}

// Called when the left mouse button is released
void CCalculator::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	// If moving...
	if (m_bTrackMove)
	{
		// Reset for next move
		m_bTrackMove = FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);

		// Calculate how far we have moved and update
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
	}
}

// Called when the mouse moves
void CCalculator::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Are we not moving the window and the left mouse button is now down???
	if(!m_bTrackMove && (nFlags & MK_LBUTTON))
	{
		// Begin the move operation
		m_bTrackMove = TRUE;
		SetCapture();
		InvertTracker(m_ptLast);
	}
	
	// If we moving...
	if (m_bTrackMove)
	{
		// Remove the old tracking rectangle
		ClientToScreen(&point);
		InvertTracker(m_ptLast);

		// Draw a new one
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else CWnd::OnMouseMove(nFlags,point);
}

// Called when a number key is pressed
void CCalculator::OnNumber(UINT nID) 
{
	ASSERT(nID >= IDC_0 && nID <= IDC_9);
	ClickedNumber(nID-IDC_0);
}

// Called when the clear key is pressed
void CCalculator::OnClear() 
{
	// Reset the internal state, empty the totals
	m_operator = OpNone;
	m_operand = 0L;
	m_accum = 0L;
	m_bOperandAvail = FALSE;
	m_errorState = ErrNone;
	UpdateDisplay();
}

// Called when the divide key is pressed
void CCalculator::OnDiv() 
{
	// Perform the division and save the operation
	PerformOperation();
	m_operator = OpDivide;
}

// Called when the equal key is pressed
void CCalculator::OnEqual() 
{
	// Get the total and save the operation
	PerformOperation();
	m_operator = OpNone;
}

// Called when the subtract key is pressed
void CCalculator::OnSub() 
{
	// Perform the subtraction and save the operation
	PerformOperation();
	m_operator = OpSubtract;
}

// Called when the add key is pressed
void CCalculator::OnAdd() 
{
	// Perform the addition and save the operation
	PerformOperation();
	m_operator = OpAdd;
}

// Called when the multiply key is pressed
void CCalculator::OnMul() 
{
	// Perform the multiplication and save the operation
	PerformOperation();
	m_operator = OpMultiply;
}

// Saves the last operand value
void CCalculator::SetOperand(long nNewValue) 
{
	// Save the operand value and indicate that operation was performed
	m_operand = nNewValue;
	m_bOperandAvail = TRUE;
}

// Translate the accelerators for the button keys
BOOL CCalculator::PreTranslateMessage(MSG* pMsg) 
{
	if (m_hAccel != NULL && TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}
