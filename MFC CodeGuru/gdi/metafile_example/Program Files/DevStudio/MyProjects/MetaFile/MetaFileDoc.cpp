// MetaFileDoc.cpp : implementation of the CMetaFileDoc class
//

#include "stdafx.h"
#include "MetaFile.h"

#include "MetaFileDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc

IMPLEMENT_DYNCREATE(CMetaFileDoc, CDocument)

BEGIN_MESSAGE_MAP(CMetaFileDoc, CDocument)
	//{{AFX_MSG_MAP(CMetaFileDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc construction/destruction

CMetaFileDoc::CMetaFileDoc()
{
	// TODO: add one-time construction code here
	
	// Metafile test
	// Load a metafile into the m_meta
	// object
	m_meta.Read("bird.wmf");
}

CMetaFileDoc::~CMetaFileDoc()
{
}

BOOL CMetaFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc serialization

void CMetaFileDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_meta.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		m_meta.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc diagnostics

#ifdef _DEBUG
void CMetaFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMetaFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc commands

CMetaFile& CMetaFileDoc::GetMetaFile()
{
	return m_meta;
}
