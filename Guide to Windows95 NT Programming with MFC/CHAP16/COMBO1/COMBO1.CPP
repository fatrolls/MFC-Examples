///////////////////////////////////////////////////////////////////
// Module   : COMBO1.CPP
//
// Purpose  : Implementation of an MFC program that shows how to 
//            use 2 standard combo boxes and 1 owner-draw combo
//            box containing color items.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-18-96
///////////////////////////////////////////////////////////////////

#include "combo1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_ERASEBKGND()
   ON_COMMAND(IDC_BTNCHANGECLR, OnBtnChangeColorClick)
   ON_CBN_DBLCLK(IDC_COLORCOMBO, OnColorComboDblClick)
END_MESSAGE_MAP()
                                             
//
// CColorCombo methods         
//

///////////////////////////////////////////////////////////////////
// CColorCombo::AddColorToList() 

void CColorCombo::AddColorToList(COLORREF crColor)
{
   // add an RGB color as a combo box string 
   AddString((LPCTSTR) crColor);
}

///////////////////////////////////////////////////////////////////
// CDropCombo::FillList() 

void CDropCombo::FillList()
{
   ResetContent();
   AddString(_T("This"));  AddString(_T("is"));
   AddString(_T("only"));  AddString(_T("a"));
   AddString(_T("very"));  AddString(_T("simple"));
   AddString(_T("test."));
}

///////////////////////////////////////////////////////////////////
// CDropList::FillList() 

void CDropList::FillList()
{
   ResetContent();
   AddString(_T("Cyan"));
   AddString(_T("Magenta"));
   AddString(_T("Yellow"));
   AddString(_T("Gray"));
}

///////////////////////////////////////////////////////////////////
// CColorCombo::FillList() 

void CColorCombo::FillList(UINT nColorIndex)
{
   switch (nColorIndex) 
   {
      case CYAN:
      {
         // Add 16 progressively darker shades of cyan
         for (int i = 255; i > 0; i-=16)
            AddColorToList(RGB(0, i, i));
         break;
      }
      
      case MAGENTA:
      {
         // Add 16 progressively darker shades of magenta
         for (int i = 255; i > 0; i-=16)
            AddColorToList(RGB(i, 0, i));
         break;
      }

      case YELLOW:
      {
         // Add 16 progressively darker shades of yellow
         for (int i = 255; i > 0; i-=16)
            AddColorToList(RGB(i, i, 0));
         break;
      }

      case GRAY:
      {
         // Add 16 progressively darker shades of gray
         for (int i = 255; i > 0; i-=16)
            AddColorToList(RGB(i, i, i));
         break;
      }
      default:
        break;
   } 
   return;
}

///////////////////////////////////////////////////////////////////
// CColorCombo::DrawItem() - overridden method called by MFC

void CColorCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   // get a device context for the current item
   CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

   // get the RGB that's stored as item data
   COLORREF cr = (COLORREF)lpDrawItemStruct->itemData; 
                                                                 
   if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
   {
      // Paint the item in the color defined by cr
      CBrush br(cr);
      pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
   }

   // See if this item is currently selected or not
   if (lpDrawItemStruct->itemState & ODS_SELECTED) 
   {
      // The item is selected, so draw a highlighted border
      COLORREF crBorderColor;
      crBorderColor = RGB(255 - GetRValue(cr),
                          255 - GetGValue(cr), 
                          255 - GetBValue(cr));
      
      // Create a brush for the highlighted border
      CBrush br(crBorderColor);
      pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
   }
   
   else 
   {
      // item isn't selected, so draw a frame the same color as cr
      CBrush br(cr);
      pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
   }
}

///////////////////////////////////////////////////////////////////
// CColorCombo::MeasureItem() - overridden method called by MFC

void CColorCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMeasure)
{
   lpMeasure->itemHeight = 25;  // set item height
}

