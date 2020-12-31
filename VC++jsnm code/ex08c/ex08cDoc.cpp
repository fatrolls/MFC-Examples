// ex08cDoc.cpp : implementation of the CEx08cDoc class
//

#include "stdafx.h"
#include "ex08c.h"

#include "ex08cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08cDoc

const char CEx08cDoc::s_profileInternet[] = "Internet"; // section name
const char CEx08cDoc::s_profileURLBrowse[] = "URLBrowse";
const char CEx08cDoc::s_profileURLSearch[] = "URLSearch";
const char CEx08cDoc::s_engineAltavista[] = "http://altavista.digital.com/";
const char CEx08cDoc::s_engineMagellan[] = "http://magellan.mckinley.com/";
const char CEx08cDoc::s_engineMicrosoft[] = "http://www.microsoft.com/Search/default.asp";
const char CEx08cDoc::s_engineYahoo[] = "http://www.yahoo.com/";

IMPLEMENT_DYNCREATE(CEx08cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx08cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx08cDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08cDoc construction/destruction

CEx08cDoc::CEx08cDoc()
{
	m_bSearchBackForward = FALSE;
	m_bSearchBusy = FALSE;
}

CEx08cDoc::~CEx08cDoc()
{
}

BOOL CEx08cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx08cDoc serialization

void CEx08cDoc::Serialize(CArchive& ar)
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
// CEx08cDoc diagnostics

#ifdef _DEBUG
void CEx08cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx08cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08cDoc commands
