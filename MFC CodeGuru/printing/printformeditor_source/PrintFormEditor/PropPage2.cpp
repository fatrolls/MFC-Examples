// PropPage2.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PropPage2.h"

#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 dialog


CPropPage2::CPropPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CPropPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropPage2)
	csCond = _T("");
	csId = _T("");
	csId2 = _T("");
	//}}AFX_DATA_INIT
	pDoc = NULL;
	pView = NULL;
}

/*
	DDX_Control(pDX, IDC_CB_ID2, wndCbId2);
	DDX_Control(pDX, IDC_CB_ID, wndCbId);
	DDX_Control(pDX, IDC_CB_COND, wndCbCond);
	DDX_Control(pDX, IDC_CB_VALIGN, wndCbVAlign);
	DDX_Control(pDX, IDC_CB_HALIGN, wndCbHAlign);
*/

void CPropPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CB_ID2, wndCbId2);
	DDX_Control(pDX, IDC_CB_ID, wndCbId);
	DDX_Control(pDX, IDC_CB_COND, wndCbCond);
	DDX_Control(pDX, IDC_CB_VALIGN, wndCbVAlign);
	DDX_Control(pDX, IDC_CB_HALIGN, wndCbHAlign);

	if (wndCbVAlign.GetCount() <= 0)
	{
		wndCbVAlign.SetItemData(wndCbVAlign.AddString("top"), DT_TOP);
		wndCbVAlign.SetItemData(wndCbVAlign.AddString("middle"), DT_VCENTER);
		wndCbVAlign.SetItemData(wndCbVAlign.AddString("bottom"), DT_BOTTOM);
	}

	if (wndCbHAlign.GetCount() <= 0)
	{
		wndCbHAlign.SetItemData(wndCbHAlign.AddString("left"), DT_LEFT);
		wndCbHAlign.SetItemData(wndCbHAlign.AddString("center"), DT_CENTER);
		wndCbHAlign.SetItemData(wndCbHAlign.AddString("right"), DT_RIGHT);
	}

	if (wndCbId.GetCount() <= 0)
	{
		wndCbId.AddString("ID TRY 1");
		wndCbId.AddString("ID TRY 2");
		wndCbId.AddString("ID TRY 3");
	}

	if (wndCbId2.GetCount() <= 0)
	{
		wndCbId2.AddString("ID TRY 1");
		wndCbId2.AddString("ID TRY 2");
		wndCbId2.AddString("ID TRY 3");
	}
		
	if (wndCbCond.GetCount() <= 0)
	{
		wndCbCond.AddString("COND1");
		wndCbCond.AddString("COND2");
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
					if (pDoc->ppObjs[t]->uiTextFormat&DT_CENTER) wndCbHAlign.SetCurSel(1);
					else if (pDoc->ppObjs[t]->uiTextFormat&DT_RIGHT) wndCbHAlign.SetCurSel(2);
					else wndCbHAlign.SetCurSel(0);

					if (pDoc->ppObjs[t]->uiTextFormat&DT_VCENTER) wndCbVAlign.SetCurSel(1);
					else if (pDoc->ppObjs[t]->uiTextFormat&DT_BOTTOM) wndCbVAlign.SetCurSel(2);
					else wndCbVAlign.SetCurSel(0);

					csId = pDoc->ppObjs[t]->cId;
					csId2 = pDoc->ppObjs[t]->cId2;
					csCond = pDoc->ppObjs[t]->cCond;
				}
			}
		}
	}

	//{{AFX_DATA_MAP(CPropPage2)
	DDX_CBString(pDX, IDC_CB_COND, csCond);
	DDX_CBString(pDX, IDC_CB_ID, csId);
	DDX_CBString(pDX, IDC_CB_ID2, csId2);
	//}}AFX_DATA_MAP
	if (pDoc && pView && pDX->m_bSaveAndValidate && pDoc->GetSelectedCount() > 0)
	{
		bool bMulti = pDoc->GetSelectedCount() > 1;

		CString cs;
		
		for (int t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				GetDlgItemText(IDC_CB_ID, csId);

				lstrcpy(pDoc->ppObjs[t]->cId, csId);
				lstrcpy(pDoc->ppObjs[t]->cId2, csId2);
				lstrcpy(pDoc->ppObjs[t]->cCond, csCond);

				pDoc->ppObjs[t]->uiTextFormat &= ~(DT_RIGHT|DT_CENTER|DT_VCENTER|DT_BOTTOM|DT_SINGLELINE);

				int idx = wndCbVAlign.GetCurSel();
				long l = wndCbVAlign.GetItemData(idx);

				pDoc->ppObjs[t]->uiTextFormat |= l;
				if (l == DT_VCENTER) pDoc->ppObjs[t]->uiTextFormat |= DT_SINGLELINE;

				idx = wndCbHAlign.GetCurSel();
				l = wndCbHAlign.GetItemData(idx);
				pDoc->ppObjs[t]->uiTextFormat |= l;
			}
		}
		pView->Invalidate();
	}
}


BEGIN_MESSAGE_MAP(CPropPage2, CDialog)
	//{{AFX_MSG_MAP(CPropPage2)
	ON_CBN_SELENDOK(IDC_CB_COND, OnSelendokCbCond)
	ON_CBN_SELENDOK(IDC_CB_HALIGN, OnSelendokCbHalign)
	ON_CBN_SELENDOK(IDC_CB_ID, OnSelendokCbId)
	ON_CBN_SELENDOK(IDC_CB_ID2, OnSelendokCbId2)
	ON_CBN_SELENDOK(IDC_CB_VALIGN, OnSelendokCbValign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 message handlers

BOOL CPropPage2::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*	wndCbVAlign.SetItemData(wndCbVAlign.AddString("top"), DT_TOP);
	wndCbVAlign.SetItemData(wndCbVAlign.AddString("middle"), DT_VCENTER);
	wndCbVAlign.SetItemData(wndCbVAlign.AddString("bottom"), DT_BOTTOM);

	wndCbHAlign.SetItemData(wndCbHAlign.AddString("left"), DT_LEFT);
	wndCbHAlign.SetItemData(wndCbHAlign.AddString("center"), DT_CENTER);
	wndCbHAlign.SetItemData(wndCbHAlign.AddString("right"), DT_RIGHT);

	wndCbId.AddString("ID TRY 1");
	wndCbId.AddString("ID TRY 2");
	wndCbId.AddString("ID TRY 3");

	wndCbId2.AddString("ID TRY 1");
	wndCbId2.AddString("ID TRY 2");
	wndCbId2.AddString("ID TRY 3");
	
	wndCbCond.AddString("COND1");
	wndCbCond.AddString("COND2");
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPage2::OnCancel() { }
void CPropPage2::OnOK() {}

void CPropPage2::OnSelendokCbCond() 
{
	UpdateData();	
}

void CPropPage2::OnSelendokCbHalign() 
{
	UpdateData();	
}

void CPropPage2::OnSelendokCbId() 
{
	UpdateData();	
}

void CPropPage2::OnSelendokCbId2() 
{
	UpdateData();	
}

void CPropPage2::OnSelendokCbValign() 
{
	UpdateData();	
}
