// JPGtestDlg.cpp : implementation file
//

#include "stdafx.h"
	#include "oxbmpfle.h"
	#include "oxjpgfle.h"
	#include "oxjpgcom.h"
	#include "oxjpgdom.h"
	#include "oxjpgexp.h"
#include "utsampleabout.h"
#include "JPGtest.h"
#include "JPGtestDlg.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZE_ERROR_BUF	255
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CJPGtestDlg dialog

CJPGtestDlg::CJPGtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJPGtestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJPGtestDlg)
	m_sGraphicsFile = _T("??????.bmp");
	m_sJPEGFile = _T("??????.jpg");
	m_bGray = FALSE;
	m_bBase = FALSE;
	m_bProgr = FALSE;
	m_bOpt = FALSE;
	m_nQuality = 75;
	m_nSmooth = 0;
	m_nMaxMem = 0;
	m_nDCT = -1;
	m_nColors = 0;
	m_nMaxMem2 = 0;
	m_bOnePass = FALSE;
	m_bGrayScale2 = FALSE;
	m_bFast = FALSE;
	m_bNoSmooth = FALSE;
	m_bOS2 = FALSE;
	m_nDither = -1;
	m_nScale = -1;
	m_nDCT2 = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJPGtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJPGtestDlg)
	DDX_Control(pDX, IDC_TIME, m_Time_Static);
	DDX_Text(pDX, IDC_EDIT1, m_sGraphicsFile);
	DDX_Text(pDX, IDC_EDIT2, m_sJPEGFile);
	DDX_Check(pDX, IDC_CHECK1, m_bGray);
	DDX_Check(pDX, IDC_CHECK2, m_bBase);
	DDX_Check(pDX, IDC_CHECK3, m_bProgr);
	DDX_Check(pDX, IDC_CHECK4, m_bOpt);
	DDX_Text(pDX, IDC_EDIT3, m_nQuality);
	DDX_Text(pDX, IDC_EDIT4, m_nSmooth);
	DDX_Text(pDX, IDC_EDIT5, m_nMaxMem);
	DDX_Radio(pDX, IDC_RADIO1, m_nDCT);
	DDX_Text(pDX, IDC_COLORS_EDIT, m_nColors);
	DDX_Text(pDX, IDC_MAXMEM_EDIT, m_nMaxMem2);
	DDX_Check(pDX, IDC_ONEPASS_CHECK, m_bOnePass);
	DDX_Check(pDX, IDC_CHECK6, m_bGrayScale2);
	DDX_Check(pDX, IDC_FAST_CHECK, m_bFast);
	DDX_Check(pDX, IDC_NOSMOOTH_CHECK, m_bNoSmooth);
	DDX_Check(pDX, IDC_CHECK5, m_bOS2);
	DDX_Radio(pDX, IDC_FS_RADIO, m_nDither);
	DDX_Radio(pDX, IDC_ONEONE_RADIO, m_nScale);
	DDX_Radio(pDX, IDC_DINT_RADIO, m_nDCT2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJPGtestDlg, CDialog)
	//{{AFX_MSG_MAP(CJPGtestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GRAPH_BUTTON, OnGraphButton)
	ON_BN_CLICKED(IDC_JPG_BUTTON, OnJpgButton)
	ON_BN_CLICKED(IDC_Compress, OnCompress)
	ON_BN_CLICKED(IDC_UnCompress, OnUnCompress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJPGtestDlg message handlers

BOOL CJPGtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJPGtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg  dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJPGtestDlg::OnPaint() 
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
HCURSOR CJPGtestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJPGtestDlg::OnGraphButton() 
{
	char szFilter[] = "Bitmap Files (*.bmp) | *.bmp ||";
  
	CFileDialog FileDialog(TRUE, "bmp", "*.bmp", OFN_HIDEREADONLY, szFilter, this);
	if (FileDialog.DoModal() == IDOK)
		{
		m_sGraphicsFile = FileDialog.GetPathName();
		UpdateData(FALSE);
		}	
}

void CJPGtestDlg::OnJpgButton() 
{
	char szFilter[] = "JPEG Files (*.jpg) | *.jpg ||";
  
	CFileDialog FileDialog(TRUE, "jpg", "*.jpg", OFN_HIDEREADONLY, szFilter, this);
	if (FileDialog.DoModal() == IDOK)
		{
		m_sJPEGFile = FileDialog.GetPathName();
		UpdateData(FALSE);
		}	
}

void CJPGtestDlg::OnCompress() 
{
	if (!UpdateData(TRUE))
		return;
	
	BeginWaitCursor();

	COXBMPFile BMPFile(m_sGraphicsFile);	
	COXJPEGFile JPGFile(m_sJPEGFile);	

	COXJPEGCompressor JCompr;

	JCompr.SetGrayScale(m_bGray);
	JCompr.SetBaseLine(m_bBase);
	JCompr.SetProgressive(m_bProgr);
	JCompr.SetOptimize(m_bOpt);
	JCompr.SetQuality(m_nQuality);
	if (m_nSmooth != 0)
		JCompr.SetSmooth(m_nSmooth);
	JCompr.SetMaxMemory(m_nMaxMem);
	if (m_nDCT != -1)
		JCompr.SetDisCosTranf((EDiscreteCosTransf)(m_nDCT + 1));

	DWORD nBeginTicks, nEndTicks;
	nBeginTicks = GetTickCount();
	short nReturn(0);
	TCHAR ErrorBuffer[SIZE_ERROR_BUF];

	TRY
		{
		nReturn = JCompr.DoCompress(&BMPFile, &JPGFile);
		if (nReturn == 2)
			AfxMessageBox(JCompr.GetWarningMessages());
		}
	CATCH(COXJPEGException, e)
		{
		e->GetErrorMessage(ErrorBuffer, SIZE_ERROR_BUF);
		AfxMessageBox(CString("Exception : ") + ErrorBuffer);

		TRACE((LPCTSTR)ErrorBuffer);
		}
	END_CATCH

	nEndTicks = GetTickCount();

	char buffer[20];
	UTBStr::sprintf(buffer, 20, "%f", (nEndTicks - nBeginTicks)/1000.0);
	m_Time_Static.SetWindowText(buffer);
	
	EndWaitCursor();	
}

void CJPGtestDlg::OnUnCompress() 
{
	if (!UpdateData(TRUE))
		return;
	
	BeginWaitCursor();

	COXBMPFile BMPFile(m_sGraphicsFile);
	BMPFile.SetOS2Format(m_bOS2);

	COXJPEGFile JPGFile(m_sJPEGFile);	

	COXJPEGDecompressor JDecompr;

	JDecompr.SetGrayScale(m_bGrayScale2);
	JDecompr.SetFast(m_bFast);
	JDecompr.SetNoSmooth(m_bNoSmooth);
	JDecompr.SetOnePass(m_bOnePass);
	JDecompr.SetMaxMemory(m_nMaxMem2);

	if (m_nDCT2 != -1)
		JDecompr.SetDisCosTranf((EDiscreteCosTransf)(m_nDCT2 + 1));
	if (m_nDither != -1)
		JDecompr.SetDitherMethod((EDitherMethod)(m_nDither + 1));
	if (m_nScale != -1)
		JDecompr.SetScale((EDecompScale)(m_nScale + 1));

	if (m_nColors != 0)
		JDecompr.SetColors(m_nColors);

	DWORD nBeginTicks, nEndTicks;
	nBeginTicks = GetTickCount();
	short nReturn(0);
	TCHAR ErrorBuffer[SIZE_ERROR_BUF];

	TRY
		{
		nReturn = JDecompr.DoDecompress(&JPGFile, &BMPFile);
		if (nReturn == 2)
			AfxMessageBox(JDecompr.GetWarningMessages());
		}
	CATCH(COXJPEGException, e)
		{
		e->GetErrorMessage(ErrorBuffer, SIZE_ERROR_BUF);
		AfxMessageBox(CString("Exception : ") + ErrorBuffer);
		TRACE((LPCTSTR)ErrorBuffer);
		}
	END_CATCH

	nEndTicks = GetTickCount();

	char buffer[20];
	UTBStr::sprintf(buffer, 20, "%f", (nEndTicks - nBeginTicks)/1000.0);
	m_Time_Static.SetWindowText(buffer);
	
	EndWaitCursor();	
}
