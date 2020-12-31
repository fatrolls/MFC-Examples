#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "StyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	ON_COMMAND(ID_FONT_SELECT, OnFontSelect)
	ON_COMMAND(ID_FONT_STYLE, OnFontStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	LOGFONT lf;
	CClientDC dc(NULL);
	CFont *ptrFt;

	ptrFt=dc.GetCurrentFont();
	ptrFt->GetLogFont(&lf);
	ASSERT(m_fontDraw.CreateFontIndirect(&lf));
	m_colorFont=RGB(0, 0, 0);
	m_bTransparentBgd=TRUE;
}

CGDIDoc::~CGDIDoc()
{
}

BOOL CGDIDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

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

void CGDIDoc::OnFontSelect()
{
	CFontDialog dlg;
	LOGFONT lf;
	
	if(dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		if(m_fontDraw.GetSafeHandle() != NULL)m_fontDraw.DeleteObject();
		ASSERT(m_fontDraw.CreateFontIndirect(&lf));
		m_colorFont=dlg.GetColor();
		UpdateAllViews(NULL);
	}
}

void CGDIDoc::OnFontStyle() 
{
	LOGFONT lf;
	CStyleDlg dlg;

	m_fontDraw.GetLogFont(&lf);
	dlg.m_lEsp=lf.lfEscapement;
	dlg.m_bBgdStyle=m_bTransparentBgd;
	if(dlg.DoModal() == IDOK)
	{
		lf.lfOrientation=lf.lfEscapement=dlg.m_lEsp;
		m_bTransparentBgd=dlg.m_bBgdStyle;
		if(m_fontDraw.GetSafeHandle() != NULL)m_fontDraw.DeleteObject();
		ASSERT(m_fontDraw.CreateFontIndirect(&lf));
		UpdateAllViews(NULL);
	}
}
