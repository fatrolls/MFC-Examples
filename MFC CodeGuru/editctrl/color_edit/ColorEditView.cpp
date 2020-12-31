// ColorEditView.cpp : implementation of the CColorEditView class
//
//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

#include "stdafx.h"
#include "ColorEdit.h"

#include "ColorEditDoc.h"
#include "ColorEditView.h"

#include "Search.h"

#include <afxadv.h>

const int ScrollTimer = 2;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEditView

IMPLEMENT_DYNCREATE(CColorEditView, CScrollView)

BEGIN_MESSAGE_MAP(CColorEditView, CScrollView)
	//{{AFX_MSG_MAP(CColorEditView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEditView construction/destruction

CColorEditView::CColorEditView()
{
	m_tabSize = 4;
	m_indent = 10;
	m_selectStart = m_selectEnd = -1;
	m_caret = 0;
	m_mouseMove = m_mouseDown = FALSE;
	m_caretPos = CPoint(0, 0);
	m_caretVisible = FALSE;
	m_scrollTimerEnabled = FALSE;
}

CColorEditView::~CColorEditView()
{
}

BOOL CColorEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CColorEditView drawing

void CColorEditView::OnDraw(CDC* dc)
{
	CColorEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CalcScrollSize(dc);

	CMemDC			pDC(dc);
	long			lineStart, lineStop;
	LOGFONT			lf;
	CPoint			scrollPos = GetScrollPosition();
	CRect			rcBounds;


	if (pDC->IsPrinting()) {
		m_font.GetLogFont(&lf);
		CFont* oldFont = pDC->SelectObject(&m_font);

		CPoint			caret = GetCaretPos(pDC, m_indent);

		if (CPoint(caret-scrollPos) != m_caretPos) {
			m_caretPos = CPoint(caret-scrollPos);
			SetCaretPos(m_caretPos);
		}

		TRACE(_T("m_nPageStartLine = %d, m_nPageEndLine = %d, lineCount = %d\r\n"), m_nPageStartLine, m_nPageEndLine, pDoc->GetLineCount());
		for (int i = m_nPageStartLine; i < m_nPageEndLine && i < pDoc->GetLineCount(); i++) {
			DrawText(pDC, CPoint(m_indent, ((i-m_nPageStartLine)*lf.lfHeight)), i, FALSE);
		}
		pDC->SelectObject(oldFont);
	} else {

		GetClientRect(&rcBounds);

		rcBounds += scrollPos;

		pDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

		m_font.GetLogFont(&lf);
		CFont* oldFont = pDC->SelectObject(&m_font);

		CPoint			caret = GetCaretPos(pDC, m_indent);

		if (CPoint(caret-scrollPos) != m_caretPos) {
			m_caretPos = CPoint(caret-scrollPos);
			SetCaretPos(m_caretPos);
		}

		lineStart = rcBounds.top/lf.lfHeight;
		lineStop = rcBounds.bottom/lf.lfHeight+1;

		for (int i = lineStart; i < lineStop && i < pDoc->GetLineCount(); i++) {
			DrawText(pDC, CPoint(m_indent, (i*lf.lfHeight)), i);
		}
		pDC->SelectObject(oldFont);
	}

}

