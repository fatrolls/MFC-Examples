///////////////////////////////////////////////////////////////////
// Module   : EDIT1.CPP
//
// Purpose  : Implementation of program that shows how to use a
//            multiple-line edit control in a frame window...
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-10-96
///////////////////////////////////////////////////////////////////

#include "edit1.h"

// Message map for CKeyEdit
BEGIN_MESSAGE_MAP(CKeyEdit, CEdit)
   ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_SIZE()
   ON_EN_UPDATE(IDC_ECMULTI, OnEditUpdate)      
   ON_EN_VSCROLL(IDC_ECMULTI, OnEditVScroll)
   ON_COMMAND(IDC_BTNCUT, OnBtnCutClick)      
   ON_COMMAND(IDC_BTNCOPY, OnBtnCopyClick)      
   ON_COMMAND(IDC_BTNPASTE, OnBtnPasteClick)      
   ON_COMMAND(IDC_BTNUNDO, OnBtnUndoClick)      
END_MESSAGE_MAP()

//
// CKeyEdit Method
//

///////////////////////////////////////////////////////////////////
// CKeyEdit::OnKeyDown

void CKeyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   // get a pointer to CMainWnd
   CMainWnd* pMainWnd = (CMainWnd*)AfxGetMainWnd();

   // Update the text info
   pMainWnd->UpdateTextInfo();

	// call inherited method
   CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////
// CKeyEdit::OnLButtonUp

void CKeyEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
   // get a pointer to CMainWnd
   CMainWnd* pMainWnd = (CMainWnd*)AfxGetMainWnd();

   // Update the text info
   pMainWnd->UpdateTextInfo();

	// call inherited method
	CEdit::OnLButtonDown(nFlags, point);
}

//
// CMainWnd Methods
//

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{
   m_bInitialized = FALSE;

   // Initialize the child control pointers to NULL...
   m_pEdit      = 0;
   m_pStatic    = 0;
   m_pbtnCut    = 0;
   m_pbtnCopy   = 0;
   m_pbtnPaste  = 0;
   m_pbtnUndo   = 0;
}  
                
///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor (overrides default)

