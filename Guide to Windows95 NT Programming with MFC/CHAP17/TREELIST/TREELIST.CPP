///////////////////////////////////////////////////////////////////
// Module   : TREELIST.CPP
//
// Purpose  : A program using tree and list controls.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 06-15-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CTestApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class

#define IDC_TREECTRL 125
#define IDC_LISTCTRL 126

#define ROOT       1000
#define ANIMAL     2000
#define VEGETABLE  3000
#define MINERAL    4000

class CMainWnd : public CMainFrame
{
public:
   CMainWnd();
   ~CMainWnd();
  
   afx_msg void OnTreeSelChange(NMHDR* pNotifyStruct, 
      LRESULT* pResult);
   afx_msg void OnTreeLabelChange(NMHDR* pNotifyStruct, 
      LRESULT* pResult);

protected:
   CTreeCtrl m_ctlTree;
   CListCtrl m_ctlList;
 
   void ShowChildren(HTREEITEM hti);

   // Message handlers
   afx_msg int OnCreate(LPCREATESTRUCT lpcs);
   afx_msg void OnSize(UINT nType, int cx, int cy);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// CMainWnd Message Map 

BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_WM_SIZE()
   ON_NOTIFY(TVN_SELCHANGED, IDC_TREECTRL, OnTreeSelChange)
   ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREECTRL, OnTreeLabelChange)
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////
// CMainWnd::CMainFrame() - constructor

CMainWnd::CMainWnd()
{
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpcs)
{    
   if (!m_ctlTree.Create(
           TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | 
           TVS_EDITLABELS | TVS_DISABLEDRAGDROP | WS_VISCHILD |
           WS_BORDER, CRect(0, 0, 0, 0), this, IDC_TREECTRL
        )
      )
      TRACE0(_T("Problem creating tree control!"));      
 
   // Items to add to the tree
   PSTR pszNode[] = {
      "Animal", "Cow", "Squirrel", "Ostrich",
      "Vegetable", "Broccoli", "Spinach", "Potato",
      "Mineral", "Quartz", "Iron", "Potassium"
   };
   
   // Item storage
   HTREEITEM ahTreeItem[13];
   
   // Initailize the top-level items
   ahTreeItem[0] = m_ctlTree.InsertItem("Root", 
                                        0, 
                                        TVI_ROOT);

   ahTreeItem[1] = m_ctlTree.InsertItem(pszNode[0], 
                                        ahTreeItem[0],
                                        ahTreeItem[0]);
   
   ahTreeItem[5] = m_ctlTree.InsertItem(pszNode[4], 
                                        ahTreeItem[0],
                                        ahTreeItem[4]);
  
   ahTreeItem[9] = m_ctlTree.InsertItem(pszNode[8], 
                                        ahTreeItem[0],
                                        ahTreeItem[8]);

   // Initialize app-specific data for the top-level items
   m_ctlTree.SetItemData(ahTreeItem[0], ROOT);
   m_ctlTree.SetItemData(ahTreeItem[1], ANIMAL);
   m_ctlTree.SetItemData(ahTreeItem[5], VEGETABLE);
   m_ctlTree.SetItemData(ahTreeItem[9], MINERAL);
   
   // Initialize the sub-items
   for (int i = 1; i < 4; i++)
      ahTreeItem[i+1] = m_ctlTree.InsertItem(pszNode[i], 
                                             ahTreeItem[1],
                                             ahTreeItem[i]);
   for (i = 5; i < 8; i++)
      ahTreeItem[i+1] = m_ctlTree.InsertItem(pszNode[i], 
                                             ahTreeItem[5],
                                             ahTreeItem[i]);
   for (i = 9; i < 12; i++)
      ahTreeItem[i+1] = m_ctlTree.InsertItem(pszNode[i], 
                                             ahTreeItem[9],
                                             ahTreeItem[i]);

   // Create the list control
   if (!m_ctlList.Create(
           LVS_LIST | WS_VISCHILD | WS_BORDER, 
           CRect(0, 0, 0, 0), this, IDC_LISTCTRL
        )
      )
      TRACE0(_T("Problem creating list control!"));      
 

   // Call inherited method
   return CFrameWnd::OnCreate(lpcs);       
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize()

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   m_ctlTree.SetWindowPos(0, 0, 0, cx / 2, cy, SWP_SHOWWINDOW);
   m_ctlList.SetWindowPos(0, cx / 2 + 1, 0, cx, cy, SWP_SHOWWINDOW);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnTreeSelChange()

void CMainWnd::OnTreeSelChange(NMHDR* pNotifyStruct, 
                                LRESULT* pResult)
{
   // Set the return code
   *pResult = 0;

   // Get the currently selected item
   HTREEITEM hti = m_ctlTree.GetSelectedItem();

   // Show the children of this item
   ShowChildren(hti);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnTreeLabelChange()

void CMainWnd::OnTreeLabelChange(NMHDR* pNotifyStruct, 
                                 LRESULT* pResult)
{
   TV_DISPINFO* ptvdi = (TV_DISPINFO*) pNotifyStruct;
   CString str = ptvdi->item.pszText;

   // Get the currently selected item
   HTREEITEM hti = m_ctlTree.GetSelectedItem();

   if (!str.GetLength()) 
      return;

   if (hti)
      m_ctlTree.SetItemText(hti, (LPCTSTR) str);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::ShowChildren()

void CMainWnd::ShowChildren(HTREEITEM hti)
{
   m_ctlList.DeleteAllItems();

   HTREEITEM htiNext  = 0;
   HTREEITEM htiChild = m_ctlTree.GetChildItem(hti);
   
   if (htiChild)
   {
      // Add the child's tree text to the list
      int i = 0;
      CString str = m_ctlTree.GetItemText(htiChild);

      m_ctlList.InsertItem(i, (LPCTSTR) str);
      htiNext = htiChild;

      // Add sibling tree text to the list
      while (1)
      {
         htiNext = m_ctlTree.GetNextSiblingItem(htiNext);
         if (!htiNext) return;
         
         CString str = m_ctlTree.GetItemText(htiNext);
         i++; 
         m_ctlList.InsertItem(i, (LPCTSTR) str);         
      }
   }
}

///////////////////////////////////////////////////////////////////
// CTestApp::InitInstance - overrides CWinApp::InitInstance

BOOL CTestApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Tree View and List View Controls"), 
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                  CRect(0, 0, 640, 480));

   // Set the client area back color
   pFrame->SetClientBackColor(COLOR_3DFACE);

   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CTestApp MyApp;

///////////////////////////////////////////////////////////////////