void CColorEditView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CWnd* desktop = (CWnd*) GetDesktopWindow();
	CDC* pDC = desktop->GetDC();
	TEXTMETRIC	tm;
	pDC->GetTextMetrics(&tm);

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	m_cHeight = lf.lfHeight = tm.tmHeight;
	strcpy(lf.lfFaceName, _T("Courier New"));
	m_font.CreateFontIndirect(&lf);

	CalcScrollSize(pDC);

	desktop->ReleaseDC(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CColorEditView printing


BOOL CColorEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CColorEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CColorEditDoc*	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int nPrinterPixCX = pDC->GetDeviceCaps(HORZRES);  
	int nPrinterPixCY = pDC->GetDeviceCaps(VERTRES);  

	int nPrinterPixPerInchX = pDC->GetDeviceCaps(LOGPIXELSX);
	int nPrinterPixPerInchY = pDC->GetDeviceCaps(LOGPIXELSY);

    CClientDC dcDisplay(this);
	int nLogPixPerInchX = dcDisplay.GetDeviceCaps(LOGPIXELSX);
	int nLogPixPerInchY = dcDisplay.GetDeviceCaps(LOGPIXELSY);

	int nPagePixWidth = (int)((DWORD)nPrinterPixCX * nLogPixPerInchX / nPrinterPixPerInchX);
	int nPagePixHeight = (int)((DWORD)nPrinterPixCY * nLogPixPerInchY / nPrinterPixPerInchY);

	m_nCurPage = pInfo->m_nCurPage;

	LOGFONT lf;
	m_font.GetLogFont(&lf);
	int nTextHeight = lf.lfHeight;
 	
 	m_nLinesPerPage = nPagePixHeight / nTextHeight - 1;
 	int nPages = (int)(pDoc->GetLineCount() / m_nLinesPerPage) + 1;
	
	m_nPageStartLine = (m_nCurPage-1)*m_nLinesPerPage;
	m_nPageEndLine = m_nPageStartLine+m_nLinesPerPage-1;

	pInfo->m_nNumPreviewPages = nPages;
	pInfo->SetMaxPage(nPages);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(nLogPixPerInchX, nLogPixPerInchY);
	pDC->SetViewportExt(nPrinterPixPerInchX, nPrinterPixPerInchY);
}

void CColorEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CColorEditView diagnostics

#ifdef _DEBUG
void CColorEditView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CColorEditView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CColorEditDoc* CColorEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorEditDoc)));
	return (CColorEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorEditView message handlers

CPoint CColorEditView::GetCaretPos(CDC * pDC, long xoffset)
{
	CColorEditDoc*	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	long		line = pDoc->Offset2Line(m_caret);
	long		col = m_caret - pDoc->GetLineOffset(line);
	CString&	string = pDoc->GetLine(line).Left(col);
	return GetExtent(pDC, string, xoffset, line);
}

CPoint CColorEditView::GetExtent(CDC * pDC, const CString & string, long xoffset, long line)
{
	CSize	size = pDC->GetTextExtent(_T(" "));
	int		x = 0, y = size.cy;
	int		tabWidth = size.cx*m_tabSize;

	for (int i = 0; i < string.GetLength(); i++) {
		TCHAR c = string[i];
		if (iswprint(c) || iswspace(c)) {
			if (c == '\t') {
				x = ((x/tabWidth)+1)*tabWidth;
			} else {
				x += pDC->GetTextExtent(c).cx;
			}
		}
	}
	return CPoint(x+xoffset, y*line);
}

CSize CColorEditView::GetScrollSize(CDC * pDC)
{
	CColorEditDoc*	pDoc = GetDocument();
	long			lineCount = pDoc->GetLineCount();
	long			width = 0;
	CString			line;
	long			x = 0;
	CSize			size = pDC->GetTextExtent(_T(" "));
	
	CFont*		oldFont = pDC->SelectObject(&m_font);
	for (long i = 0; i < lineCount; i++) {
		CString& line = pDoc->GetLine(i);
		x = GetExtent(pDC, line, m_indent*2, i).x;
		if (x > width) {
			width = x;
		}
	}
	pDC->SelectObject(oldFont);
	return CSize(width, size.cy*(lineCount+1));
}

CPoint CColorEditView::DrawText(CDC * pDC, CPoint pos, int line, BOOL bDrawSelection)
{
	CColorEditDoc*	pDoc = GetDocument();
	long		x = pos.x, y = pos.y;
	long		offset = pDoc->GetLineOffset(line);
	int			spaceWidth = GetExtent(pDC, _T(" ")).x;
	long		length = pDoc->GetLength();
	TCHAR		c;
	COLORREF	color;
	CString		string;
	long		i;

	if (offset < length) {
		for (i = offset, c = pDoc->GetAt(i), color = pDoc->GetColor(i); i < length && c != '\n'; i++, 
					c = (i < length ? pDoc->GetAt(i) : c), color = (i < length ? pDoc->GetColor(i) : color)) {
			if (bDrawSelection && i >= m_selectStart && i < m_selectEnd) {
#ifndef BLACK_BACKGROUND
				// Hilight text on selection
				pDC->SetBkColor(RGB(230, 230, 230));
				pDC->SetTextColor(color);
#else
				// Invert color on selection
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor((~color) & 0xffffff);
#endif
			} else {
				pDC->SetBkColor(RGB(255, 255, 255));
				pDC->SetTextColor(color);
			}
			
			string = c;
			if (c != '\t') pDC->TextOut(x, y, c);
			x += GetExtent(pDC, string).x;
		}
	}

	return CPoint(x, y);
}

BOOL CColorEditView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

void CColorEditView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate) {
		if (!m_caretVisible) {
			CreateSolidCaret(2, m_cHeight);
			ShowCaret();
			SetCaretPos(m_caretPos);
			m_caretVisible = TRUE;
		}
	} else {
		if (m_caretVisible) {
			HideCaret();
			m_caretVisible = FALSE;
		}
	}

	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CColorEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	long			p;
	CColorEditDoc*	pDoc = GetDocument();

	if ((p = SelectionPoint(point))  >= 0 && p < pDoc->GetLength()) {
		if (p >= 0 && p < pDoc->GetLength()) {
			if (!IsWhite(pDoc->GetAt(p))) {
				m_selectStart = m_selectEnd = p;

				while (m_selectStart > 1 && !IsWhite(pDoc->GetAt(m_selectStart-1)))
					m_selectStart--;

				while (m_selectEnd > 0 && !IsWhite(pDoc->GetAt(m_selectEnd)))
					m_selectEnd++;

				m_caret = m_selectEnd;
			}
		}

		Invalidate();
	}
}

void CColorEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	long	p;

	SetCapture();
	m_mouseDown = TRUE;
	m_mouseMove = FALSE;

	if ((p = SelectionPoint(point)) != m_caret) {
		m_caret = m_selectStart = m_selectEnd = p;
		Invalidate();
	}
}

void CColorEditView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_mouseDown = FALSE;
	m_mouseMove = FALSE;
	ReleaseCapture();
	if (m_scrollTimerEnabled) {
		m_scrollTimerEnabled = FALSE;
		KillTimer(ScrollTimer);
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CColorEditView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect	client;

	GetClientRect(&client);

	m_mouseMove = TRUE;
	m_mousePosition = point;

	if (m_mouseDown) {
		if (client.PtInRect(point)) {
			if (m_scrollTimerEnabled) {
				m_scrollTimerEnabled = FALSE;
				KillTimer(ScrollTimer);
			}
			long p = SelectionPoint(point);
			m_caret = p;
			if (p <= m_selectStart) {
				m_selectStart = p;
			} else {
				m_selectEnd = p;
			}
			Invalidate();
		} else {
			if (!m_scrollTimerEnabled) {
				m_autoScrollCount = 0;
				m_scrollTimerEnabled = TRUE;
				SetTimer(ScrollTimer, 175, NULL);
			}
		}
	} 
	
	CScrollView::OnMouseMove(nFlags, point);
}

long CColorEditView::SelectionPoint(CPoint point)
{
	LOGFONT			lf;
	CPaintDC		dc(this);

	CColorEditDoc* pDoc = GetDocument();

	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	CPoint	pos = point;

	m_font.GetLogFont(&lf);
	CFont* oldFont = dc.SelectObject(&m_font);
	CSize		size = GetExtent(&dc, _T(" "));

	long line = pos.y/size.cy;

	CString string = pDoc->GetLine(line);
	long offset = pDoc->GetLineOffset(line);

	for (int i = 0; i < string.GetLength()-1; i++) {
		CSize size = GetExtent(&dc, string.Left(i+1));
		if (pos.x-m_indent < size.cx) {
			return offset + i;
		}
	}

	dc.SelectObject(oldFont);
	return offset + string.GetLength();
}

