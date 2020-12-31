#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	ON_COMMAND(ID_DIALOG_FONT, OnDialogFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	m_szText="This is just a test string";
	m_nCaretIndex=0;
}

CGDIDoc::~CGDIDoc()
{
}

BOOL CGDIDoc::OnNewDocument()
{
	CClientDC dc(NULL);
	LOGFONT lf;
	CFont *ptrFont;
	TEXTMETRIC tm;

	if(!CDocument::OnNewDocument())return FALSE;
	ptrFont=dc.GetCurrentFont();
	ptrFont->GetLogFont(&lf);
	VERIFY(m_ftDraw.CreateFontIndirect(&lf));
	dc.GetOutputTextMetrics(&tm);
	m_nCaretVerSize=tm.tmHeight;
	
	return TRUE;
}

void CGDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CGDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CGDIDoc::OnDialogFont() 
{
	CFontDialog dlg;
	LOGFONT lf;
	TEXTMETRIC tm;
	CClientDC dc(NULL);
	CFont *ptrFtOld;
	
	if(dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		m_ftDraw.DeleteObject();
		VERIFY(m_ftDraw.CreateFontIndirect(&lf));
		ptrFtOld=dc.SelectObject(&m_ftDraw);
		dc.GetOutputTextMetrics(&tm);
		dc.SelectObject(ptrFtOld);
		m_nCaretVerSize=tm.tmHeight;
		GetCGDIView()->CreateNewCaret(TRUE);
		UpdateAllViews(NULL);
	}
}

POINT CGDIDoc::GetCaretPosition()
{
	POINT pt;
	CClientDC dc(NULL);
	CFont *ptrFtOld;
	CString szStr;
	CSize sizeExtent;
	
	ASSERT(m_ftDraw.GetSafeHandle());
	ptrFtOld=dc.SelectObject(&m_ftDraw);
	szStr=m_szText.Left(m_nCaretIndex);
	sizeExtent=dc.GetTextExtent(szStr);
	dc.SelectObject(ptrFtOld);

	pt.x=sizeExtent.cx;
	pt.y=0;
	return pt;
}

void CGDIDoc::ForwardCaret()
{
	m_nCaretIndex++;
	if(m_nCaretIndex > m_szText.GetLength())
	{
		m_nCaretIndex=m_szText.GetLength();
	}
	GetCGDIView()->RedrawCaret();
}

void CGDIDoc::BackwardCaret()
{
	m_nCaretIndex--;
	if(m_nCaretIndex < 0)
	{
		m_nCaretIndex=0;
	}
	GetCGDIView()->RedrawCaret();
}

CGDIView *CGDIDoc::GetCGDIView()
{
	POSITION pos;
	CGDIView *ptrView;

	pos=GetFirstViewPosition();
	do
	{
		ptrView=(CGDIView *)GetNextView(pos);
	}while(!ptrView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	return ptrView;
}