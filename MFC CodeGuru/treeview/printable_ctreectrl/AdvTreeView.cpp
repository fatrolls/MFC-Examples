//  ---------------------------------------------------------
//
//      ( C )     Copyright C - Channel Eng. AG 1998
//      Use or copying of all or any part of the document,
//      except as permitted by the License Agreement is
//      prohibited.
//
//      Author  : Michael Wild, 5063  C - Channel Eng. AG
//
//      Purpose : 
//      This File contains the class CAdvancedTreeView
// 
//      Creation date: April 28, 1998
//
//  ---------------------------------------------------------

#include "stdafx.h"
#include "PrintTree.h"

#include "PrintTreeDoc.h"
#include "AdvTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Image list indexes
#define ILI_HARD_DISK       0
#define ILI_FLOPPY          1
#define ILI_CD_ROM          2
#define ILI_NET_DRIVE       3
#define ILI_RAM_DRIVE       4
#define ILI_CLOSED_FOLDER   5
#define ILI_OPEN_FOLDER     6

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeView

IMPLEMENT_DYNCREATE(CAdvancedTreeView, CFormView)

BEGIN_MESSAGE_MAP(CAdvancedTreeView, CFormView)
	//{{AFX_MSG_MAP(CAdvancedTreeView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeView construction/destruction

CAdvancedTreeView::CAdvancedTreeView()
	: CFormView(CAdvancedTreeView::IDD)
     ,m_wndTree()
{
	//{{AFX_DATA_INIT(CAdvancedTreeView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_bFirstTime        = TRUE;
}

CAdvancedTreeView::~CAdvancedTreeView()
{
}

void CAdvancedTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedTreeView)
	DDX_Control(pDX, IDC_TREE1, m_wndTree);
	//}}AFX_DATA_MAP
}

BOOL CAdvancedTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeView printing

BOOL CAdvancedTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAdvancedTreeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    m_bFirstTime                   = TRUE;
    m_wndTree.m_bContinuePrinting  = TRUE;

    // Fill the DIB-Array
    m_wndTree.CreateDibArrays();
}

void CAdvancedTreeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    m_bFirstTime                   = TRUE;
    m_wndTree.m_bContinuePrinting  = TRUE;

    // Empty the DIB-Array
    m_wndTree.DeleteDibArrays();
}

void CAdvancedTreeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CFormView::OnPrepareDC(pDC, pInfo);

    // Stop Printing
    if( NULL != pInfo )
    {
        if( FALSE == pInfo->m_bPreview )
        {
            // Set the Continueflag
            pInfo->m_bContinuePrinting = m_wndTree.m_bContinuePrinting;	
        }
    }
}

void CAdvancedTreeView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // Define the Originmapping of the viewport and 
    // the window for Footer and Header
    int iSavedPageStart = pInfo->m_rectDraw.top;
    pDC->SetWindowOrg( 0,  0 );
    pDC->SetViewportOrg( pInfo->m_rectDraw.left,  -iSavedPageStart );

    // Print the Page
        // Get the View-DC
        CDC* pViewDC = GetDC();

        // Set the Mappingmode
        pDC->SetMapMode(MM_ANISOTROPIC);

        // Define the Originmapping of the viewport and 
        // the window for Treeoutput
        pDC->SetWindowOrg( 0,  0 );
        pDC->SetViewportOrg( pInfo->m_rectDraw.left,  pInfo->m_rectDraw.top - iSavedPageStart );

        // Define the Extentmapping of the viewport and the Window
        pDC->SetViewportExt( pDC->GetDeviceCaps(LOGPIXELSX)
						    ,pDC->GetDeviceCaps(LOGPIXELSY) );

        pDC->SetWindowExt( pViewDC->GetDeviceCaps(LOGPIXELSX)
					      ,pViewDC->GetDeviceCaps(LOGPIXELSY) );

        // Release the View-DC
        ReleaseDC(pViewDC);

        if( TRUE == m_bFirstTime )
        {    
            // Draw the Tree to the Printer-DC
            m_wndTree.MakePaging( pDC, pInfo );

            m_bFirstTime = FALSE;
        }

        // Draw the Tree to the Printer-DC
        m_wndTree.DrawTreeCtrl( pDC, pInfo );
}

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeView diagnostics