BOOL CColorEditView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (nHitTest == HTCLIENT && pWnd == this) {
		::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
		return TRUE;   
	}
	
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CColorEditView::OnEditUndo() 
{
	CColorEditDoc* pDoc = GetDocument();
	pDoc->Undo();
	pDoc->m_text.Reset();
	Invalidate();
}

void CColorEditView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CColorEditDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanUndo());
}

void CColorEditView::OnEditRedo() 
{
	CColorEditDoc* pDoc = GetDocument();
	pDoc->Redo();
	pDoc->m_text.Reset();
	Invalidate();
}

void CColorEditView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	CColorEditDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanRedo());
}

void CColorEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CColorEditDoc*	pDoc = GetDocument();

	switch (nChar) {
	case VK_DELETE:
		if (m_selectStart != m_selectEnd && m_selectStart >= 0) {
			pDoc->m_text.Delete(m_selectStart, m_selectEnd-m_selectStart);
			m_caret = m_selectEnd = m_selectStart;
		} else if (m_caret >= 0 && pDoc->m_text.GetLength() > m_caret+1) {
			pDoc->m_text.Delete(m_caret, 1);
		}
		pDoc->SetModifiedFlag();
		pDoc->CheckPoint();
		CalcScrollSize();
		Invalidate();
		break;
	case VK_BACK:
		if (m_selectStart != m_selectEnd && m_selectStart >= 0) {
			pDoc->m_text.Delete(m_selectStart, m_selectEnd-m_selectStart);
			m_caret = m_selectEnd = m_selectStart;
		} else if (m_caret > 0) {
			m_caret -= 1;
			pDoc->m_text.Delete(m_caret, 1);
		}
		pDoc->SetModifiedFlag();
		pDoc->CheckPoint();
		CalcScrollSize();
		Invalidate();
		break;
	case VK_RETURN:
		pDoc->m_text.Insert(m_caret, _T('\n'));
		m_caret += 1;
		pDoc->SetModifiedFlag();
		pDoc->CheckPoint();
		CalcScrollSize();
		Invalidate();
		break;
	case VK_END:
		m_caret = pDoc->m_text.GetLength()-1;
		ScrollToCaret();
		break;
	case VK_HOME:
		m_caret = 0;
		ScrollToCaret();
		break;
	case VK_LEFT:
		if (m_caret > 0) {
			m_caret--;
			ScrollToCaret();
		}
		break;
	case VK_RIGHT:
		if (m_caret < pDoc->m_text.GetLength()-1) {
			m_caret++;
			ScrollToCaret();
		}
		break;
	case VK_UP:
		{
			long line = pDoc->Offset2Line(m_caret);
			long lineoffset = pDoc->GetLineOffset(line);
			long pos = m_caret - lineoffset;

			if (line > 0) {
				long prevLine = pDoc->GetLineOffset(line-1);
				long prevLineLen = pDoc->GetLine(line-1).GetLength();

				if (pos < prevLineLen) {
					m_caret = prevLine + pos;
				} else {
					m_caret = prevLine + prevLineLen;
				}

				ScrollToCaret();
			}
		}
		break;
	case VK_DOWN:
		{
			long line = pDoc->Offset2Line(m_caret);
			long lineoffset = pDoc->GetLineOffset(line);
			long pos = m_caret - lineoffset;
			long lineCount = pDoc->GetLineCount();

			if (line < lineCount-1) {
				long nextLine = pDoc->GetLineOffset(line+1);
				long nextLineLen = pDoc->GetLine(line+1).GetLength();

				if (pos < nextLineLen) {
					m_caret = nextLine + pos;
				} else {
					m_caret = nextLine + nextLineLen;
				}

				ScrollToCaret();
			}
		}
		break;
		break;
	default:
		CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CColorEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CColorEditDoc*	pDoc = GetDocument();

	if (iswprint(nChar)) {
		pDoc->m_text.Insert(m_caret, nChar);
		m_caret += 1;
		pDoc->SetModifiedFlag();
		pDoc->CheckPoint();
		CalcScrollSize();
		Invalidate();
	} 
}

