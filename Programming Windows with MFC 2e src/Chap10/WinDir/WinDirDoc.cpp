// WinDirDoc.cpp : implementation of the CWinDirDoc class
//

#include "stdafx.h"
#include "WinDir.h"

#include "WinDirDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinDirDoc

IMPLEMENT_DYNCREATE(CWinDirDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinDirDoc, CDocument)
	//{{AFX_MSG_MAP(CWinDirDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinDirDoc construction/destruction

CWinDirDoc::CWinDirDoc()
{
	// TODO: add one-time construction code here

}

CWinDirDoc::~CWinDirDoc()
{
}

BOOL CWinDirDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWinDirDoc serialization

void CWinDirDoc::Serialize(CArchive& ar)
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
// CWinDirDoc diagnostics

#ifdef _DEBUG
void CWinDirDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinDirDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinDirDoc commands
