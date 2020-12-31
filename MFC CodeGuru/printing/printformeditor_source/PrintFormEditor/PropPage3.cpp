// PropPage3.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PropPage3.h"

#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage3 dialog


CPropPage3::CPropPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CPropPage3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropPage3)
	iLineWidth = 0;
	//}}AFX_DATA_INIT
	crBack = RGB(255,255,255);
	crText = RGB(0,0,0);
	crBdr  = RGB(0,0,0);
	pDoc = NULL;
	pView = NULL;
}

/*
	DDX_Control(pDX, IDC_BT_TEXTCOLOR, wndTextCol);
	DDX_Control(pDX, IDC_BT_COLORBDR, wndBdrCol);
	DDX_Control(pDX, IDC_BT_BCKCOL, wndBkCol);
	DDX_Control(pDX, IDC_CB_LINETYPE, wndLineType);
	DDX_Control(pDX, IDC_CB_BORDERSIZE, wndBorderSize);
	DDX_Control(pDX, IDC_CB_BORDER, wndBorder);
	DDX_Control(pDX, IDC_CB_BCK_TYPE, wndBckType);
*/

void CPropPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BT_TEXTCOLOR, wndTextCol);
	DDX_Control(pDX, IDC_BT_COLORBDR, wndBdrCol);
	DDX_Control(pDX, IDC_BT_BCKCOL, wndBkCol);
	DDX_Control(pDX, IDC_CB_LINETYPE, wndLineType);
	DDX_Control(pDX, IDC_CB_BORDERSIZE, wndBorderSize);
	DDX_Control(pDX, IDC_CB_BORDER, wndBorder);
	DDX_Control(pDX, IDC_CB_BCK_TYPE, wndBckType);

	if (wndLineType.GetCount() <= 0)
	{
		wndLineType.AddString("Solid line");
		wndLineType.AddString("Dotted line");
	}

	if (wndBorderSize.GetCount() <= 0)
	{
		wndBorderSize.AddString("0");
		wndBorderSize.AddString("1");
		wndBorderSize.AddString("2");
		wndBorderSize.AddString("3");
		wndBorderSize.AddString("4");
		wndBorderSize.AddString("5");
		wndBorderSize.AddString("6");
		wndBorderSize.AddString("7");
		wndBorderSize.AddString("8");
		wndBorderSize.AddString("9");
		wndBorderSize.AddString("10");
		wndBorderSize.AddString("11");
		wndBorderSize.AddString("12");
		wndBorderSize.AddString("13");
		wndBorderSize.AddString("14");
		wndBorderSize.AddString("15");
		wndBorderSize.AddString("16");
		wndBorderSize.AddString("17");
		wndBorderSize.AddString("18");
		wndBorderSize.AddString("19");
		wndBorderSize.AddString("20");
	}

	if (wndBorder.GetCount() <= 0)
	{
		wndBorder.AddString("No border");
		wndBorder.AddString("Single line border");
		wndBorder.AddString("Double line border");
	}

	if (wndBckType.GetCount() <= 0)
	{

		wndBckType.AddString("Transparent");
		wndBckType.AddString("Solid");
	}


	if (pDoc && pView && !(pDX->m_bSaveAndValidate))
	{
		if (pDoc->GetSelectedCount() > 0)
		{
			bool bMulti = pDoc->GetSelectedCount() > 1;

			CString cs;
			for (int t = 0; t < pDoc->iFormObj; t++)
			{
				if (pDoc->ppObjs[t]->bSelected)
				{
					crBack = pDoc->ppObjs[t]->crBack;
					crText = pDoc->ppObjs[t]->crFront;
					crBdr  = pDoc->ppObjs[t]->crBdr;

					if (pDoc->ppObjs[t]->iBack == 0) wndBckType.SetCurSel(1);
					else wndBckType.SetCurSel(0);

					if (pDoc->ppObjs[t]->iBorder == 1) wndBorder.SetCurSel(1);
					else if (pDoc->ppObjs[t]->iBorder == 2) wndBorder.SetCurSel(2);
					else wndBorder.SetCurSel(0);

					wndBorderSize.SetCurSel(pDoc->ppObjs[t]->iBorderSize);

					wndLineType.EnableWindow(true);
					if (pDoc->ppObjs[t]->exInfo == 1) wndLineType.SetCurSel(1);
					else wndLineType.SetCurSel(0);
				}
			}
		}
	}


	//{{AFX_DATA_MAP(CPropPage3)
	DDX_Text(pDX, IDC_ED_LW, iLineWidth);
	//}}AFX_DATA_MAP
    DDX_ColourPicker(pDX, IDC_BT_BCKCOL, crBack);
    DDX_ColourPicker(pDX, IDC_BT_COLORBDR, crBdr);
    DDX_ColourPicker(pDX, IDC_BT_TEXTCOLOR, crText);

	if (pDoc && pView && pDX->m_bSaveAndValidate && pDoc->GetSelectedCount() > 0)
	{
		bool bMulti = pDoc->GetSelectedCount() > 1;

		CString cs;
		
		for (int t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				pDoc->ppObjs[t]->crBack = crBack;
				pDoc->ppObjs[t]->crFront = crText;
				pDoc->ppObjs[t]->crBdr = crBdr;

				int idx = wndBckType.GetCurSel();
				pDoc->ppObjs[t]->iBack = (idx == 0 ? -1 : 0);

				idx = wndBorder.GetCurSel();
				if (idx == 1) pDoc->ppObjs[t]->iBorder = 1;
				else if (idx == 2) pDoc->ppObjs[t]->iBorder = 2;
				else pDoc->ppObjs[t]->iBorder = 0;

				idx = wndBorderSize.GetCurSel();
				if (idx < 1) idx = 1;
				pDoc->ppObjs[t]->iBorderSize = idx;
			}
		}
		pView->Invalidate();
	}

}


BEGIN_MESSAGE_MAP(CPropPage3, CDialog)
	//{{AFX_MSG_MAP(CPropPage3)
	ON_CBN_SELENDOK(IDC_CB_BCK_TYPE, OnSelendokCbBckType)
	ON_CBN_SELENDOK(IDC_CB_BORDER, OnSelendokCbBorder)
	ON_CBN_SELENDOK(IDC_CB_BORDERSIZE, OnSelendokCbBordersize)
	ON_CBN_SELENDOK(IDC_CB_LINETYPE, OnSelendokCbLinetype)
	ON_EN_KILLFOCUS(IDC_ED_LW, OnKillfocusEdLw)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CPN_SELENDOK,OnColSelendOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage3 message handlers

LONG CPropPage3::OnColSelendOk(UINT lParam, LONG wParam)
{
	UpdateData();
	return 0;
}

BOOL CPropPage3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPage3::OnCancel() { }
void CPropPage3::OnOK() {}

void CPropPage3::OnSelendokCbBckType() 
{
	UpdateData();
}

void CPropPage3::OnSelendokCbBorder() 
{
	UpdateData();
}

void CPropPage3::OnSelendokCbBordersize() 
{
	UpdateData();
}

void CPropPage3::OnSelendokCbLinetype() 
{
	UpdateData();
}

void CPropPage3::OnKillfocusEdLw() 
{
	UpdateData();
}