CMainWnd::~CMainWnd()
{
   if (m_pEdit)      delete m_pEdit;
   if (m_pStatic)    delete m_pStatic;
   if (m_pbtnCut)    delete m_pbtnCut;
   if (m_pbtnCopy)   delete m_pbtnCopy;
   if (m_pbtnPaste)  delete m_pbtnPaste;
   if (m_pbtnUndo)   delete m_pbtnUndo;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() 

void CMainWnd::CreateChildControls()
{
   // Set the init flag
   if (!m_bInitialized) 
      m_bInitialized = TRUE;
      
   // Allocate the child controls
   m_pEdit     = new CKeyEdit; ASSERT_VALID(m_pEdit);   
   m_pStatic   = new CEdit;    ASSERT_VALID(m_pStatic);   
   m_pbtnCut   = new CButton;  ASSERT_VALID(m_pbtnCut);
   m_pbtnCopy  = new CButton;  ASSERT_VALID(m_pbtnCopy);
   m_pbtnPaste = new CButton;  ASSERT_VALID(m_pbtnPaste);
   m_pbtnUndo  = new CButton;  ASSERT_VALID(m_pbtnUndo);
   
   // Create a dummy rect, actual control placement/sizing 
   // occurs in PositionChildControls()
   CRect rc(0, 10, 0, 10);
   
   // initialize the child controls
   if (!m_pEdit->Create(ES_MULTI, rc, this, IDC_ECMULTI))
      { TRACE0("Failed to create multiple-line edit control\n"); }

   if (!m_pStatic->Create(ES_STATIC, rc, this, IDC_ECSTATIC))
      { TRACE0("Failed to create static-edit control\n"); }

   // initialize the buttons
   if (!m_pbtnCut->Create("Cut", BS_COMMAND, rc, this, IDC_BTNCUT))
      { TRACE0("Failed to create Cut button\n"); }

   if (!m_pbtnCopy->Create("Copy", BS_COMMAND, rc, this, IDC_BTNCOPY))
      { TRACE0("Failed to create Copy button\n"); }

   if (!m_pbtnPaste->Create("Paste", BS_COMMAND, rc, this, IDC_BTNPASTE))
      { TRACE0("Failed to create Paste button\n"); }

   if (!m_pbtnUndo->Create("Undo", BS_COMMAND, rc, this, IDC_BTNUNDO))
      { TRACE0("Failed to create Undo button\n"); }

   PositionChildControls();

   // Set tab stops and give the edit control the focus
   m_pStatic->SetTabStops(::GetDialogBaseUnits() * 5);
   m_pEdit->SetFocus;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::PositionChildControls()

void CMainWnd::PositionChildControls()
{
   //
   // Set the positions of the child windows
   //
   RECT rcClient, rcEdit;
   GetClientRect(&rcClient);

   rcEdit.left = 5; 
   rcEdit.top  = 5;

   if (rcClient.right > 70)
      rcEdit.right = rcClient.right - 70;
       
   if (rcClient.bottom > 60)
      rcEdit.bottom = rcClient.bottom - 60;                  

   // Update the positions of the child windows
   m_pEdit->MoveWindow(&rcEdit);
   m_pStatic->MoveWindow(rcEdit.left, rcEdit.bottom + 5, 
                         rcEdit.right - 5, rcClient.bottom - 10);

   m_pbtnCut->MoveWindow(rcEdit.right + 5, rcEdit.top,  60, 25);
   m_pbtnCopy->MoveWindow(rcEdit.right + 5, rcEdit.top + 30, 60, 25);
   m_pbtnPaste->MoveWindow(rcEdit.right + 5, rcEdit.top + 60, 60, 25);
   m_pbtnUndo->MoveWindow(rcEdit.right + 5, rcEdit.top + 90, 60, 25);
  
   UpdateTextInfo();
}       
   
///////////////////////////////////////////////////////////////////
// CMainWnd::UpdateTextInfo()

void CMainWnd::UpdateTextInfo()
{
   CString szAllText;
   m_pEdit->GetWindowText(szAllText);

   // Use edit methods to get some info
   int nChars     = szAllText.GetLength();
   int nLineCount = m_pEdit->GetLineCount();
   int nCurLine   = m_pEdit->LineFromChar() + 1;
   int nFirstVis  = m_pEdit->GetFirstVisibleLine() + 1;

   // Convert the info to strings w/inherited IntToString() method
   CString szLineCount, szCurLine, szFirstVis, szChars;              
   
   szLineCount = IntToString(nLineCount);
   szCurLine   = IntToString(nCurLine);
   szFirstVis  = IntToString(nFirstVis);
   szChars     = IntToString(nChars);            

   // Update the current text info
   CString szHeader;
   szHeader = "LineCount:\tCurLine:\tVisLine:\tCharCount:";
   
   CString szInfo = szHeader    + "\r\n" + 
                    szLineCount + "\t" + 
                    szCurLine   + "\t" + 
                    szFirstVis  + "\t" + 
                    szChars;  

   m_pStatic->SetWindowText(_T(szInfo));
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize()

void CMainWnd::OnSize(UINT nType, int cx, int cy) 
{
   CFrameWnd::OnSize(nType, cx, cy);
      
   if (m_bInitialized)
      PositionChildControls();
}

//
// CEditApp Methods
//

///////////////////////////////////////////////////////////////////
// CEditApp::InitInstance 

BOOL CEditApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window                                      
   pFrame->Create(0, _T("Simple Text Editor"),
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   AfxGetApp()->m_pMainWnd = pFrame;
  
   // Create the child controls for the frame window
   pFrame->CreateChildControls();
   pFrame->SetClientBackColor(COLOR_BTNFACE);

   // Show the frame window
   pFrame->ShowWindow(SW_SHOWMAXIMIZED);
   pFrame->UpdateWindow();

   return TRUE;
}
                
///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CEditApp MyEditApp;

///////////////////////////////////////////////////////////////////