#ifdef _DEBUG
void CAdvancedTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAdvancedTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPrintTreeDoc* CAdvancedTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintTreeDoc)));
	return (CPrintTreeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeView message handlers

void CAdvancedTreeView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

    m_wndTree.InitImageList();

    // Fill the tree with colored text.
	CString m_str;
	for(int i=1;i<=10;i++)
	{
		m_str.Format("Parent Item %d", i);
		HTREEITEM hItem = m_wndTree.InsertItem(m_str, 0, 0);
		for(int j=1;j<=5;j++)
		{
			m_str.Format("Child Item %d", j);
			HTREEITEM hChild = m_wndTree.InsertItem(m_str, 1, 1, hItem);
		    for(int k=1;k<=5;k++)
		    {
			    m_str.Format("ChildChild Item %d", k);
			    HTREEITEM hChildChild = m_wndTree.InsertItem(m_str, 1, 1, hChild);
		        for(int s=1;s<=5;s++)
		        {
			        m_str.Format("ChildChildChild Item %d", s);
			        HTREEITEM hChildChildChild = m_wndTree.InsertItem(m_str, 1, 1, hChildChild);
		        }
		    }
		}
	}
    
    // Fill the tree with default text.
	HTREEITEM hItem = m_wndTree.InsertItem("Parent Item default A", 0, 0);
	HTREEITEM hChild = m_wndTree.InsertItem("Child Item default A", 1, 1, hItem);
	hItem = m_wndTree.InsertItem("Parent Item default B", 0, 0);
	hChild = m_wndTree.InsertItem("Child Item default B", 1, 1, hItem);

    // Fill the tree special text.
	hItem = m_wndTree.InsertItem("Parent Item default A", 0, 0);
	hChild = m_wndTree.InsertItem("Child Item default A", 1, 1, hItem);
	hItem = m_wndTree.InsertItem("Parent Item default B", 0, 0);
	hChild = m_wndTree.InsertItem("Child Item default B", 1, 1, hItem);

    // Fill the tree with Text and Icons
    hItem = m_wndTree.InsertItem( "Floppy Drive", ILI_FLOPPY, ILI_FLOPPY );
    hChild = m_wndTree.InsertItem( "Child Node", ILI_CLOSED_FOLDER, 
                                       ILI_OPEN_FOLDER, hItem, TVI_SORT);

    hItem = m_wndTree.InsertItem( "HardDisk Drive", ILI_HARD_DISK, ILI_HARD_DISK );
    hChild = m_wndTree.InsertItem( "Child Node", ILI_CLOSED_FOLDER, 
                                       ILI_OPEN_FOLDER, hItem, TVI_SORT);

    hItem = m_wndTree.InsertItem( "Net Drive", ILI_NET_DRIVE, ILI_NET_DRIVE );
    hChild = m_wndTree.InsertItem( "Child Node", ILI_CLOSED_FOLDER, 
                                       ILI_OPEN_FOLDER, hItem, TVI_SORT);

    hItem = m_wndTree.InsertItem( "CD Drive", ILI_CD_ROM, ILI_CD_ROM );
    hChild = m_wndTree.InsertItem( "Child Node", ILI_CLOSED_FOLDER, 
                                       ILI_OPEN_FOLDER, hItem, TVI_SORT);
    HTREEITEM hChildChild = m_wndTree.InsertItem( "ChildChild Node", ILI_CLOSED_FOLDER, 
                                       ILI_OPEN_FOLDER, hChild, TVI_SORT);

    // Set Overlay-Image
    BOOL b = m_wndTree.SetItemState( hChildChild, INDEXTOOVERLAYMASK(2), TVIS_OVERLAYMASK );

    // Sizing the Treecontrol equal to the ClientAreaSize
    RECT locRect;
    GetClientRect( &locRect );
    m_wndTree.MoveWindow( 0, 0, locRect.right, locRect.bottom );
    m_wndTree.ShowWindow( TRUE );
}

void CAdvancedTreeView::OnSize(UINT nType, int cx, int cy) 
{
    // CFormView::OnSize(nType, cx, cy); Not needed!!! 
    // Do my own Size-Handling. Othervise it could happen,
    // that two overlayed Scrollbars are painted.
    if( m_wndTree.m_hWnd )
    {
        // Fill the whole Client Area of the View with the Control
        m_wndTree.MoveWindow( 0, 0, cx, cy );
    }
}
