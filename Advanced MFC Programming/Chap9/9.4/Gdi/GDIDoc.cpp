#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"

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
}

CGDIDoc::~CGDIDoc()
{
}

BOOL CGDIDoc::OnNewDocument()
{
	CClientDC dc(NULL);
	LOGFONT lf;
	CFont *ptrFont;

	if(!CDocument::OnNewDocument())return FALSE;
	ptrFont=dc.GetCurrentFont();
	ptrFont->GetLogFont(&lf);
	VERIFY(m_ftDraw.CreateFontIndirect(&lf));
	
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
	
	if(dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		m_ftDraw.DeleteObject();
		VERIFY(m_ftDraw.CreateFontIndirect(&lf));
		UpdateAllViews(NULL);
	}
}
