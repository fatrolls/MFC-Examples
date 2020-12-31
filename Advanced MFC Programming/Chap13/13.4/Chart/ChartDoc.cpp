#include "stdafx.h"
#include "Chart.h"
#include "ChartDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChartDoc, CDocument)

BEGIN_MESSAGE_MAP(CChartDoc, CDocument)
	//{{AFX_MSG_MAP(CChartDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChartDoc::CChartDoc()
{
	m_nA=20;
	m_nB=70;
	m_nC=10;
}

CChartDoc::~CChartDoc()
{
}

BOOL CChartDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CChartDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CChartDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChartDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
