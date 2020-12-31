// HtmlClockDoc.cpp : implementation of the CHtmlClockDoc class
//

#include "stdafx.h"
#include "HtmlClock.h"

#include "HtmlClockDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockDoc

IMPLEMENT_DYNCREATE(CHtmlClockDoc, CDocument)

BEGIN_MESSAGE_MAP(CHtmlClockDoc, CDocument)
	//{{AFX_MSG_MAP(CHtmlClockDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockDoc construction/destruction

CHtmlClockDoc::CHtmlClockDoc()
{
	// TODO: add one-time construction code here

}

CHtmlClockDoc::~CHtmlClockDoc()
{
}

BOOL CHtmlClockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHtmlClockDoc serialization

void CHtmlClockDoc::Serialize(CArchive& ar)
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
// CHtmlClockDoc diagnostics

#ifdef _DEBUG
void CHtmlClockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHtmlClockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockDoc commands
