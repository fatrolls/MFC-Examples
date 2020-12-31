// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "VtxButton.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_BUTTON9, m_cButton9);
	DDX_Control(pDX, IDC_BUTTON8, m_cButton8);
	DDX_Control(pDX, IDC_BUTTON7, m_cButton7);
	DDX_Control(pDX, IDC_BUTTON6, m_cButton6);
	DDX_Control(pDX, IDC_BUTTON5, m_cButton5);
	DDX_Control(pDX, IDC_BUTTON12, m_cButton12);
	DDX_Control(pDX, IDC_BUTTON11, m_cButton11);
	DDX_Control(pDX, IDC_BUTTON10, m_cButton10);
	DDX_Control(pDX, IDC_BUTTON4, m_cButton4);
	DDX_Control(pDX, IDC_BUTTON3, m_cButton3);
	DDX_Control(pDX, IDC_BUTTON2, m_cButton2);
	DDX_Control(pDX, IDC_BUTTON1, m_cButton1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CRect rect;
	m_cButton1.GetClientRect(&rect);            // Get the button's original dimensions
	CVtxPolygons vtxPolygons;
	int offset[4] = {0, 1, 2, 4};
	for (int i = 0; i < 4; i++)                 // Iterate through each of the polygons
	{
		// Add the corners
		vtxPolygons.Add(i, CVertex(rect.left + offset[i], rect.top + offset[i]));
		vtxPolygons.Add(i, CVertex(rect.right - offset[i] - 1, rect.top + offset[i]));
		vtxPolygons.Add(i, CVertex(rect.right - offset[i] - 1, rect.bottom - offset[i] - 1));
		vtxPolygons.Add(i, CVertex(rect.left + offset[i], rect.bottom - offset[i] - 1));
	}
	vtxPolygons.ClosePolygons();                // Close the polygons off
	m_cButton1.SetVtxPolygons(&vtxPolygons);    // Set the button's polygons

	m_cButton2.SetVtx(VTX_DIAMOND);
	m_cButton3.SetVtx(VTX_CIRCLE);
	m_cButton4.SetVtx(VTX_STRETCHEDCIRCLE);

	m_cButton5.SetVtx(VTX_RECT);
	m_cButton6.SetVtx(VTX_DIAMOND);
	m_cButton7.SetVtx(VTX_CIRCLE);
	m_cButton8.SetVtx(VTX_STRETCHEDCIRCLE);

	m_cButton9.SetVtx(VTX_RECT);
	m_cButton10.SetVtx(VTX_DIAMOND);
	m_cButton11.SetVtx(VTX_CIRCLE);
	m_cButton12.SetVtx(VTX_STRETCHEDCIRCLE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
