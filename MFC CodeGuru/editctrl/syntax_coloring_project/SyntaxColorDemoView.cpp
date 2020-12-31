// SyntaxColorDemoView.cpp : implementation of the CSyntaxColorDemoView class
//

#include "stdafx.h"
#include "SyntaxColorDemo.h"

#include "SyntaxColorDemoDoc.h"
#include "SyntaxColorDemoView.h"

#include "ColorEditWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoView

IMPLEMENT_DYNCREATE(CSyntaxColorDemoView, CFormView)

BEGIN_MESSAGE_MAP(CSyntaxColorDemoView, CFormView)
	//{{AFX_MSG_MAP(CSyntaxColorDemoView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(IDM_RETAB, OnRetab)
	ON_COMMAND(IDM_SHOW, OnShow)
	ON_UPDATE_COMMAND_UI(IDM_SHOW, OnUpdateShow)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoView construction/destruction

CSyntaxColorDemoView::CSyntaxColorDemoView()
	: CFormView(CSyntaxColorDemoView::IDD)
{
	//{{AFX_DATA_INIT(CSyntaxColorDemoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	cColorWnd = NULL;
}

CSyntaxColorDemoView::~CSyntaxColorDemoView()
{
	if(cColorWnd) delete cColorWnd;
}

void CSyntaxColorDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyntaxColorDemoView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CSyntaxColorDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoView printing

BOOL CSyntaxColorDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSyntaxColorDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSyntaxColorDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSyntaxColorDemoView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoView diagnostics

#ifdef _DEBUG
void CSyntaxColorDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSyntaxColorDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSyntaxColorDemoDoc* CSyntaxColorDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSyntaxColorDemoDoc)));
	return (CSyntaxColorDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoView message handlers

void CSyntaxColorDemoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	CRect client;
	GetClientRect(client);
	CString keywordsFile = "Keywords.ini";
	BOOL caseSensitive = FALSE;
	long pCharDX = 10;
	long pCharDY = 16;
	long pTabSize = 4;
	int pFontSize = 120;
	CString pFontName = "Courier New";


/*
	cColorWnd = new ColorEditWnd(
		this,			//parent window
		client,			//initial size and position
		IDC_COLOR_WND,	//id value
		keywordsFile,	//keywords file
		caseSensitive,	//case sensitive ? 
		pCharDX,		//width of each character
		pCharDY,		//height of each character
		pTabSize,		//size of a tab
		pFontSize,		//font size * 10 (I.E. 100 = 10)
		pFontName);		//the font name
*/
	cColorWnd = new ColorEditWnd(
		this,				//parent window
		client,				//position
		IDC_COLOR_WND,		//controlid
		keywordsFile,		//file of keywords
		TRUE,				//case sensitive?
		6,					//char width 
		11,					//char height
		2,					//tab spacng
		80,					//Font size
		CString("Courier New")	//Font name
		);

	cColorWnd->ShowWindow(SW_HIDE);

}

void CSyntaxColorDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	CRect client;
	GetClientRect(client);
	if(cColorWnd)
	{
		cColorWnd->SetWindowPos(this,client.left,client.top,
			client.Width(), client.Height(), SWP_NOZORDER);
	}
}

int CSyntaxColorDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CSyntaxColorDemoView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CFormView::OnSetCursor(pWnd, nHitTest, message);
}

void CSyntaxColorDemoView::OnEditCopy() 
{
	cColorWnd->DoCopy();
}

void CSyntaxColorDemoView::OnEditPaste() 
{
	cColorWnd->DoPaste();
}

void CSyntaxColorDemoView::OnRetab() 
{
	cColorWnd->Retab();
}

void CSyntaxColorDemoView::OnDraw(CDC* pDC) 
{
	CRect rect;
	pDC->GetClipBox(rect);
	pDC->FillSolidRect(rect,RGB(200,100,100));
}

void CSyntaxColorDemoView::OnShow() 
{
	if(cColorWnd->IsWindowVisible())
	{
		cColorWnd->ShowWindow(SW_HIDE);
	}
	else
	{
		cColorWnd->ShowWindow(SW_SHOW);
		cColorWnd->SetFocus();
	}
}

void CSyntaxColorDemoView::OnUpdateShow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((cColorWnd->IsWindowVisible()));
}

void CSyntaxColorDemoView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFormView::OnShowWindow(bShow, nStatus);
	
}
