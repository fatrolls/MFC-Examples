#include "stdafx.h"
#include "Menu.h"
#include "MenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CMenuDoc, CDocument)
	//{{AFX_MSG_MAP(CMenuDoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID__POPUPITEM1, OnPopUpItem1)
	ON_COMMAND(ID__POPUPITEM2, OnPopUpItem2)
	ON_COMMAND(ID__POPUPITEM3, OnPopUpItem3)
	ON_COMMAND(ID__POPUPITEM4, OnPopUpItem4)
END_MESSAGE_MAP()

CMenuDoc::CMenuDoc()
{
}

CMenuDoc::~CMenuDoc()
{
}

BOOL CMenuDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}

void CMenuDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CMenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CMenuDoc::OnPopUpItem1()
{
	AfxMessageBox("Pop up menu item 1");
}

void CMenuDoc::OnPopUpItem2()
{
	AfxMessageBox("Pop up menu item 2");
}

void CMenuDoc::OnPopUpItem3()
{
	AfxMessageBox("Pop up menu item 3");
}

void CMenuDoc::OnPopUpItem4()
{
	AfxMessageBox("Pop up menu item 4");
}
