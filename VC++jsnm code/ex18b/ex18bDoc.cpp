// ex18bDoc.cpp : implementation of the CEx18bDoc class
//

#include "stdafx.h"
#include "ex18b.h"

#include "ex18bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc

IMPLEMENT_DYNCREATE(CEx18bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx18bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx18bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc construction/destruction

CEx18bDoc::CEx18bDoc()
{
	// TODO: add one-time construction code here

}

CEx18bDoc::~CEx18bDoc()
{
}

BOOL CEx18bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	int n1, n2, n3;
	// Make 50 random circles
	srand((unsigned) time(NULL));
	m_ellipseArray.SetSize(nMaxEllipses);

	for (int i=0; i< nMaxEllipses; i++) {
		n1 = rand() * 600 / RAND_MAX;
		n2 = rand() * 600 / RAND_MAX;
		n3 = rand() * 50  / RAND_MAX;
		m_ellipseArray[i] = CRect(n1, -n2, n1+n3, -(n2 + n3));
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc serialization

void CEx18bDoc::Serialize(CArchive& ar)
{
	m_ellipseArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc diagnostics

#ifdef _DEBUG
void CEx18bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx18bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc commands
