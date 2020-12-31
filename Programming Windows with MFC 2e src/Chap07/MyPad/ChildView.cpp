// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MyPad.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_wndEdit.Create (WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |
        ES_AUTOVSCROLL, CRect (0, 0, 0, 0), this, IDC_EDIT);
	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
    m_wndEdit.MoveWindow (0, 0, cx, cy);
}

void CChildView::OnSetFocus(CWnd* pOldWnd) 
{
	m_wndEdit.SetFocus ();	
}

void CChildView::OnEditCut() 
{
	m_wndEdit.Cut ();
 }

void CChildView::OnEditCopy() 
{
	m_wndEdit.Copy ();
}

void CChildView::OnEditPaste() 
{
	m_wndEdit.Paste ();
}

void CChildView::OnEditDelete() 
{
	m_wndEdit.Clear ();
}

void CChildView::OnEditUndo() 
{
	m_wndEdit.Undo ();
}

void CChildView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsTextSelected ());
}

void CChildView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsTextSelected ());
}

void CChildView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (::IsClipboardFormatAvailable (CF_TEXT));
}

void CChildView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsTextSelected ());
}

void CChildView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_wndEdit.CanUndo ());
}

void CChildView::OnFileNew() 
{
    m_wndEdit.SetWindowText (_T (""));
}

BOOL CChildView::IsTextSelected()
{
    int nStart, nEnd;
    m_wndEdit.GetSel (nStart, nEnd);
    return (nStart != nEnd);
}