void CColorEditView::CalcScrollSize(CDC * pDC)
{
	if (pDC == NULL) {
		LOGFONT			lf;
		CPaintDC		dc(this);
		OnPrepareDC(&dc);
		m_font.GetLogFont(&lf);
		CFont* oldFont = dc.SelectObject(&m_font);
		m_scrollSize = GetScrollSize(&dc);
		CSize status = dc.SetWindowExt(m_scrollSize);
		ASSERT(status != CSize(0, 0));

		SetScrollSizes(MM_TEXT, m_scrollSize);
		dc.SelectObject(oldFont);

		ASSERT(m_scrollSize == GetTotalSize());
	} else {
		m_scrollSize = GetScrollSize(pDC);
		CSize status = pDC->SetWindowExt(m_scrollSize);
		ASSERT(status != CSize(0, 0));
		SetScrollSizes(MM_TEXT, m_scrollSize);

		ASSERT(m_scrollSize == GetTotalSize());
	}
}

long CColorEditView::CurrentPosition()
{
	return m_caret;
}


void CColorEditView::SetCurrentPosition(long position)
{
	CColorEditDoc* pDoc = GetDocument();
	if (position > 0 && position < pDoc->GetLength()) {
		m_caret = position;
		ScrollToCurrent();
	}
}

void CColorEditView::ScrollToCurrent()
{
	LOGFONT			lf;
	CPaintDC		dc(this);
	CRect			client;
	CPoint			scrollPos = GetScrollPosition();

	CColorEditDoc* pDoc = GetDocument();

	OnPrepareDC(&dc);

	m_font.GetLogFont(&lf);
	CFont* oldFont = dc.SelectObject(&m_font);

	GetClientRect(&client);

	client += scrollPos;
	CPoint caret = TextPosition2ScreenCoord(&dc, m_caret);
	long x = scrollPos.x;
	long y = scrollPos.y;

	if (caret.y > client.bottom) {
		y = caret.y-client.Height()/2;
	} else if (caret.y < client.top) {
		y = caret.y-client.Height()/2;
	}

	if (caret.x < client.left) {
		if (caret.x < client.Width()) {
			x = 0;
		} else {
			x = caret.x-client.Width()/2;
		}
	} else if (caret.x > client.right) {
		if (caret.x < client.Width()) {
			x = 0;
		} else {
			x = caret.x-client.Width()/2;
		}
	}

	dc.SelectObject(oldFont);

	ScrollToPosition(CPoint(x, y));

	Invalidate();
}

void CColorEditView::SetSelection(long start, long end)
{
	if (start < end) {
		m_selectStart = start;
		m_caret = m_selectEnd = end;
	} else {
		m_caret = m_selectStart = end;
		m_selectEnd = start;
	}
}

void CColorEditView::ScrollToCaret()
{
	LOGFONT			lf;
	CPaintDC		dc(this);
	CRect			client;
	CPoint			scrollPos = GetScrollPosition();

	CColorEditDoc* pDoc = GetDocument();

	OnPrepareDC(&dc);

	m_font.GetLogFont(&lf);
	CFont* oldFont = dc.SelectObject(&m_font);

	GetClientRect(&client);

	client += scrollPos;
	CPoint caret = TextPosition2ScreenCoord(&dc, m_caret);
	long x = scrollPos.x;
	long y = scrollPos.y;

	if (caret.y > client.bottom) {
		y = caret.y-client.Height()/2;
	} else if (caret.y < client.top) {
		y = caret.y-client.Height()/2;
	}

	if (caret.x < client.left) {
		if (caret.x < client.Width()) {
			x = 0;
		} else {
			x = caret.x-client.Width()/2;
		}
	} else if (caret.x > client.right) {
		if (caret.x < client.Width()) {
			x = 0;
		} else {
			x = caret.x-client.Width()/2;
		}
	}

	dc.SelectObject(oldFont);

	ScrollToPosition(CPoint(x, y));

	Invalidate();
}

