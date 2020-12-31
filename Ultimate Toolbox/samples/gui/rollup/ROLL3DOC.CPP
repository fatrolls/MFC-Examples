// Roll3doc.cpp : implementation of the CRoll32Doc class
//

#include "stdafx.h"
#include "Roll32.h"

#include "Roll3doc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoll32Doc

IMPLEMENT_DYNCREATE(CRoll32Doc, CDocument)

BEGIN_MESSAGE_MAP(CRoll32Doc, CDocument)
	//{{AFX_MSG_MAP(CRoll32Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoll32Doc construction/destruction

CRoll32Doc::CRoll32Doc()
{
	// TODO: add one-time construction code here
	m_strTestText = _T("For Rollup with a big caption, double-click view! For a small caption, look at the view menu");
}

CRoll32Doc::~CRoll32Doc()
{
}

BOOL CRoll32Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRoll32Doc serialization

void CRoll32Doc::Serialize(CArchive& ar)
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
// CRoll32Doc diagnostics

#ifdef _DEBUG
void CRoll32Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRoll32Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoll32Doc commands
