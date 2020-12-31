// LayoutView.cpp : implementation of the CLayoutView class
//

#include "stdafx.h"
#include "Layout.h"

#include "LayoutDoc.h"
#include "LayoutView.h"

#include "OXLayoutManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OX_OFFSET (7)	// This is the default padding in the Visual C++ Dialog editor
						// so we use it here too. This number must be >= 0

/////////////////////////////////////////////////////////////////////////////
// CLayoutView

IMPLEMENT_DYNCREATE(CLayoutView, CFormView)

BEGIN_MESSAGE_MAP(CLayoutView, CFormView)
	//{{AFX_MSG_MAP(CLayoutView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayoutView construction/destruction

CLayoutView::CLayoutView()
	: CFormView(CLayoutView::IDD)
{
	//{{AFX_DATA_INIT(CLayoutView)
	//}}AFX_DATA_INIT

	m_pLayoutManager = NULL;
}

CLayoutView::~CLayoutView()
{
	if (m_pLayoutManager != NULL)
	{
		delete m_pLayoutManager;
		m_pLayoutManager = NULL;
	}
}

void CLayoutView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CLayoutView)
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Control(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}

BOOL CLayoutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutView printing

BOOL CLayoutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLayoutView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLayoutView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLayoutView::OnPrint(CDC* /*pDC*/, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutView diagnostics

#ifdef _DEBUG
void CLayoutView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLayoutView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLayoutDoc* CLayoutView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLayoutDoc)));
	return (CLayoutDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLayoutView message handlers

void CLayoutView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	if (m_pLayoutManager == NULL)
	{
		if ((m_pLayoutManager = new COXLayoutManager(this)) != NULL)
		{
			ASSERT_VALID(m_pLayoutManager);

			// Force the Frame to size with the parent window on the left and right
			// sides with an offset of OX_OFFSET (Note: On the right side we need
			// to use a negative offset)
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);

			// Force progress bar to size between the (above) frame with the same offset
			m_pLayoutManager->SetConstraint(IDC_PROGRESS, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_PROGRESS, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);

			// Size combo box with the right side of the Frame
			// The combo box window will not resize, it will only move; This is because we
			// have not setup a constraint on combo box on the left side.
			m_pLayoutManager->SetConstraint(IDC_COMBO, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);

			// Setup the slider bar to fill the space between the FRAME on the left side
			// and the combo box on the right side. Note the usage of the OX_LMT_OPPOSITE 
			// flag here instead of OX_LMT_SAME.
			m_pLayoutManager->SetConstraint(IDC_SLIDER, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_SLIDER, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_COMBO);
			//
			// Set the minimum size for the slider control
			m_pLayoutManager->SetMinMax(IDC_SLIDER, CSize(50, 0));

			// BUTTON SIZING
			m_pLayoutManager->SetConstraint(IDC_BUTTON, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_BUTTON, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_BUTTON, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_FRAME);

			// EDIT SIZING
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -3 /* = 3 pixels (just because OX_OFFSET is too big here*/, IDC_BUTTON);
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_FRAME);
			
			// The following enclosed controls are sized between each other. This is done using the
			// OX_LMT_POSITION flag and setting a percentage of fill space for the window
			//
			// The Tree control is positioned relative to the FormView filling 33% of
			// the window space.
			// The Radio, Picture and Picture2 controls are sized between the Tree and
			// the Listbox filling the remaining space (33%)
			//
			// The listbox is sized on from 66% of the window until the window edge; it is
			// sized to 33% of the window.
			
			// TREE SIZING
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_EDIT);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_RIGHT, OX_LMT_POSITION, 33);

			// RADIO SIZING
			m_pLayoutManager->SetConstraint(IDC_RADIO, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_PICTURE);
			m_pLayoutManager->SetConstraint(IDC_RADIO, OX_LMS_LEFT, OX_LMT_OPPOSITE, OX_OFFSET, IDC_TREE);
			m_pLayoutManager->SetConstraint(IDC_RADIO, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_LIST);

			// PICTURE2 SIZING
			m_pLayoutManager->SetConstraint(IDC_PICTURE2, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_RADIO);
			m_pLayoutManager->SetConstraint(IDC_PICTURE2, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_TEXT);
			m_pLayoutManager->SetConstraint(IDC_PICTURE2, OX_LMS_LEFT, OX_LMT_OPPOSITE, OX_OFFSET, IDC_TREE);
			m_pLayoutManager->SetConstraint(IDC_PICTURE2, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_LIST);
			//
			// Set minium height of this picture
			m_pLayoutManager->SetMinMax(IDC_PICTURE2, CSize(0, 5));

			// PICTURE SIZING
			m_pLayoutManager->SetConstraint(IDC_PICTURE, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_EDIT);
			m_pLayoutManager->SetConstraint(IDC_PICTURE, OX_LMS_LEFT, OX_LMT_OPPOSITE, OX_OFFSET, IDC_TREE);
			m_pLayoutManager->SetConstraint(IDC_PICTURE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_LIST);

			// LIST SIZING
			// (The bottom edge of this window is sized according to the upper edge of
			// the (below) Static Text control using the OX_LMT_OPPOSITE)
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_LEFT, OX_LMT_POSITION, 66);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_EDIT);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -OX_OFFSET, IDC_TEXT);

			// TEXT SIZING
			m_pLayoutManager->SetConstraint(IDC_TEXT, OX_LMS_LEFT, OX_LMT_OPPOSITE, OX_OFFSET, IDC_TREE);
			m_pLayoutManager->SetConstraint(IDC_TEXT, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);

			// Redraw the controls in the window with the new layout
			m_pLayoutManager->RedrawLayout();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Set some data on the dialog
	
	m_progress.SetRange(0, 100);
	m_progress.SetPos(30);

	m_edit.SetWindowText(_T("C:\\Ultimate Toolbox\\"));

	HTREEITEM hItem = m_tree.InsertItem(_T("Root"));
	TCHAR szBuffer[10];
	int i = 0;
	for (; i < 100; i++)
	{
		wsprintf(szBuffer, _T("Item #%d"), i);
		
		m_combo.InsertString(i, szBuffer);
		m_list.InsertString(i, szBuffer);

		m_tree.InsertItem(szBuffer, hItem);
	}

	m_tree.ModifyStyle(NULL, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	m_tree.Expand(hItem, TVE_EXPAND);
}

void CLayoutView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	////////////////////////////////////////////
	//
	// Undo MFC's adding of Vertical and/or Horizontal
	// scroll bars

	SetScrollSizes(MM_TEXT, CSize(0, 0));
}