void CColorEditView::ScrollToSelection()
{
	LOGFONT			lf;
	CPaintDC		dc(this);
	CRect			client;
	CPoint			scrollPos = GetScrollPosition();

	CColorEditDoc* pDoc = GetDocument();

	OnPrepareDC(&dc);

	m_font.GetLogFont(&lf);
	CFont* oldFont = dc.SelectObject(&m_font);

	GetClientRect(&client);

	client += scrollPos;
	CPoint selectEnd = TextPosition2ScreenCoord(&dc, m_selectEnd);
	long x = scrollPos.x;
	long y = scrollPos.y;

	if (selectEnd.y > client.bottom) {
		y = selectEnd.y-client.Height()/2;
	} else if (selectEnd.y < client.top) {
		y = selectEnd.y-client.Height()/2;
	}

	if (selectEnd.x < client.left) {
		if (selectEnd.x < client.Width()) {
			x = 0;
		} else {
			x = selectEnd.x-client.Width()/2;
		}
	} else if (selectEnd.x > client.right) {
		if (selectEnd.x < client.Width()) {
			x = 0;
		} else {
			x = selectEnd.x-client.Width()/2;
		}
	}

	dc.SelectObject(oldFont);

	ScrollToPosition(CPoint(x, y));

	Invalidate();
}

long CColorEditView::GetSearchPosition()
{
	if (m_selectEnd >= 0) {
		return m_selectEnd;
	}
	return CurrentPosition();
}

CPoint CColorEditView::TextPosition2ScreenCoord(CDC* pDC, long pos)
{
	CColorEditDoc*	pDoc = GetDocument();
	long		line = pDoc->m_text.Offset2Line(pos);
	long		offset = pDoc->GetLineOffset(line);
	CString		string = pDoc->m_text.Mid(offset, pos-offset);
	return CPoint(GetExtent(pDC, string).x+m_indent, GetExtent(pDC, _T(" ")).y*line);
}

BOOL CColorEditView::ReplaceSelection(CString string)
{
	CColorEditDoc*	pDoc = GetDocument();
	if (m_selectStart != m_selectEnd) {
		pDoc->m_text.Replace(m_selectStart, m_selectEnd - m_selectStart, string);
		m_caret = m_selectEnd = m_selectStart;
		pDoc->CheckPoint();
		CalcScrollSize();
		Invalidate();
		return TRUE;
	}
	return FALSE;
}

void CColorEditView::OnEditFind() 
{
	CColorEditDoc* pDoc = GetDocument();
	CSearch	dlg;
	dlg.m_pString = &pDoc->m_text;
	dlg.m_view = this;
	dlg.m_search_string = pDoc->Range(m_selectStart, m_selectEnd);
	dlg.DoModal();
	CreateSolidCaret(2, m_cHeight);
	ShowCaret();
	ScrollToCurrent();
	pDoc->UpdateAllViews(NULL);	
}

void CColorEditView::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	CColorEditDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetLength() > 0);	
}

void CColorEditView::DisableCheckPoint()
{
	CColorEditDoc* pDoc = GetDocument();
	pDoc->DisableCheckPoint();
}

void CColorEditView::EnableCheckPoint()
{
	CColorEditDoc* pDoc = GetDocument();
	pDoc->EnableCheckPoint();
}

void CColorEditView::CheckPoint()
{
	CColorEditDoc* pDoc = GetDocument();
	pDoc->CheckPoint();
}

