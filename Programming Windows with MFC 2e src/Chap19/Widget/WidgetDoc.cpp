// WidgetDoc.cpp : implementation of the CWidgetDoc class
//

#include "stdafx.h"
#include "Widget.h"

#include "WidgetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWidgetDoc

IMPLEMENT_DYNCREATE(CWidgetDoc, CDocument)

BEGIN_MESSAGE_MAP(CWidgetDoc, CDocument)
	//{{AFX_MSG_MAP(CWidgetDoc)
	ON_COMMAND(ID_INSERT_REDWIDGET, OnInsertRedWidget)
	ON_COMMAND(ID_INSERT_BLUEWIDGET, OnInsertBlueWidget)
	ON_COMMAND(ID_INSERT_YELLOWWIDGET, OnInsertYellowWidget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWidgetDoc construction/destruction

CWidgetDoc::CWidgetDoc()
{
	// TODO: add one-time construction code here

}

CWidgetDoc::~CWidgetDoc()
{
}

BOOL CWidgetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWidgetDoc serialization

void CWidgetDoc::Serialize(CArchive& ar)
{
	m_arrWidgets.Serialize (ar);
}

/////////////////////////////////////////////////////////////////////////////
// CWidgetDoc diagnostics

#ifdef _DEBUG
void CWidgetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWidgetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWidgetDoc commands

void CWidgetDoc::DeleteContents() 
{
	int i = m_arrWidgets.GetSize ();
	while (i)
		delete m_arrWidgets[--i];
	m_arrWidgets.RemoveAll ();
	CDocument::DeleteContents();
}

int CWidgetDoc::GetWidgetCount()
{
	return m_arrWidgets.GetSize ();
}

CWidget* CWidgetDoc::GetWidget(int nIndex)
{
	if (nIndex >= m_arrWidgets.GetSize ())
		return NULL;
	return (CWidget*) m_arrWidgets[nIndex];
}

int CWidgetDoc::AddWidget(int x, int y, COLORREF color)
{
	int nIndex = -1;
	CWidget* pWidget = NULL;

	try {
		pWidget = new CWidget (x, y, color);
		nIndex = m_arrWidgets.Add (pWidget);	
		SetModifiedFlag ();
	}
	catch (CMemoryException* e) {
		AfxMessageBox (_T ("Out of memory"));
		if (pWidget != NULL)
			delete pWidget;
		e->Delete ();
		return -1;
	}
	return nIndex;
}

BOOL CWidgetDoc::RemoveWidget(int nIndex)
{
	if (nIndex >= m_arrWidgets.GetSize ())
		return FALSE;

	delete m_arrWidgets[nIndex];
	m_arrWidgets.RemoveAt (nIndex);
	return TRUE;
}

void CWidgetDoc::OnInsertBlueWidget() 
{
	AddWidget (10, 10, RGB (0, 0, 255));
	UpdateAllViews (NULL);
}

void CWidgetDoc::OnInsertRedWidget() 
{
	AddWidget (10, 10, RGB (255, 0, 0));
	UpdateAllViews (NULL);
}

void CWidgetDoc::OnInsertYellowWidget() 
{
	AddWidget (10, 10, RGB (255, 255, 0));
	UpdateAllViews (NULL);
}
