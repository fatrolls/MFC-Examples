///////////////////////////////////////////////////////////////////
// Module  : EDIT1.H
//
// Purpose : Header for CEditApp.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//       
// Date    : 03-10-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define two custom edit control styles
#define ES_MULTI (ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | \
                  WS_CHILD | ES_LEFT | WS_BORDER )

#define ES_STATIC (ES_MULTILINE | ES_LEFT | ES_READONLY | \
                   WS_VISIBLE | WS_CHILD)

// Button style
#define BS_COMMAND (BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD )

// Control IDs 
#define IDC_ECMULTI      100   // multi-line edit control
#define IDC_ECSTATIC     101   // multi-line static-edit control
#define IDC_BTNCUT       102   // cut button
#define IDC_BTNCOPY      103   // copy button
#define IDC_BTNPASTE     104   // paste button
#define IDC_BTNUNDO      105   // undo button

///////////////////////////////////////////////////////////////////
// Class   : CKeyEdit
//
// Purpose : A custom edit control that traps WM_KEYDOWN messages

class CKeyEdit : public CEdit
{
protected:
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
   
   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// Class   : CMainWnd
//
// Purpose : A custom frame window class derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   BOOL     m_bInitialized;   // initialization flag

   // Child window controls 
   CKeyEdit* m_pEdit;         // multi-line edit
   CEdit*    m_pStatic;       // multi-line static-edit
   CButton*  m_pbtnCut;       // cut button
   CButton*  m_pbtnCopy;      // copy button
   CButton*  m_pbtnPaste;     // paste button
   CButton*  m_pbtnUndo;      // undo button

   // General methods
   void PositionChildControls();

   // Message Handlers
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnEditUpdate();
   afx_msg void OnEditVScroll();
   afx_msg void OnBtnCutClick();  
   afx_msg void OnBtnCopyClick();    
   afx_msg void OnBtnPasteClick();   
   afx_msg void OnBtnUndoClick();   

public:
   CMainWnd();
   ~CMainWnd();
   virtual void CreateChildControls(); 
   void UpdateTextInfo();

   DECLARE_MESSAGE_MAP();
};

//
// Inline methods
//
inline void CMainWnd::OnBtnCutClick()
   { m_pEdit->Cut(); }

inline void CMainWnd::OnBtnCopyClick()
   { m_pEdit->Copy(); }

inline void CMainWnd::OnBtnPasteClick()
   { m_pEdit->Paste(); }

inline void CMainWnd::OnBtnUndoClick()
   { m_pEdit->Undo(); }

inline void CMainWnd::OnEditUpdate()
   { UpdateTextInfo(); }

inline void CMainWnd::OnEditVScroll()
   { UpdateTextInfo(); }


///////////////////////////////////////////////////////////////////
// Class   : CEditApp
//
// Purpose : An application class derived from CWinApp

class CEditApp : public CWinApp
{
public: 
   virtual BOOL InitInstance();     // overridden from CWnd
};

///////////////////////////////////////////////////////////////////