void CColorEditView::OnEditCopy() 
{
	CColorEditDoc* pDoc = GetDocument();
	CString text = pDoc->Range(m_selectStart, m_selectEnd);	

	COleDataSource*	pSource = new COleDataSource();
	CSharedFile		sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
	sf.Write(text, text.GetLength());
	HGLOBAL hMem = sf.Detach();
	if (!hMem) return;
	pSource->CacheGlobalData(CF_TEXT, hMem);
	pSource->SetClipboard();
}

void CColorEditView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selectStart < m_selectEnd);
}

void CColorEditView::OnEditCut() 
{
	CColorEditDoc* pDoc = GetDocument();
	CString text = pDoc->Range(m_selectStart, m_selectEnd);	

	COleDataSource*	pSource = new COleDataSource();
	CSharedFile		sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
	sf.Write(text, text.GetLength());
	HGLOBAL hMem = sf.Detach();
	if (!hMem) return;
	pSource->CacheGlobalData(CF_TEXT, hMem);
	pSource->SetClipboard();
	ReplaceSelection(_T(""));
}

void CColorEditView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selectStart < m_selectEnd);
}

void CColorEditView::OnEditPaste() 
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

			if (m_selectStart < m_selectEnd) {
				ReplaceSelection(buffer);
			} else {
				CColorEditDoc*	pDoc = GetDocument();
				pDoc->m_text.Insert(m_caret, buffer);
				pDoc->CheckPoint();
				CalcScrollSize();
				Invalidate();
			}
		}
	}
	
}

void CColorEditView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	COleDataObject	obj;
	obj.AttachClipboard();
	pCmdUI->Enable(obj.IsDataAvailable(CF_TEXT));
}

void CColorEditView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	if (pDC->IsPrinting()) {
		CColorEditDoc*	pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		int nPrinterPixCX = pDC->GetDeviceCaps(HORZRES);  
		int nPrinterPixCY = pDC->GetDeviceCaps(VERTRES);  

		int nPrinterPixPerInchX = pDC->GetDeviceCaps(LOGPIXELSX);
		int nPrinterPixPerInchY = pDC->GetDeviceCaps(LOGPIXELSY);

		CClientDC dcDisplay(this);
		int nLogPixPerInchX = dcDisplay.GetDeviceCaps(LOGPIXELSX);
		int nLogPixPerInchY = dcDisplay.GetDeviceCaps(LOGPIXELSY);

		int nPagePixWidth = (int)((DWORD)nPrinterPixCX * nLogPixPerInchX / nPrinterPixPerInchX);
		int nPagePixHeight = (int)((DWORD)nPrinterPixCY * nLogPixPerInchY / nPrinterPixPerInchY);
		
		m_nCurPage = pInfo->m_nCurPage;

		LOGFONT lf;
		m_font.GetLogFont(&lf);
		int nTextHeight = lf.lfHeight;
 		
 		m_nLinesPerPage = nPagePixHeight / nTextHeight - 1;

		TRACE("m_nLinesPerPage = %d\r\n", m_nLinesPerPage);
		
		m_nPageStartLine = (m_nCurPage-1)*m_nLinesPerPage;
		m_nPageEndLine = m_nPageStartLine+m_nLinesPerPage-1;

		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(nLogPixPerInchX, nLogPixPerInchY);
		pDC->SetViewportExt(nPrinterPixPerInchX, nPrinterPixPerInchY);
	} else {
		CScrollView::OnPrepareDC(pDC, pInfo);
	}
}


void CColorEditView::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == ScrollTimer) {
		AutoScroll();
		return;
	} 
	CScrollView::OnTimer(nIDEvent);
}

void CColorEditView::AutoScroll()
{
	CRect	client;
	GetClientRect(&client);

	if (client.PtInRect(m_mousePosition)) return;
	long p = SelectionPoint(m_mousePosition);
	m_caret = p;
	if (p <= m_selectStart) {
		m_selectStart = p;
	} else {
		m_selectEnd = p;
	}
	SetCurrentPosition(p);
	TRACE(_T("AutoScroll(%d)\r\n"), m_autoScrollCount++);
}

