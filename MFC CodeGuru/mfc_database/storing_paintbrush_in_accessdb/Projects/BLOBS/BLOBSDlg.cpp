// BLOBSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BLOBS.h"
#include "BLOBSDlg.h"
#include "RSOle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBLOBSDlg dialog

CBLOBSDlg::CBLOBSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBLOBSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBLOBSDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBLOBSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBLOBSDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBLOBSDlg, CDialog)
	//{{AFX_MSG_MAP(CBLOBSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOADIMAGE, OnLoadImage)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBLOBSDlg message handlers

BOOL CBLOBSDlg::OnInitDialog()
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

void CBLOBSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
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

void CBLOBSDlg::OnPaint() 
{
	CPaintDC dc(this);
	if (!(OleBmp.m_hObject == NULL))
	{

		CDC dcMem; 
		dcMem.CreateCompatibleDC( &dc ); //create a Memory Image
		CBitmap*  pbmpOld ;
		
		BITMAP  BmpSize ; 
		OleBmp.GetBitmap(&BmpSize); //get Image Size
		
		pbmpOld = dcMem.SelectObject(&OleBmp);

		//Draw Stretch Image 
		dc.StretchBlt( 5, 5, 150, 200, &dcMem, 0, 0, BmpSize.bmWidth, BmpSize.bmHeight, SRCCOPY);
		dcMem.SelectObject( pbmpOld );
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBLOBSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CBLOBSDlg::ReadFromBLOB(CByteArray & DBArray)
{
	CByteArray Array;
	Array.Copy( DBArray); 
	// the header of BLOB is OLE stuff like "Paint Brush Application" .... ecc..
	// the len is 78 byte ( I do not know for other headers ) 
	int HeaderLen =   78 + sizeof(BITMAPFILEHEADER); 
	Array.RemoveAt( 0, HeaderLen ); // I cut all Headers 
    
	// some BMP information  
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)Array.GetData() ;
    BITMAPINFO &bmInfo = *(LPBITMAPINFO)Array.GetData() ;
	
	
     // If bmiHeader.biClrUsed is zero we have to infer the number
     // of colors from the number of bits used to specify it.
     int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount;

     LPVOID lpDIBBits;
     if( bmInfo.bmiHeader.biBitCount > 8 )
        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
                        ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
     else
        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);


     CClientDC dc(NULL);
    
	 HBITMAP hBmp = CreateDIBitmap( dc.m_hDC,   // handle to device context 
			                    &bmiHeader,     // pointer to bitmap size and format data 
                                CBM_INIT,       // initialization flag 
                                lpDIBBits,      // pointer to initialization data 
                                &bmInfo,        // pointer to bitmap color-format data 
                                DIB_RGB_COLORS);                // color-data usage 
     
	OleBmp.Attach( hBmp );

	Array.RemoveAll(); //Relese Memory

	return TRUE;

}

void CBLOBSDlg::OnLoadImage() 
{
	
	RSOle db;
	db.Open();
	//db.MoveNext(); // if you want try to load the  next image
	ReadFromBLOB(db.m_Images);
	Invalidate();  
	
}

void CBLOBSDlg::OnAbout() 
{
CAboutDlg About;
About.DoModal();	
}
