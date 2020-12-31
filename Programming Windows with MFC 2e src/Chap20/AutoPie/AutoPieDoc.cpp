// AutoPieDoc.cpp : implementation of the CAutoPieDoc class
//

#include "stdafx.h"
#include "AutoPie.h"

#include "AutoPieDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPieDoc

IMPLEMENT_DYNCREATE(CAutoPieDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoPieDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoPieDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoPieDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CAutoPieDoc)
	DISP_PROPERTY_EX(CAutoPieDoc, "Chart", GetChart, SetChart, VT_DISPATCH)
	DISP_PROPERTY_EX(CAutoPieDoc, "Window", GetWindow, SetWindow, VT_DISPATCH)
	DISP_PROPERTY_EX(CAutoPieDoc, "Toolbar", GetToolbar, SetToolbar, VT_DISPATCH)
	DISP_FUNCTION(CAutoPieDoc, "Quit", Quit, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoPie to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3B5BA308-3B72-11D2-AC82-006008A8274D}
static const IID IID_IAutoPie =
{ 0x3b5ba308, 0x3b72, 0x11d2, { 0xac, 0x82, 0x0, 0x60, 0x8, 0xa8, 0x27, 0x4d } };

BEGIN_INTERFACE_MAP(CAutoPieDoc, CDocument)
	INTERFACE_PART(CAutoPieDoc, IID_IAutoPie, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPieDoc construction/destruction

CAutoPieDoc::CAutoPieDoc()
{
	EnableAutomation();

	AfxOleLockApp();
}

CAutoPieDoc::~CAutoPieDoc()
{
	AfxOleUnlockApp();
}

BOOL CAutoPieDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_nRevenues[0] = 1;
	m_nRevenues[1] = 1;
	m_nRevenues[2] = 1;
	m_nRevenues[3] = 1;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPieDoc serialization

void CAutoPieDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		for (int i=0; i<4; i++)
			ar << m_nRevenues[i];
	}
	else
	{
		for (int i=0; i<4; i++)
			ar >> m_nRevenues[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPieDoc diagnostics

#ifdef _DEBUG
void CAutoPieDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoPieDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoPieDoc commands

int CAutoPieDoc::GetRevenue(int nQuarter)
{
	ASSERT (nQuarter >= 0 && nQuarter <= 3);
	return m_nRevenues[nQuarter];
}

void CAutoPieDoc::SetRevenue(int nQuarter, int nNewValue)
{
	ASSERT (nQuarter >= 0 && nQuarter <= 3);
	m_nRevenues[nQuarter] = nNewValue;
}

void CAutoPieDoc::Quit() 
{
	AfxGetMainWnd ()->PostMessage (WM_CLOSE, 0, 0);
}

LPDISPATCH CAutoPieDoc::GetChart() 
{
	return m_autoChart.GetIDispatch (TRUE);
}

void CAutoPieDoc::SetChart(LPDISPATCH newValue) 
{
	SetNotSupported ();
}

LPDISPATCH CAutoPieDoc::GetWindow() 
{
	return m_autoWindow.GetIDispatch (TRUE);
}

void CAutoPieDoc::SetWindow(LPDISPATCH newValue) 
{
	SetNotSupported ();
}

LPDISPATCH CAutoPieDoc::GetToolbar() 
{
	return m_autoToolbar.GetIDispatch (TRUE);
}

void CAutoPieDoc::SetToolbar(LPDISPATCH newValue) 
{
	SetNotSupported ();
}
