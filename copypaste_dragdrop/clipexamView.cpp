// clipexamView.cpp : implementation of the CClipExamView class
//

#include "stdafx.h"
#include "clipexam.h"

#include "clipexamDoc.h"
#include "clipexamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipExamView

IMPLEMENT_DYNCREATE(CClipExamView, CView)

BEGIN_MESSAGE_MAP(CClipExamView, CView)
	//{{AFX_MSG_MAP(CClipExamView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipExamView construction/destruction

CClipExamView::CClipExamView()
{
	// TODO: add construction code here

}

CClipExamView::~CClipExamView()
{
}

BOOL CClipExamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClipExamView drawing

void CClipExamView::OnDraw(CDC* pDC)
{
	CClipExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CClipExamView printing

BOOL CClipExamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClipExamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClipExamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CClipExamView diagnostics

#ifdef _DEBUG
void CClipExamView::AssertValid() const
{
	CView::AssertValid();
}

void CClipExamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClipExamDoc* CClipExamView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClipExamDoc)));
	return (CClipExamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipExamView message handlers

void CClipExamView::OnEditCopy() 
{
	COleDataSource*	pSource = new COleDataSource();
	CSharedFile	sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
	CString		text = _T("Testing 1... 2... 3...");

	sf.Write(text, text.GetLength()); // You can write to the clipboard as you would to any CFile

	HGLOBAL hMem = sf.Detach();
	if (!hMem) return;
	pSource->CacheGlobalData(CF_TEXT, hMem);
	pSource->SetClipboard();
}

void CClipExamView::OnEditPaste() 
{
	COleDataObject	obj;

	if (obj.AttachClipboard()) {
		if (obj.IsDataAvailable(CF_TEXT)) {
			HGLOBAL hmem = obj.GetGlobalData(CF_TEXT);
			CMemFile sf((BYTE*) ::GlobalLock(hmem), ::GlobalSize(hmem));
			CString buffer;

			LPSTR str = buffer.GetBufferSetLength(::GlobalSize(hmem));
			sf.Read(str, ::GlobalSize(hmem));
			::GlobalUnlock(hmem);

			// Do something with the data in 'buffer'
			TRACE("Paste received = '%s'\r\n", buffer);
		}
	}
}

DROPEFFECT CClipExamView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if (pDataObject->IsDataAvailable(CF_TEXT)) {
		return DROPEFFECT_COPY;		
	}
	return DROPEFFECT_NONE;
}

BOOL CClipExamView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if (pDataObject->IsDataAvailable(CF_TEXT)) {
		HGLOBAL hmem = pDataObject->GetGlobalData(CF_TEXT);
		CMemFile sf((BYTE*) ::GlobalLock(hmem), ::GlobalSize(hmem));
		CString buffer;

		LPSTR str = buffer.GetBufferSetLength(::GlobalSize(hmem));
		sf.Read(str, ::GlobalSize(hmem));
		::GlobalUnlock(hmem);

		// Do something with the data in 'buffer'
		TRACE("OnDrop received = '%s'\r\n", buffer);
		return TRUE;
	}
	return FALSE;
}

void CClipExamView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	COleDataSource*	pSource = new COleDataSource();
	CSharedFile	sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
	CString		text = _T("Testing 1... 2... 3...");

	sf.Write(text, text.GetLength()); // You can write to the clipboard as you would to any CFile

	HGLOBAL hMem = sf.Detach();
	if (!hMem) return;
	pSource->CacheGlobalData(CF_TEXT, hMem);
	pSource->DoDragDrop();
}

void CClipExamView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	m_DropTarget.Register(this);
}
