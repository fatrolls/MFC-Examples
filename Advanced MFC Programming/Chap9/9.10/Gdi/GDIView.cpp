#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC *pDC)
{
	CString szText;
	CString szStr;
	CFont *ptrFontOld;
	int nSelIndexBgn;
	int nSelIndexEnd;
	int nSel;
	UINT uTextAlign;
	COLORREF colorFg;
	COLORREF colorBk;

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	szText=pDoc->GetText();
	ptrFontOld=pDC->SelectObject(pDoc->GetFont());
	nSelIndexBgn=pDoc->GetSelIndexBgn();
	nSelIndexEnd=pDoc->GetSelIndexEnd();
	if
	(
		nSelIndexBgn == -1 || 
		nSelIndexEnd == -1 ||
		(nSelIndexBgn == nSelIndexEnd)
	)
	{
		pDC->TextOut(0, 0, szText);
	}
	else
	{
		if(nSelIndexEnd < nSelIndexBgn)
		{
			nSel=nSelIndexBgn;
			nSelIndexBgn=nSelIndexEnd;
			nSelIndexEnd=nSel;
		}
		uTextAlign=pDC->SetTextAlign(TA_UPDATECP);
		szStr=szText.Left(nSelIndexBgn);
		pDC->TextOut(0, 0, szStr);
		colorFg=pDC->GetTextColor();
		colorBk=pDC->GetBkColor();
		pDC->SetTextColor(colorBk);
		pDC->SetBkColor(colorFg);
		szStr=szText.Mid(nSelIndexBgn, nSelIndexEnd-nSelIndexBgn);
		pDC->TextOut(0, 0, szStr);
		pDC->SetTextColor(colorFg);
		pDC->SetBkColor(colorBk);
		szStr=szText.Mid(nSelIndexEnd);
		pDC->TextOut(0, 0, szStr);
		pDC->SetTextAlign(uTextAlign);
	}
	pDC->SelectObject(ptrFontOld);
}

void CGDIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	sizeTotal.cx=sizeTotal.cy=100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CreateNewCaret(FALSE);
	m_hCur=AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

void CGDIView::OnDestroy() 
{
	HideCaret();
	::DestroyCaret();
	CScrollView::OnDestroy();
}

void CGDIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CGDIDoc *ptrDoc;
	SHORT nKeyState;

	ptrDoc=(CGDIDoc *)GetDocument();
	ASSERT(ptrDoc);
	switch(nChar)
	{
		case VK_LEFT:
		{
			nKeyState=GetKeyState(VK_CONTROL);
			if(HIBYTE(nKeyState) != 0)
			{
				ptrDoc->BackwardCaretToBlank();
			}
			else ptrDoc->BackwardCaret();
			break;
		}
		case VK_RIGHT:
		{
			nKeyState=GetKeyState(VK_CONTROL);
			if(HIBYTE(nKeyState) != 0)
			{
				ptrDoc->ForwardCaretToBlank();
			}
			else ptrDoc->ForwardCaret();
			break;
		}
		case VK_END:
		{
			ptrDoc->EndCaret();
			break;
		}
		case VK_HOME:
		{
			ptrDoc->HomeCaret();
			break;
		}
		case VK_DELETE:
		{
			ptrDoc->DeleteChar(FALSE);
			break;
		}
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGDIView::RedrawCaret()
{
	CGDIDoc *ptrDoc;

	ptrDoc=(CGDIDoc *)GetDocument();
	HideCaret();
	SetCaretPos(ptrDoc->GetCaretPosition());
	ShowCaret();
}

void CGDIView::CreateNewCaret(BOOL bDestroy)
{
	CGDIDoc *ptrDoc;

	if(bDestroy == TRUE)::DestroyCaret();
	ptrDoc=(CGDIDoc *)GetDocument();
	CreateSolidCaret(0, ptrDoc->GetCaretVerSize());
	SetCaretPos(ptrDoc->GetCaretPosition());
	ShowCaret();
}

void CGDIView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CGDIDoc *ptrDoc;
	
	ptrDoc=(CGDIDoc *)GetDocument();
	if(nChar != VK_RETURN && nChar != VK_ESCAPE && nChar != VK_TAB)
	{
		if(nChar == VK_BACK)ptrDoc->DeleteChar(TRUE);
		else ptrDoc->AddChar(nChar, nRepCnt);
	}
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CGDIView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message) 
{
	POINT pt;
	CRect rect(0, 0, 0, 0);
	CGDIDoc *ptrDoc;
	
	::GetCursorPos(&pt);
	ScreenToClient(&pt);
	ptrDoc=(CGDIDoc *)GetDocument();
	rect.right=ptrDoc->GetTextHorSize();
	rect.bottom=ptrDoc->GetCaretVerSize();
	if(rect.PtInRect(pt) == TRUE)
	{
		::SetCursor(m_hCur);
		return TRUE;
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CGDIView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CGDIDoc *ptrDoc;
	
	ptrDoc=(CGDIDoc *)GetDocument();
	ptrDoc->ResetSelection();
	if(::GetCursor() == m_hCur)ptrDoc->SetCaret(point);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CGDIDoc *ptrDoc;
	
	ptrDoc=(CGDIDoc *)GetDocument();
	if(::GetCursor() == m_hCur)ptrDoc->SetCaret(point);
	CScrollView::OnLButtonUp(nFlags, point);
}

void CGDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CGDIDoc *ptrDoc;
	
	if(nFlags & MK_LBUTTON)
	{
		ptrDoc=(CGDIDoc *)GetDocument();
		if(::GetCursor() == m_hCur)ptrDoc->SetCaret(point);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CGDIView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CClientDC dc(this);
	CFont *ptrFontOld;
	CRect rect;
	CGDIDoc *ptrDoc;
	CString szText;
	CSize sizeExtent;
	int nIndex;
	int nSelIndexBgn;
	int nSelIndexEnd;
	int nSelIndexEndOld;
	int nSel;
	int nNum;

	if(lHint == 0)
	{
		CScrollView::OnUpdate(pSender, lHint, pHint);
		return;
	}

	ptrDoc=(CGDIDoc *)GetDocument();
	ASSERT(ptrDoc != NULL);
	ptrFontOld=dc.SelectObject(ptrDoc->GetFont());
	GetClientRect(rect);
	rect.bottom=ptrDoc->GetCaretVerSize();
	szText=ptrDoc->GetText();

	nSelIndexBgn=ptrDoc->GetSelIndexBgn();
	nSelIndexEnd=ptrDoc->GetSelIndexEnd();
	nSelIndexEndOld=ptrDoc->GetSelIndexEndOld();

	switch(lHint)
	{
		case HINT_DELCHAR_AFTER:
		case HINT_PASTE:
		case HINT_INPUT:
		{
			nIndex=ptrDoc->GetCaretIndex();
			szText=szText.Left(nIndex);
			sizeExtent=dc.GetTextExtent(szText);
			rect.left=sizeExtent.cx;
			InvalidateRect(rect);
			break;
		}
		case HINT_DELCHAR_BEFORE:
		{
			nIndex=ptrDoc->GetCaretIndex();
			if(nIndex != 0)nIndex--;
			szText=szText.Left(nIndex);
			sizeExtent=dc.GetTextExtent(szText);
			rect.left=sizeExtent.cx;
			InvalidateRect(rect);
			break;
		}
		case HINT_DELETE_SELECTION:
		{
			nIndex=min(nSelIndexBgn, nSelIndexEnd);
			szText=szText.Left(nIndex);
			sizeExtent=dc.GetTextExtent(szText);
			rect.left=sizeExtent.cx;
			InvalidateRect(rect);
			break;
		}
		case HINT_UNSELECTION:
		{
			nSelIndexBgn=ptrDoc->GetSelIndexBgnOld();
			nSelIndexEnd=ptrDoc->GetSelIndexEndOld();
			nSel=min(nSelIndexBgn, nSelIndexEnd);
			nNum=max(nSelIndexBgn, nSelIndexEnd)-nSel;
			rect.left=(dc.GetTextExtent(szText.Left(nSel))).cx;
			szText=szText.Mid(nSel, nNum);
			rect.right=(dc.GetTextExtent(szText)).cx+rect.left;
			InvalidateRect(rect, FALSE);
			break;
		}
		case HINT_SELECTION:
		{
			if(nSelIndexBgn != -1 && nSelIndexEnd != -1)
			{
				if(nSelIndexEndOld == -1)
				{
					nSel=min(nSelIndexBgn, nSelIndexEnd);
					nNum=max(nSelIndexBgn, nSelIndexEnd)-nSel;
				}
				else
				{
					nSel=min(nSelIndexEnd, nSelIndexEndOld);
					nNum=max(nSelIndexEnd, nSelIndexEndOld)-nSel;
				}
				rect.left=(dc.GetTextExtent(szText.Left(nSel))).cx;
				szText=szText.Mid(nSel, nNum);
				rect.right=(dc.GetTextExtent(szText)).cx+rect.left;
				InvalidateRect(rect, FALSE);
			}
			break;
		}
	}
	dc.SelectObject(ptrFontOld);
}
