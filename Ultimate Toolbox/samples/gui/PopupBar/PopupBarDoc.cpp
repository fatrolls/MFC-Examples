// PopupBarDoc.cpp : implementation of the CPopupBarDoc class
//

#include "stdafx.h"
#include "PopupBar.h"

#include "MainFrm.h"
#include "PopupBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupBarDoc

IMPLEMENT_DYNCREATE(CPopupBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CPopupBarDoc, CDocument)
	//{{AFX_MSG_MAP(CPopupBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupBarDoc construction/destruction

CPopupBarDoc::CPopupBarDoc()
{
	// TODO: add one-time construction code here

}

CPopupBarDoc::~CPopupBarDoc()
{
}

BOOL CPopupBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	m_clrText=GetDefaultTextColor();
	m_clrFill=GetDefaultFillColor();
	m_clrBorder=GetDefaultBorderColor();

	m_nBorderStyle=GetDefaultBorderStyle();
	m_nLineStyle=GetDefaultLineStyle();
	m_nDashStyle=GetDefaultDashStyle();

	return TRUE;
}


BOOL CPopupBarDoc::DoFileSave()
{
	if(m_strPathName.IsEmpty())
	{
		// File was created using File New
		//
		// set whatever name for the document file
		m_strPathName=_T("Document.ext");
		if (!DoSave(m_strPathName))
		{
			TRACE0("Warning: File save failed.\n");
			return FALSE;
		}
		return TRUE;
	}
	else
		return CDocument::DoFileSave();
}


/////////////////////////////////////////////////////////////////////////////
// CPopupBarDoc serialization

void CPopupBarDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << (DWORD)m_clrText;
		ar << (DWORD)m_clrFill;
		ar << (DWORD)m_clrBorder;
		ar << m_nBorderStyle;
		ar << m_nLineStyle;
		ar << m_nDashStyle;
	}
	else
	{
		// TODO: add loading code here
		ar >> (DWORD)m_clrText;
		ar >> (DWORD)m_clrFill;
		ar >> (DWORD)m_clrBorder;
		ar >> m_nBorderStyle;
		ar >> m_nLineStyle;
		ar >> m_nDashStyle;


		// check for correct values
		if((m_nBorderStyle&ID_BORDER_ALL)==0 && m_nBorderStyle!=ID_BORDER_NONE)
		{
			TRACE(_T("CPopupBarDoc::Serialize: Incorrect border style"));
			m_nBorderStyle=ID_BORDER_ALL;
		}
		if(m_nLineStyle<ID_LINE_1PX || m_nLineStyle>ID_LINE_7PX_3LINES)
		{
			TRACE(_T("CPopupBarDoc::Serialize: Incorrect line style"));
			m_nLineStyle=ID_LINE_1PX;
		}
		if(m_nDashStyle<ID_DASH_SOLID || m_nDashStyle>ID_DASH_DASHDOTDOT)
		{
			TRACE(_T("CPopupBarDoc::Serialize: Incorrect dash style"));
			m_nDashStyle=ID_DASH_SOLID;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPopupBarDoc diagnostics

#ifdef _DEBUG
void CPopupBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPopupBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