//
// CMainWnd methods 
//

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{
   // Set initial color to medium gray
   m_crBackColor = RGB(192, 192, 192);

   // initialize child pointers to NULL
   m_pClrCombo  = 0;  
   m_pDropCombo = 0; 
   m_pDropList  = 0;  

   m_pBtnChangeColor = 0;  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - override destructor

CMainWnd::~CMainWnd()
{
   if (m_pClrCombo)  delete m_pClrCombo;
   if (m_pDropCombo) delete m_pDropCombo;
   if (m_pDropList)  delete m_pDropList;

   if (m_pBtnChangeColor) delete m_pBtnChangeColor;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() - overrides CMainFrame method

void CMainWnd::CreateChildControls()
{
   // Allocate the color combo box
   m_pClrCombo  = new CColorCombo; ASSERT_VALID(m_pClrCombo);
   m_pDropCombo = new CDropCombo;  ASSERT_VALID(m_pDropCombo);
   m_pDropList  = new CDropList;   ASSERT_VALID(m_pDropList);

   m_pBtnChangeColor = new CButton; ASSERT_VALID(m_pBtnChangeColor);
   
   // initialize the color combo box 
   if (!m_pClrCombo->Create(CBS_COLOR, 
      CRect(10, 10, 300, 400), this, IDC_COLORCOMBO))
      { TRACE0("Failed to create combo box\n"); }

   // initialize the drop-down combo box 
   if (!m_pDropCombo->Create(CBS_DROPCOMBO, 
      CRect(305, 10, 410, 400), this, IDC_COLORCOMBO))
      { TRACE0("Failed to create combo box\n"); }

   // initialize the drop-down list box 
   if (!m_pDropList->Create(CBS_DROPLIST, 
      CRect(305, 45, 410, 400), this, IDC_COLORCOMBO))
      { TRACE0("Failed to create combo box\n"); }

   // initialize the change color button 
   if (!m_pBtnChangeColor->Create("Change Color", BS_COMMAND, 
      CRect(305, 80, 410, 110), this, IDC_BTNCHANGECLR))
      { TRACE0("Failed to create button\n"); }

   // Set the text-frame heights
   m_pClrCombo ->SetItemHeight(-1, 20);
   m_pDropCombo->SetItemHeight(-1, 20);
   m_pDropList ->SetItemHeight(-1, 20);

   // Fill the combo box lists
   m_pClrCombo ->FillList(CYAN);
   m_pDropCombo->FillList();
   m_pDropList ->FillList();

   m_pDropList->SetExtendedUI(); 

   // Set the default color string
   m_pDropList ->SelectString(-1, _T("Cyan"));  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBtnChangeColorClick()

void CMainWnd::OnBtnChangeColorClick()
{
   // Clear the current colors
   m_pClrCombo->ResetContent();

   // Determine new color and fill the color list
   int nWhich = m_pDropList->GetCurSel();
   m_pClrCombo->FillList(nWhich);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   // We're explicitly painting the entire client area, so we 
   // don't want to call the inherited method...
   
   // create a brush of desired background color
   CBrush brClientColor(m_crBackColor);

   // paint the client area as m_crBackColor
   CRect rc;
   GetClientRect(&rc);
   pDC->FillRect(&rc, &brClientColor);

   return TRUE;
}    

///////////////////////////////////////////////////////////////////
// CMainWnd::OnColorComboDblClick()  

void CMainWnd::OnColorComboDblClick()
{
   // Find the combo box element currently selected
   int nCurSel = m_pClrCombo->GetCurSel();

   // Get the color from the selected item
   COLORREF crSel = (COLORREF)m_pClrCombo->GetItemData(nCurSel);

   // Set the client area background to the selected color
   SetBackColor(crSel);
   InvalidateRect(0); 
   
   // Get a pointer to the edit control of the color combo 
   CEdit* pColorEdit;
   pColorEdit = (CEdit*)m_pClrCombo->GetDlgItem(IDC_EDITCONTROL);

   // Change the combo box edit control color
   CRect rc; 
   CBrush br(crSel);

   pColorEdit->GetClientRect(&rc);
   pColorEdit->GetDC()->FillRect(&rc, &br);
}                      

//
// CComboApp methods 
//

///////////////////////////////////////////////////////////////////
// CComboApp::InitInstance() - overrides CWinApp method

BOOL CComboApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Combo Box Sample Program"), 
                  WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   AfxGetApp()->m_pMainWnd = pFrame;

   // Create the combo box
   pFrame->CreateChildControls();

   // Show the frame window
   pFrame->ShowWindow(SW_SHOWMAXIMIZED);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CComboApp MyComboApp;

///////////////////////////////////////////////////////////////////
