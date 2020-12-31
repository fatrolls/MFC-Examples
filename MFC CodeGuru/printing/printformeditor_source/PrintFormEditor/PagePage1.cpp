// PagePage1.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PagePage1.h"

#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagePage1 dialog


CPagePage1::CPagePage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPagePage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPagePage1)
	iBottom = 0;
	iLeft = 0;
	csName = _T("");
	iRight = 0;
	iTop = 0;
	//}}AFX_DATA_INIT
	pDoc = NULL;
}


void CPagePage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if (pDoc)
	{
		if (!(pDX->m_bSaveAndValidate))
		{
			csName = pDoc->name;
			iBottom = pDoc->rcPaper.bottom;
			iLeft = pDoc->rcPaper.left;
			iRight = pDoc->rcPaper.right;
			iTop = pDoc->rcPaper.top;
		}
	}

	//{{AFX_DATA_MAP(CPagePage1)
	DDX_Text(pDX, IDC_ED_BOTTOM, iBottom);
	DDX_Text(pDX, IDC_ED_LEFT, iLeft);
	DDX_Text(pDX, IDC_ED_NAME, csName);
	DDX_Text(pDX, IDC_ED_RIGHT, iRight);
	DDX_Text(pDX, IDC_ED_TOP, iTop);
	//}}AFX_DATA_MAP

	if (pDoc)
	{
		if (pDX->m_bSaveAndValidate)
		{
			pDoc->RenamePage(pDoc->iSelpage, csName);
			pDoc->SetPageRect(CRect(iLeft, iTop, iRight, iBottom));
/*			pDoc->name = csName;
			pDoc->rcPaper.bottom = iBottom;
			pDoc->rcPaper.left = iLeft;
			pDoc->rcPaper.right = iRight;
			pDoc->rcPaper.top = iTop;*/
		}
	}
}


BEGIN_MESSAGE_MAP(CPagePage1, CDialog)
	//{{AFX_MSG_MAP(CPagePage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagePage1 message handlers
