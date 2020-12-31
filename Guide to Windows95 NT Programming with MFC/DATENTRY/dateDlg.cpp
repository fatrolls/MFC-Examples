// datentryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dtime.h"
#include "resource.h"
#include "dateDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDatentryDlg::CDatentryDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CDatentryDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDatentryDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  m_CDate = CDate::CurrentDate();
  m_CLTimeSpan = CLTimeSpan(1, 2, 3, 4, 5);
  m_CLTimeOfDay = CLTimeOfDay(1, 2, 3, 4);
  m_CLDate = CLDate::CurrentTime(LOCAL);
}

void CDatentryDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDatentryDlg)
  //}}AFX_DATA_MAP

  //connect to the controls, using a selection of flags for 
  //demonstration purposes, you can change the flags to suit the way you
  //prefer to display the dialogs
  DDX_CDateControl(pDX, IDC_CDATE, m_ctrlCDate, DT_NODRAG | DT_MODAL);
  DDX_CLTimeSpanControl(pDX, IDC_CLTIMESPAN, m_ctrlCLTimeSpan, DT_MODAL);
  DDX_CLTimeOfDayControl(pDX, IDC_CLTIMEOFDAY, m_ctrlCLTimeOfDay, DT_ONLYVALID | DT_PUSHPIN | DT_MODELESS);
  DDX_CLDateControl(pDX, IDC_CLDATE, m_ctrlCLDate, DT_MODELESS);

  //retreive / set the actual values 
  DDX_CDate(pDX, m_ctrlCDate, m_CDate);
  DDX_CLTimeSpan(pDX, m_ctrlCLTimeSpan, m_CLTimeSpan);
  DDX_CLTimeOfDay(pDX, m_ctrlCLTimeOfDay, m_CLTimeOfDay);
  DDX_CLDate(pDX, m_ctrlCLDate, m_CLDate);
}

BEGIN_MESSAGE_MAP(CDatentryDlg, CDialog)
  //{{AFX_MSG_MAP(CDatentryDlg)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  //}}AFX_MSG_MAP
  #ifndef _WIN32
  ON_COMMAND(DTIME_EDIT_CONTROL_ID, OnEditButton)
  #endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatentryDlg message handlers

BOOL CDatentryDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  #ifdef _WIN32
    SetIcon(m_hIcon, TRUE);     // Set big icon
    SetIcon(m_hIcon, FALSE);    // Set small icon
  #endif
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDatentryDlg::OnPaint() 
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
HCURSOR CDatentryDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

#ifndef _WIN32
void CDatentryDlg::OnEditButton()
{                       
  //reflect the message back down to the window which sent it to us
  const MSG* pMsg = GetCurrentMessage( ); 
  HWND hButton = (HWND) LOWORD(pMsg->lParam);
  ::SendMessage(hButton, UWM_BN_CLICKED, 0, 0L);
}
#endif
