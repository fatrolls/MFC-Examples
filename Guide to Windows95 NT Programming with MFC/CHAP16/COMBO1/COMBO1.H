///////////////////////////////////////////////////////////////////
// Header  : COMBO1.H
//
// Purpose : Header for CComboApp
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//       
// Date    : 03-08-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define 3 custom combo box styles
#define CBS_COLOR (CBS_OWNERDRAWFIXED | CBS_SIMPLE | WS_VSCROLL | \
                   CBS_NOINTEGRALHEIGHT| WS_BORDER | WS_VISIBLE | \
                   WS_CHILD)

#define CBS_DROPCOMBO (WS_VSCROLL | WS_BORDER | CBS_DROPDOWN | \
                       WS_VISIBLE | WS_CHILD)

#define CBS_DROPLIST (WS_VSCROLL | WS_BORDER | CBS_DROPDOWNLIST | \
                      WS_VISIBLE | WS_CHILD)

// Button style
#define BS_COMMAND (BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD )

// Control IDs
#define IDC_DROPCOMBO    100  // control ID for drop-down combo
#define IDC_DROPLIST     101  // control ID for drop-down list
#define IDC_COLORCOMBO   102  // control ID for color combo
#define IDC_BTNCHANGECLR 103  // control ID for change color button 

// A combo box's edit control ID is always 1001
#define IDC_EDITCONTROL  1001 

// Color indices for color combo
#define CYAN     0
#define MAGENTA  1
#define YELLOW   2
#define GRAY     3

///////////////////////////////////////////////////////////////////
// Class   : CColorCombo

class CColorCombo : public CComboBox
{
protected:   
   // Overridden ancestor methods
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
   virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

public:
   // helper methods
   void AddColorToList(COLORREF crColor);
   void FillList(UINT nColorIndex);            
};

///////////////////////////////////////////////////////////////////
// Class : CDropCombo

class CDropCombo : public CComboBox
{
public:
   void FillList();  // helper method          
};

///////////////////////////////////////////////////////////////////
// Class : CDropList

class CDropList : public CComboBox
{
public:
   void FillList();  // helper method          
};

///////////////////////////////////////////////////////////////////
// Class : CMainWnd
//
// Purpose : A frame window derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   COLORREF     m_crBackColor;         // background color 
   CColorCombo* m_pClrCombo;           // color combo member
   CDropCombo*  m_pDropCombo;          // drop-down combo member
   CDropList*   m_pDropList;           // drop-down list member
   CButton*     m_pBtnChangeColor;     // change color button member

public:
   CMainWnd();                         // Constructor
   ~CMainWnd();                        // Destructor
   
   void SetBackColor(COLORREF cr);     // access method
   virtual void CreateChildControls(); // override CMainFrame method

   // message handlers
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);  // message handler
   afx_msg void OnColorComboDblClick();  // respond to double click
   afx_msg void OnBtnChangeColorClick(); // change color
                
   DECLARE_MESSAGE_MAP();
};

inline void CMainWnd::SetBackColor(COLORREF cr)
   { m_crBackColor = cr; }

///////////////////////////////////////////////////////////////////
// Class   : CComboApp
//
// Purpose : An application class derived from CWinApp

class CComboApp : public CWinApp
{
public: 
   virtual BOOL InitInstance();       // overridden from CWnd
};

///////////////////////////////////////////////////////////////////

