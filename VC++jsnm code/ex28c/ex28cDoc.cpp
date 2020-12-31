// ex28cDoc.cpp : implementation of the CEx28cDoc class
//

#include "stdafx.h"
#include "ex28c.h"

#include "ex28cSet.h"
#include "ex28cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc

IMPLEMENT_DYNCREATE(CEx28cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc construction/destruction

CEx28cDoc::CEx28cDoc()
{
	m_pEx28cSet = NULL;
}

CEx28cDoc::~CEx28cDoc()
{
}

BOOL CEx28cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if(m_pEx28cSet == NULL) {
		m_pEx28cSet = new CEx28cSet(&m_database);
		CString strConnect = m_pEx28cSet->GetDefaultConnect();
		m_database.Open(NULL, FALSE, FALSE, strConnect, FALSE);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc diagnostics

#ifdef _DEBUG
void CEx28cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc commands
