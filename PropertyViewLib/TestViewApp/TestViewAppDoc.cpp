// TestViewAppDoc.cpp : implementation of the CTestViewAppDoc class
//

#include "stdafx.h"
#include "TestViewApp.h"

#include "TestViewAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppDoc

IMPLEMENT_DYNCREATE(CTestViewAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestViewAppDoc, CDocument)
	//{{AFX_MSG_MAP(CTestViewAppDoc)
	ON_COMMAND(ID_OBJECT0, OnObject0)
	ON_UPDATE_COMMAND_UI(ID_OBJECT0, OnUpdateObject0)
	ON_COMMAND(ID_OBJECT1, OnObject1)
	ON_UPDATE_COMMAND_UI(ID_OBJECT1, OnUpdateObject1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppDoc construction/destruction

CTestViewAppDoc::CTestViewAppDoc()
{
	m_pCurrentHost = &m_SomeObject0;
}

CTestViewAppDoc::~CTestViewAppDoc()
{
}

BOOL CTestViewAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestViewAppDoc serialization

void CTestViewAppDoc::Serialize(CArchive& ar)
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

IPropertyHost* CTestViewAppDoc::GetPropertyHost()
{
	return m_pCurrentHost;
}



/////////////////////////////////////////////////////////////////////////////
// CTestViewAppDoc diagnostics

#ifdef _DEBUG
void CTestViewAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestViewAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



void CTestViewAppDoc::OnObject0() 
{
	m_pCurrentHost = &m_SomeObject0;
	UpdateAllViews( NULL , HINT_SET_PROPERTY_HOST );
}

void CTestViewAppDoc::OnObject1() 
{
	m_pCurrentHost = &m_SomeObject1;
	UpdateAllViews( NULL , HINT_SET_PROPERTY_HOST );
}

void CTestViewAppDoc::OnUpdateObject0(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_pCurrentHost == &m_SomeObject0 );
}

void CTestViewAppDoc::OnUpdateObject1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_pCurrentHost == &m_SomeObject1 );
}
