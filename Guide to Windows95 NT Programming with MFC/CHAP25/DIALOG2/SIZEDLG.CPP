///////////////////////////////////////////////////////////////////
//  Module   : SIZEDLG.CPP
//
//  Purpose  : Implementation of a custom dialog class.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-22-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "dialog2.h"
#include "sizedlg.h"

// CWndSizeDlg message map
BEGIN_MESSAGE_MAP(CWndSizeDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_320, OnRadioSizeClick)
	ON_BN_CLICKED(IDC_RADIO_640, OnRadioSizeClick)
	ON_BN_CLICKED(IDC_RADIO_800, OnRadioSizeClick)
	ON_BN_CLICKED(IDC_RADIO_1024, OnRadioSizeClick)
	ON_BN_CLICKED(IDC_RADIO_DESKTOP, OnRadioSizeClick)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioSizeClick)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::CWndSizeDlg()

CWndSizeDlg::CWndSizeDlg(CWnd* pParent)
	: CDialog(CWndSizeDlg::IDD, pParent)
{
   // Get the display size
   m_uWidth  = ::GetSystemMetrics(SM_CXSCREEN);
	m_uHeight = ::GetSystemMetrics(SM_CYSCREEN);
}

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::DoDataExchange()

void CWndSizeDlg::DoDataExchange(CDataExchange* pDX)
{
   // Get the display size
   UINT cx = ::GetSystemMetrics(SM_CXSCREEN);;
	UINT cy = ::GetSystemMetrics(SM_CYSCREEN);
   
   // Call the inherited handler
   CDialog::DoDataExchange(pDX);

	// Data map
   DDX_Text(pDX, IDC_EDIT_WIDTH, m_uWidth);
   DDV_MinMaxUInt(pDX, m_uWidth, 0, cx);

	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_uHeight);
	DDV_MinMaxUInt(pDX, m_uHeight, 0, cy);
}     

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::ResizeParent()

void CWndSizeDlg::ResizeParent(UINT uWidth, UINT uHeight)
{
   // Get a pointer to the parent window
   CWnd* pWnd = this->GetParent();

   // Resize the window
   if (pWnd != NULL)
      pWnd->SetWindowPos(0, 0, 0, uWidth, uHeight, 
         SWP_NOMOVE | SWP_NOZORDER);

   // Center the window
   if (pWnd->IsKindOf(RUNTIME_CLASS(CMainWnd)))
      pWnd->CenterWindow();
}

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::SetNewSize()

void CWndSizeDlg::SetNewSize(UINT uWidth, UINT uHeight)
{
   m_uWidth  = uWidth;
   m_uHeight = uHeight;
}

///////////////////////////////////////////////////////////////////
// CWndSizeDlg message handlers
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::OnInitDialog() 

BOOL CWndSizeDlg::OnInitDialog() 
{
	// call inherited method
   CDialog::OnInitDialog();
   
   // Disable the edit and static label controls
   editWidth().EnableWindow(FALSE);
   editHeight().EnableWindow(FALSE);
   
   statWidth().EnableWindow(FALSE);
   statHeight().EnableWindow(FALSE);

   // get the width of the screen in pixels
	UINT cx = ::GetSystemMetrics(SM_CXSCREEN);
   
   // Disable the higher resolutions if not available
   btn800().EnableWindow((cx >= 800));
   btn1024().EnableWindow((cx >= 1024));
      
   return TRUE;  
}

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::OnRadioSizeClick()

void CWndSizeDlg::OnRadioSizeClick() 
{
   // Enable or disable the "custom size" controls
   BOOL bEnabled = (btnCustom().GetCheck() == 1);

   editWidth().EnableWindow(bEnabled);
   editHeight().EnableWindow(bEnabled);
   
   statWidth().EnableWindow(bEnabled);
   statHeight().EnableWindow(bEnabled);

   // Set the window size
   if (btn320().GetCheck() == 1)
      SetNewSize(320, 240);

   else if (btn640().GetCheck() == 1)
      SetNewSize(640, 480);
   
   else if (btn800().GetCheck() == 1)
      SetNewSize(800, 600);
   
   else if (btn1024().GetCheck() == 1)
      SetNewSize(1024, 768);

   else if (btnDesktop().GetCheck() == 1)
   {
      CWnd* pWnd = GetDesktopWindow();
      CRect rc;
      pWnd->GetClientRect(&rc);
      SetNewSize(rc.Width(), rc.Height());
   }

   else if (btnCustom().GetCheck() == 1)
      SetNewSize(m_uWidth, m_uHeight);
 }

///////////////////////////////////////////////////////////////////
// CWndSizeDlg::OnOK()

void CWndSizeDlg::OnOK() 
{
   if (btnCustom().GetCheck() == 1) 
   {
      if (UpdateData(TRUE))
      {
         // Resize the parent window
         ResizeParent(m_uWidth, m_uHeight); 
      }
   }
   else
   {
      // Resize the parent window
      ResizeParent(m_uWidth, m_uHeight);
         
      // Call the inherited method second 
      CDialog::OnOK();
   }
}

///////////////////////////////////////////////////////////////////
