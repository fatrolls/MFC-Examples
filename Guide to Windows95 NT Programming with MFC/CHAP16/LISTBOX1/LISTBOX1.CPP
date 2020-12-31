///////////////////////////////////////////////////////////////////
// Module   : LISTBOX1.CPP
//
// Purpose  : Implementation of program that shows how to use 
//            multiple-select and single-select list boxes in 
//            a frame window...
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-05-96
///////////////////////////////////////////////////////////////////

#include "listbox1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
	ON_WM_ERASEBKGND()
   ON_LBN_DBLCLK(IDC_LBSINGLE, OnSListBoxDblClick)      
   ON_LBN_DBLCLK(IDC_LBMULTI, OnMListBoxDblClick)      
   ON_LBN_SELCHANGE(IDC_LBMULTI, OnMListBoxClick)      
   ON_COMMAND(IDC_BTNSEND, OnBtnSendClick)      
   ON_COMMAND(IDC_BTNCLEAR, OnBtnClearClick)      
END_MESSAGE_MAP()

//
// CMainWnd Methods
//

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{
   m_cnSelected = 0;

   // initialize the child control pointers to NULL
   m_plbSingle = 0;  
   m_plbMulti  = 0;  
   m_pbtnSend  = 0; 
   m_pbtnClear = 0; 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor (overrides default)

CMainWnd::~CMainWnd()
{
   if (m_plbSingle) delete m_plbSingle;
   if (m_plbMulti)  delete m_plbMulti;
   if (m_pbtnSend)  delete m_pbtnSend;
   if (m_pbtnClear) delete m_pbtnClear;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd() - handles WM_ERASEBKGND

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   // Call inherited method
   CWnd::OnEraseBkgnd(pDC);

   // Some quick & dirty list box labels
   pDC->SetBkMode(TRANSPARENT);
   pDC->TextOut(10, 10, _T("Multiple-Select"));
   pDC->TextOut(295, 10, _T("Single-Select"));

   // Show the number of selected items 
   CString szTemp = IntToString(m_cnSelected);
   CString szMsg  = _T("Selected: " + szTemp);

   pDC->TextOut(10, 310, szMsg);

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls()  

void CMainWnd::CreateChildControls()
{
   //
   // Allocate the child controls
   //
   m_plbSingle = new CListBox; ASSERT_VALID(m_plbSingle);
   m_plbMulti  = new CListBox; ASSERT_VALID(m_plbMulti);
   m_pbtnSend  = new CButton;  ASSERT_VALID(m_pbtnSend);
   m_pbtnClear = new CButton;  ASSERT_VALID(m_pbtnClear);

   //
   // Set the positions of the child windows
   //
   CRect rcMulti, rcSingle, rcSend, rcClear;

   rcMulti.left    = 10; 
   rcMulti.top     = 30;
   rcMulti.right   = 210; 
   rcMulti.bottom  = 300;                  

   rcSend.left     = rcMulti.right + 10;
   rcSend.top      = rcMulti.top;
   rcSend.right    = rcSend.left + 65;
   rcSend.bottom   = rcMulti.top + 25;       
   
   rcClear.left    = rcMulti.right + 10;
   rcClear.top     = rcSend.bottom + 5;   
   rcClear.right   = rcSend.left + 65;  
   rcClear.bottom  = rcClear.top + 25;                

   rcSingle.left   = rcSend.right + 10;
   rcSingle.top    = rcMulti.top;
   rcSingle.right  = rcSingle.left + rcMulti.right;
   rcSingle.bottom = rcMulti.bottom ;       
   
   //
   // initialize the list boxes with custom styles
   //
   if (!m_plbSingle->Create(LBS_SINGLE, rcSingle, 
                            this, IDC_LBSINGLE))
      { TRACE0("Failed to create single-selection list box\n"); }

   if (!m_plbMulti->Create(LBS_MULTI, rcMulti, 
                           this, IDC_LBMULTI))
      { TRACE0("Failed to create multiple-selection list box\n"); }

   // Fill the multiple-select list box with file names 
   // from the current directory
   #define DIR_READONLY (0x0001)

   if (!m_plbMulti->Dir(DIR_READONLY, (LPCTSTR)"*.*"))
     { TRACE0("Problem filling file list!\n"); }
      
   //
   // initialize the buttons
   //
   if (!m_pbtnSend->Create("Send >>", BS_COMMAND, rcSend, 
                           this, IDC_BTNSEND))
      { TRACE0("Failed to create Send button\n"); }

   if (!m_pbtnClear->Create("Clear >>", BS_COMMAND, rcClear, 
                            this, IDC_BTNCLEAR))
      { TRACE0("Failed to create Clear button\n"); }
}  

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMListBoxClick()  

void CMainWnd::OnMListBoxClick()
{
   // A buffer for the selected indices (100 max)
   int nBuffer[100];   
   
   // Find the list box elements currently selected
   m_cnSelected = m_plbMulti->GetSelItems(100, (LPINT)&nBuffer);

   Invalidate();
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMListBoxDblClick()  

void CMainWnd::OnMListBoxDblClick()
{
   OnBtnSendClick();
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSListBoxDblClick()  

void CMainWnd::OnSListBoxDblClick()
{
   // Find the list box element currently selected
   int nCurSel = m_plbSingle->GetCurSel();

   // Get the string from the selected item
   CString szSelected;
   m_plbSingle->GetText(nCurSel, szSelected);

   // Display the list box string in a message box 
   AfxMessageBox("You chose \"" + szSelected + "\"", 
                 MB_ICONINFORMATION | MB_OK);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBtnClearClick()  

void CMainWnd::OnBtnClearClick()
{
   if (m_plbSingle->GetCount())     // if count > 0
      m_plbSingle->ResetContent();  // clear all items
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBtnSendClick()  

void CMainWnd::OnBtnSendClick()
{
   // A buffer for the selected indices
   int nBuffer[100];  // 100 max
   
   // Find the list box elements currently selected
   int cSelected = m_plbMulti->GetSelItems(100, (LPINT)&nBuffer);

   // Iterate through the array of indices and add 
   // the file names to the single-select list box
      
   CString szFilename;

   for (int i = 0; i < cSelected; i++)
   {
      m_plbMulti->GetText(nBuffer[i], szFilename);
      
      // Prevent duplicate strings by searching all items in the
      // single-selection list box

      if (LB_ERR == m_plbSingle->FindString(-1, (LPCTSTR)szFilename))
         m_plbSingle->AddString(szFilename);
   }  
}

///////////////////////////////////////////////////////////////////
// CListBoxApp::InitInstance - overrides CWinApp::InitInstance

BOOL CListBoxApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Sample List Box Program"),
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   // Allocate and init the child controls
   pFrame->CreateChildControls();
   pFrame->CenterWindow();

   // Change the window class background brush and center window
   pFrame->SetClientBackColor(COLOR_BTNFACE);
   pFrame->CenterWindow();

   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();
  
   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CListBoxApp MyListBoxApp;


