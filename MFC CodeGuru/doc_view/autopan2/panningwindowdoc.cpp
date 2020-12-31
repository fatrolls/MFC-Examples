// PanningWindowDoc.cpp : implementation of the CPanningWindowDoc class
//

#include "stdafx.h"
#include "PanningWindow.h"

#include "PanningWindowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowDoc

IMPLEMENT_DYNCREATE(CPanningWindowDoc, CDocument)

BEGIN_MESSAGE_MAP(CPanningWindowDoc, CDocument)
	//{{AFX_MSG_MAP(CPanningWindowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowDoc construction/destruction

CPanningWindowDoc::CPanningWindowDoc()
	: m_sizeDrawing( 1000, 1000 )
{
	// TODO: add one-time construction code here

}

CPanningWindowDoc::~CPanningWindowDoc()
{
}


BOOL CPanningWindowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	int nCount = 0;
	for( int nRow = 0; nRow < 10; nRow++ )
	{
		for( int nCol = 0; nCol < 10; nCol++ )
		{
			m_arrShapes.Add( new CRectangle( ++nCount, CPoint( nCol * 100, nRow * 100 ) ) );
		}
	}
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPanningWindowDoc serialization

void CPanningWindowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//	We will not be doing this for this demo!
		ASSERT( FALSE );
	}
	else
	{
		//	We will not be doing this for this demo!
		ASSERT( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowDoc diagnostics

#ifdef _DEBUG
void CPanningWindowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPanningWindowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowDoc commands

CSize CPanningWindowDoc::GetDrawingSize() const
{
	return m_sizeDrawing;
}

void CPanningWindowDoc::DeleteContents() 
{
	for( int n = 0; n < m_arrShapes.GetSize(); n++ )
	{
		delete m_arrShapes[ n ];
	}
	m_arrShapes.RemoveAll();

	CDocument::DeleteContents();
}
