// MyWordView.cpp : implementation of the CMyWordView class
//

#include "stdafx.h"
#include "MyWord.h"

#include "MyWordDoc.h"
#include "CntrItem.h"
#include "MyWordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWordView

IMPLEMENT_DYNCREATE(CMyWordView, CRichEditView)

BEGIN_MESSAGE_MAP(CMyWordView, CRichEditView)
	//{{AFX_MSG_MAP(CMyWordView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_CHAR_BOLD, OnCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, OnCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, OnCharUnderline)
	ON_COMMAND(ID_PARA_LEFT, OnParaLeft)
	ON_COMMAND(ID_PARA_CENTER, OnParaCenter)
	ON_COMMAND(ID_PARA_RIGHT, OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_CHAR_BOLD, OnUpdateCharBold)
	ON_UPDATE_COMMAND_UI(ID_CHAR_ITALIC, OnUpdateCharItalic)
	ON_UPDATE_COMMAND_UI(ID_CHAR_UNDERLINE, OnUpdateCharUnderline)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, OnUpdateParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, OnUpdateParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, OnUpdateParaRight)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLineNumber)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWordView construction/destruction

CMyWordView::CMyWordView()
{
}

CMyWordView::~CMyWordView()
{
}

BOOL CMyWordView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRichEditView::PreCreateWindow(cs);
}

void CMyWordView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

    CHARFORMAT cf;
    cf.cbSize = sizeof (CHARFORMAT);
    cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE |
        CFM_PROTECTED | CFM_STRIKEOUT | CFM_FACE | CFM_SIZE;
    cf.dwEffects = 0;
    cf.yHeight = 240; // 240 twips == 12 points
    ::lstrcpy (cf.szFaceName, _T ("Times New Roman"));
    SetCharFormat (cf);
}

void CMyWordView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CMyWordView diagnostics

#ifdef _DEBUG
void CMyWordView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMyWordView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CMyWordDoc* CMyWordView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWordDoc)));
	return (CMyWordDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWordView message handlers

void CMyWordView::OnCharBold() 
{
    CHARFORMAT cf;
    cf = GetCharFormatSelection ();

    if (!(cf.dwMask & CFM_BOLD) || !(cf.dwEffects & CFE_BOLD))
        cf.dwEffects = CFE_BOLD;
    else
        cf.dwEffects = 0;

    cf.dwMask = CFM_BOLD;
    SetCharFormat (cf);
}

void CMyWordView::OnCharItalic() 
{
    CHARFORMAT cf;
    cf = GetCharFormatSelection ();

    if (!(cf.dwMask & CFM_ITALIC) || !(cf.dwEffects & CFE_ITALIC))
        cf.dwEffects = CFE_ITALIC;
    else
        cf.dwEffects = 0;

    cf.dwMask = CFM_ITALIC;
    SetCharFormat (cf);
}

void CMyWordView::OnCharUnderline() 
{
    CHARFORMAT cf;
    cf = GetCharFormatSelection ();

    if (!(cf.dwMask & CFM_UNDERLINE) || !(cf.dwEffects & CFE_UNDERLINE))
        cf.dwEffects = CFE_UNDERLINE;
    else
        cf.dwEffects = 0;

    cf.dwMask = CFM_UNDERLINE;
    SetCharFormat (cf);
}

void CMyWordView::OnParaLeft() 
{
    OnParaAlign (PFA_LEFT);
}

void CMyWordView::OnParaCenter() 
{
    OnParaAlign (PFA_CENTER);
}

void CMyWordView::OnParaRight() 
{
    OnParaAlign (PFA_RIGHT);
}

void CMyWordView::OnUpdateCharBold(CCmdUI* pCmdUI) 
{
    OnUpdateCharEffect (pCmdUI, CFM_BOLD, CFE_BOLD);
}

void CMyWordView::OnUpdateCharItalic(CCmdUI* pCmdUI) 
{
    OnUpdateCharEffect (pCmdUI, CFM_ITALIC, CFE_ITALIC);
}

void CMyWordView::OnUpdateCharUnderline(CCmdUI* pCmdUI) 
{
    OnUpdateCharEffect (pCmdUI, CFM_UNDERLINE, CFE_UNDERLINE);
}

void CMyWordView::OnUpdateParaLeft(CCmdUI* pCmdUI) 
{
    OnUpdateParaAlign (pCmdUI, PFA_LEFT);
}

void CMyWordView::OnUpdateParaCenter(CCmdUI* pCmdUI) 
{
    OnUpdateParaAlign (pCmdUI, PFA_CENTER);
}

void CMyWordView::OnUpdateParaRight(CCmdUI* pCmdUI) 
{
    OnUpdateParaAlign (pCmdUI, PFA_RIGHT);
}

void CMyWordView::OnUpdateLineNumber(CCmdUI* pCmdUI)
{
    int nLine = GetRichEditCtrl ().LineFromChar (-1) + 1;

    CString string;
    string.Format (_T ("Line %d"), nLine);
    pCmdUI->Enable (TRUE);
    pCmdUI->SetText (string);
}

void CMyWordView::ChangeFont(LPCTSTR pszFaceName)
{
    CHARFORMAT cf;
    cf.cbSize = sizeof (CHARFORMAT);
    cf.dwMask = CFM_FACE;
    ::lstrcpy (cf.szFaceName, pszFaceName);
    SetCharFormat (cf);
}

void CMyWordView::ChangeFontSize(int nSize)
{
    CHARFORMAT cf;
    cf.cbSize = sizeof (CHARFORMAT);
    cf.dwMask = CFM_SIZE;
    cf.yHeight = nSize;
    SetCharFormat (cf);
}

void CMyWordView::GetFontInfo(LPTSTR pszFaceName, int& nSize)
{
    CHARFORMAT cf = GetCharFormatSelection ();
    ::lstrcpy (pszFaceName, cf.dwMask & CFM_FACE ? cf.szFaceName : _T (""));
    nSize = cf.dwMask & CFM_SIZE ? cf.yHeight : -1; 
}
