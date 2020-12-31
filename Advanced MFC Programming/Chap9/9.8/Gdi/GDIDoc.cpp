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
	m_nSelIndexBgn=-1;
	m_nSelIndexEnd=-1;
}

CGDIDoc::~CGDIDoc()
{
}

BOOL CGDIDoc::OnNewDocument()
{
	CClientDC dc(NULL);
	LOGFONT lf;
	CFont *ptrFont;
	CSize sizeExtent;

	if(!CDocument::OnNewDocument())return FALSE;
	ptrFont=dc.GetCurrentFont();
	ptrFont->GetLogFont(&lf);
	VERIFY(m_ftDraw.CreateFontIndirect(&lf));
	sizeExtent=dc.GetTextExtent(m_szText);
	m_nCaretVerSize=sizeExtent.cy;
	m_nTextHorSize=sizeExtent.cx;

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
	CClientDC dc(NULL);
	CFont *ptrFtOld;
	CSize sizeExtent;
	
	if(dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		m_ftDraw.DeleteObject();
		VERIFY(m_ftDraw.CreateFontIndirect(&lf));
		ptrFtOld=dc.SelectObject(&m_ftDraw);
		sizeExtent=dc.GetTextExtent(m_szText);
		dc.SelectObject(ptrFtOld);
		m_nCaretVerSize=sizeExtent.cy;
		m_nTextHorSize=sizeExtent.cx;
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

void CGDIDoc::HomeCaret()
{
	m_nCaretIndex=0;
	GetCGDIView()->RedrawCaret();
}

void CGDIDoc::EndCaret()
{
	m_nCaretIndex=m_szText.GetLength();
	GetCGDIView()->RedrawCaret();
}

void CGDIDoc::ForwardCaretToBlank()
{
	CString szSub;
	int nFwd;

	szSub=m_szText.Right(m_szText.GetLength()-m_nCaretIndex);
	nFwd=szSub.Find(' ');
	if(nFwd == -1)EndCaret();
	else
	{
		m_nCaretIndex+=nFwd+1;
		GetCGDIView()->RedrawCaret();
	}
}

void CGDIDoc::BackwardCaretToBlank()
{
	CString szSub;
	int nBkd;

	szSub=m_szText.Left(m_nCaretIndex-1);
	nBkd=szSub.ReverseFind(' ');
	if(nBkd == -1)HomeCaret();
	else
	{
		m_nCaretIndex-=szSub.GetLength()-nBkd;
		GetCGDIView()->RedrawCaret();
	}
}

void CGDIDoc::SetCaret(CPoint point)
{
	int nFinalDist;
	int nDist;
	int nIndex;
	int nStrLen;
	int i;
	CString szStr;
	CFont *ptrFtOld;
	CSize sizeExtent;
	CClientDC dc(NULL);


	ptrFtOld=dc.SelectObject(&m_ftDraw);
	nStrLen=m_szText.GetLength();
	nIndex=0;
	nFinalDist=point.x;
	for(i=1; i<=nStrLen; i++)
	{
		szStr=m_szText.Left(i);
		sizeExtent=dc.GetTextExtent(szStr);
		nDist=abs(point.x-sizeExtent.cx);
		if(nDist < nFinalDist)
		{
			nFinalDist=nDist;
			nIndex=i;
		}
	}
	dc.SelectObject(ptrFtOld);
	m_nCaretIndex=nIndex;
	if(m_nSelIndexBgn == -1)m_nSelIndexBgn=m_nCaretIndex;
	else
	{
		m_nSelIndexEnd=m_nCaretIndex;
		UpdateAllViews(NULL);
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

void CGDIDoc::AddChar(UINT uChar, UINT uRepCnt)
{
	CString szStr;
	UINT i;

	szStr=m_szText;
	m_szText=m_szText.Left(m_nCaretIndex);
	szStr=szStr.Right(szStr.GetLength()-m_nCaretIndex);
	for(i=0; i<uRepCnt; i++)m_szText+=(TCHAR)uChar;
	m_szText+=szStr;
	UpdateAllViews(NULL);
	ForwardCaret();
}

void CGDIDoc::DeleteChar(BOOL bBefore)
{
	CString szStr;

	if(bBefore == TRUE)
	{
		if(m_nCaretIndex != 0)
		{
			szStr=m_szText;
			m_szText=m_szText.Left(m_nCaretIndex-1);
			szStr=szStr.Right(szStr.GetLength()-m_nCaretIndex);
			m_szText+=szStr;
			UpdateAllViews(NULL);
			BackwardCaret();
		}
	}
	else
	{
		if(m_nCaretIndex != m_szText.GetLength())
		{
			szStr=m_szText;
			m_szText=m_szText.Left(m_nCaretIndex);
			szStr=szStr.Right(szStr.GetLength()-m_nCaretIndex-1);
			m_szText+=szStr;
			UpdateAllViews(NULL);
		}
	}
}
