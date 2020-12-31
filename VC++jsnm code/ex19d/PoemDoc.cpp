// PoemDoc.cpp : implementation of the CPoemDoc class
//

#include "stdafx.h"
#include "ex19d.h"

#include "PoemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPoemDoc

IMPLEMENT_DYNCREATE(CPoemDoc, CDocument)

BEGIN_MESSAGE_MAP(CPoemDoc, CDocument)
	//{{AFX_MSG_MAP(CPoemDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPoemDoc construction/destruction

CPoemDoc::CPoemDoc()
{
	// TODO: add one-time construction code here

}

CPoemDoc::~CPoemDoc()
{
}

BOOL CPoemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_stringArray.SetSize(10);
	m_stringArray[0] = "The pennycandystore beyond the El";
	m_stringArray[1] = "is where I first";
	m_stringArray[2] = "                  fell in love";
	m_stringArray[3] = "                      with unreality";
	m_stringArray[4] = "Jellybeans glowed in the semi-gloom";
	m_stringArray[5] = "of that september afternoon";
	m_stringArray[6] = "A cat upon the counter moved among";
	m_stringArray[7] = "                     the licorice sticks";
	m_stringArray[8] = "                  and tootsie rolls";
	m_stringArray[9] = "           and Oh Boy Gum";

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPoemDoc serialization

void CPoemDoc::Serialize(CArchive& ar)
{
	m_stringArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPoemDoc diagnostics

#ifdef _DEBUG
void CPoemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPoemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPoemDoc commands

void CPoemDoc::DeleteContents() 
{
	// called before OnNewDocument and when document is closed
	m_stringArray.RemoveAll();
}
