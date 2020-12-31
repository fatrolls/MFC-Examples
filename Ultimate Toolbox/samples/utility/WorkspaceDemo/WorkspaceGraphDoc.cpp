// WorkspaceGraphDoc.cpp : implementation of the CWorkspaceGraphDoc class
//

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceGraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphDoc

IMPLEMENT_DYNCREATE(CWorkspaceGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorkspaceGraphDoc, CDocument)
//{{AFX_MSG_MAP(CWorkspaceGraphDoc)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphDoc construction/destruction

CWorkspaceGraphDoc::CWorkspaceGraphDoc()
	:
	m_color(0),
	m_nSides(3)
	{
	}

CWorkspaceGraphDoc::~CWorkspaceGraphDoc()
	{
	}

BOOL CWorkspaceGraphDoc::OnNewDocument()
	{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
	}

BOOL CWorkspaceGraphDoc::SetColor(COLORREF color)
	{
	BOOL bModified = FALSE;
	if (color != m_color)
		{
		m_color = color;
		bModified = TRUE;
		SetModifiedFlag(TRUE);
		}
	
	return bModified;
	}

COLORREF CWorkspaceGraphDoc::GetColor() const
	{
	return m_color;
	}

BOOL CWorkspaceGraphDoc::SetSides(int nSides)
	{
	BOOL bModified = FALSE;
	if (nSides != m_nSides)
		{
		m_nSides = nSides;
		bModified = TRUE;
		SetModifiedFlag(TRUE);
		}
	
	return bModified;
	}

int CWorkspaceGraphDoc::GetSides() const
	{
	return m_nSides;
	}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphDoc serialization

void CWorkspaceGraphDoc::Serialize(CArchive& ar)
	{
	if (ar.IsStoring())
		{
		ar << m_color;
		ar << m_nSides;
		}
	else
		{
		ar >> m_color;
		ar >> m_nSides;
		}
	}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphDoc diagnostics

#ifdef _DEBUG
void CWorkspaceGraphDoc::AssertValid() const
	{
	CDocument::AssertValid();
	}

void CWorkspaceGraphDoc::Dump(CDumpContext& dc) const
	{
	CDocument::Dump(dc);
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphDoc commands
