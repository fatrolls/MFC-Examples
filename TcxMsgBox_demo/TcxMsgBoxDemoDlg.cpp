// TcxMsgBoxDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcxMsgBoxDemo.h"
#include "TcxMsgBoxDemoDlg.h"

#include "TcxMsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBoxDemoDlg dialog

CTcxMsgBoxDemoDlg::CTcxMsgBoxDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcxMsgBoxDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcxMsgBoxDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcxMsgBoxDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcxMsgBoxDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTcxMsgBoxDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTcxMsgBoxDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAMPLE1, OnSample1)
	ON_BN_CLICKED(IDC_SAMPLE2, OnSample2)
	ON_BN_CLICKED(IDC_SAMPLE3, OnSample3)
	ON_BN_CLICKED(IDC_SAMPLE4, OnSample4)
	ON_BN_CLICKED(IDC_SAMPLE5, OnSample5)
	ON_BN_CLICKED(IDC_SAMPLE6, OnSample6)
	ON_BN_CLICKED(IDC_SAMPLE7, OnSample7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBoxDemoDlg message handlers

BOOL CTcxMsgBoxDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcxMsgBoxDemoDlg::OnPaint() 
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
HCURSOR CTcxMsgBoxDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTcxMsgBoxDemoDlg::OnSample1() 
{
   CTcxMsgBox msg( this );

      msg.SetTitle( IDS_TITLE1 );

      msg.SetMsg( IDS_MSG1 );

      msg.AddButton( IDC_OK, TRUE, TRUE );

   msg.DoModal();
}

void CTcxMsgBoxDemoDlg::OnSample2() 
{
   CTcxMsgBox msg( this );

      msg.SetTitle( IDS_TITLE2 );

      msg.SetMsg( IDS_MSG2 );
   
      msg.SetIcon( IDI_MELT );

      msg.AddButton( IDC_PLEASE, TRUE, FALSE );
      msg.AddButton( IDC_LATER, FALSE, TRUE );

   msg.DoModal();
}

void CTcxMsgBoxDemoDlg::OnSample3() 
{
   // We must use quad-backslashs (\\\\) for each backslash (\\) the message
   // will show. The problem is that the RTF uses the backslash as an identifier
   // of format, and a double backslash as a regular backslash. Since C/C++ does
   // the same, we must provide \\\\ for each final \  :)
   const TCHAR szDirName[] =
      _T("D:\\\\Users\\\\Carvalho\\\\Projects\\\\CoolThings\\\\TcxMsgBoxDemo");

   const TCHAR szFileName1[] = _T("TcxMsgBoxDemo.dsw");
   const TCHAR szFileName2[] = _T("TcxMsgBoxDemo.dsp");

	CTcxMsgBox msg( this );

      msg.SetTitle( IDS_TITLE3 );

      msg.SetRtf();
      msg.FormatMsgEx(
         MAKEINTRESOURCE(IDR_RTF_MSGS1), _T("RTF_MSGS"),
         szDirName, szFileName1, szDirName, szFileName2
         );

      msg.SetIcon( IDI_DISK );
	   
      msg.AddButton( IDC_OK, TRUE, FALSE );
      msg.AddButton( IDC_CANCEL, FALSE, TRUE );

   int i = msg.DoModal();
   TRACE( "%d\n", i );
}

void CTcxMsgBoxDemoDlg::OnSample4() 
{
	CTcxMsgBox msg( this );
      
      msg.SetTitle( IDS_TITLE3 );

      CString str;
      VERIFY( str.LoadString( IDS_MSG3 ) );

      VERIFY( msg.SetMsg( str ) );

      msg.SetIcon( IDI_NUTS );
	   
      msg.AddButton( IDC_PLAYDOOM, FALSE, FALSE );
      msg.AddButton( IDC_DRINKABEER, FALSE, FALSE );
      msg.AddButton( IDC_SURFTHEWEB, FALSE, FALSE );

   msg.DoModal();
}

void CTcxMsgBoxDemoDlg::OnSample5() 
{
	CTcxMsgBox msg( this );
   msg.SetTitle( IDS_TITLE3 );
   msg.SetRtf();
   msg.SetMsgEx( MAKEINTRESOURCE(IDR_RTF_MSGS3), _T("RTF_MSGS") );
   msg.SetIcon( IDI_NOSMOKE );
	
   msg.AddButton( IDC_OK, TRUE, FALSE );
   msg.AddButton( IDC_IGNORE, FALSE, FALSE );

   msg.DoModal();
}

void CTcxMsgBoxDemoDlg::OnSample6() 
{
   static const LPCTSTR _pMsg =
      "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\fswiss MS Sans Serif;}{\\f1\\froman\\fcharset2 Symbol;}{\\f2\\froman Times New Roman;}{\\f3\\froman Times New Roman;}{\\f4\\fswiss\\fprq2 Arial;}}"
      "{\\colortbl\\red0\\green0\\blue0;}"
      "\\deflang1046\\pard\\plain\\f4\\fs20 What about a Message Box with the following features?"
      "\\par \\pard\\li360\\fi-360{\\*\\pn\\pnlvlblt\\pnf1\\pnindent360{\\pntxtb\\'b7}}\\plain\\f4\\fs20\\b {\\pntext\\f1\\'b7\\tab}R\\plain\\f4\\fs20\\i ich \\plain\\f4\\fs20\\b T\\plain\\f4\\fs20\\i ext \\plain\\f4\\fs20\\b F\\plain\\f4\\fs20\\i ormat\\plain\\f4\\fs20  support;\\plain\\f2\\fs20 "
      "\\par \\plain\\f4\\fs20 {\\pntext\\f1\\'b7\\tab}Automatic layout calculation for best size;\\plain\\f2\\fs20 "
      "\\par \\plain\\f4\\fs20 {\\pntext\\f1\\'b7\\tab}Customizeable \\plain\\f4\\fs20\\b Buttons\\plain\\f4\\fs20 ;\\plain\\f2\\fs20 "
      "\\par \\plain\\f4\\fs20 {\\pntext\\f1\\'b7\\tab}Customizeable \\plain\\f4\\fs20\\b Icon\\plain\\f4\\fs20 ;\\plain\\f2\\fs20 "
      "\\par \\plain\\f4\\fs20 {\\pntext\\f1\\'b7\\tab}Customizeable \\plain\\f4\\fs20\\b Title\\plain\\f4\\fs20 ;\\plain\\f2\\fs20 "
      "\\par \\pard\\plain\\f4\\fs20 "
      "\\par Wouldn't that be really \\plain\\f4\\fs28\\b\\i \"cool\" \\plain\\f4\\fs20 ?\\plain\\f2\\fs20 "
      "\\par }";

	CTcxMsgBox msg( this );
   
      msg.SetTitle( IDS_TITLE3 );
      msg.SetRtf();
      msg.SetMsg( _pMsg );
      msg.SetIcon( IDI_THUMB );
	   
      msg.AddButton( IDC_YEAH, TRUE, FALSE );
      msg.AddButton( IDC_YES, FALSE, FALSE );
      msg.AddButton( IDC_MAYBE, FALSE, FALSE );

   msg.DoModal();
}

void CTcxMsgBoxDemoDlg::OnSample7() 
{
	CTcxMsgBox msg( this );

      msg.SetTitle( IDS_ABOUT_TITLE );
      msg.SetRtf();
      msg.SetMsg( IDS_ABOUT );
      msg.SetIcon( IDI_BFLAG );
	   
      msg.AddButton( IDC_OK, TRUE, FALSE );

   msg.DoModal();
}
