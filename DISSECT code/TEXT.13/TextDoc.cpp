// TextDoc.cpp : implementation of the CTextDoc class
//

#include "stdafx.h"
#include "Text.h"

#include "TextDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDoc

IMPLEMENT_DYNCREATE(CTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextDoc, CDocument)
	//{{AFX_MSG_MAP(CTextDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDoc construction/destruction

CTextDoc::CTextDoc()
{
	// TODO: add one-time construction code here

}

CTextDoc::~CTextDoc()
{
}

BOOL CTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_stringArray.SetSize(10);
	m_stringArray[0] = "If you love me let me know,  ";
	m_stringArray[1] = "if you don't then let me go, ";
	m_stringArray[2] = "I can take another minute    ";
	m_stringArray[3] = "  of day without you in it.  ";
	m_stringArray[4] = "                             ";
	m_stringArray[5] = "If you love me let it be,    ";
	m_stringArray[6] = "if you don't then set me free";
	m_stringArray[7] = "...                          ";
	m_stringArray[8] = "SORRY, I FORGET IT!          ";
	m_stringArray[9] = "           J.J.Hou 1995.03.22  19:26";

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTextDoc serialization

void CTextDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTextDoc diagnostics

#ifdef _DEBUG
void CTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextDoc commands
