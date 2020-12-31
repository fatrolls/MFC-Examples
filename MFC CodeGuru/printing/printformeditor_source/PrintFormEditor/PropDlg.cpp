// PropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PropDlg.h"

#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

void SelectById(CComboBox * pBox, long lId)
{
	for (int t = 0; t < pBox->GetCount(); t++)
	{
		long l = pBox->GetItemData(t);
		if (lId != 0 && lId&l) 
		{
			pBox->SetCurSel(t);
			return;
		}
	}
}

CPropDlg::CPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pView = NULL;
	pDoc  = NULL;
}


void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
	DDX_Control(pDX, IDC_TAB1, wndTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropDlg, CDialog)
	//{{AFX_MSG_MAP(CPropDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BT_APPLY, OnBtApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers

BOOL CPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect drc;
	wndTab.GetClientRect(drc);
	
	dlgSheet1.Create(CPropPage1::IDD, &wndTab);
	dlgSheet1.SetWindowPos(0,4,27,drc.Width() - 8,drc.Height()-30,SWP_NOZORDER);

	dlgSheet2.Create(CPropPage2::IDD, &wndTab);
	dlgSheet2.SetWindowPos(0,4,27,drc.Width() - 8,drc.Height()-30,SWP_NOZORDER);

	dlgSheet3.Create(CPropPage3::IDD, &wndTab);
	dlgSheet3.SetWindowPos(0,4,27,drc.Width() - 8,drc.Height()-30,SWP_NOZORDER);

	GfxAddTabItem(wndTab, 0, "General");
	GfxAddTabItem(wndTab, 1, "Id's");
	GfxAddTabItem(wndTab, 2, "Other");

	dlgSheet1.ShowWindow(SW_SHOW);

	GfxSetTabDialog(0, &dlgSheet1);
	GfxSetTabDialog(1, &dlgSheet2);
	GfxSetTabDialog(2, &dlgSheet3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int idx = wndTab.GetCurSel();
	GfxSwitchTabDialog(idx, iNumDialog);
	
	*pResult = 0;
}

void CPropDlg::OnBtApply() 
{
	if (pView && pDoc && pDoc->GetSelectedCount() > 0)
	{
		bool bMulti = pDoc->GetSelectedCount() > 1;

		CString cs;
		
		for (int t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				if (!bMulti)
				{
					dlgSheet1.wndEditX.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.left = atoi(cs);

					dlgSheet1.wndEditWidth.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.right = pDoc->ppObjs[t]->rc.left + atoi(cs);

					dlgSheet1.wndEditY.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.top = atoi(cs);

					dlgSheet1.wndEditHeight.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.bottom = pDoc->ppObjs[t]->rc.top + atoi(cs);
				}
				dlgSheet1.UpdateData();
				dlgSheet2.UpdateData();
				dlgSheet3.UpdateData();

				pDoc->ppObjs[t]->bBold = dlgSheet1.bBold ? true : false;
				pDoc->ppObjs[t]->bItalic = dlgSheet1.bItalic ? true : false;
				pDoc->ppObjs[t]->bUnderline = dlgSheet1.bUnderline ? true : false;

				lstrcpy(pDoc->ppObjs[t]->cId, dlgSheet2.csId);
				lstrcpy(pDoc->ppObjs[t]->cId2, dlgSheet2.csId2);
				lstrcpy(pDoc->ppObjs[t]->cCond, dlgSheet2.csCond);

				lstrcpy(pDoc->ppObjs[t]->cFont, dlgSheet1.csFontName);
				pDoc->ppObjs[t]->iSize = atoi(dlgSheet1.csFontSize);

				pDoc->ppObjs[t]->uiTextFormat &= ~(DT_RIGHT|DT_CENTER|DT_VCENTER|DT_BOTTOM|DT_SINGLELINE);

				int idx = dlgSheet2.wndCbVAlign.GetCurSel();
				long l = dlgSheet2.wndCbVAlign.GetItemData(idx);

				pDoc->ppObjs[t]->uiTextFormat |= l;
				if (l == DT_VCENTER) pDoc->ppObjs[t]->uiTextFormat |= DT_SINGLELINE;

				idx = dlgSheet2.wndCbHAlign.GetCurSel();
				l = dlgSheet2.wndCbHAlign.GetItemData(idx);
				pDoc->ppObjs[t]->uiTextFormat |= l;

				pDoc->ppObjs[t]->crBack = dlgSheet3.crBack;
				pDoc->ppObjs[t]->crFront = dlgSheet3.crText;
				pDoc->ppObjs[t]->crBdr = dlgSheet3.crBdr;

				idx = dlgSheet3.wndBckType.GetCurSel();
				pDoc->ppObjs[t]->iBack = (idx == 0 ? -1 : 0);

				idx = dlgSheet3.wndBorderSize.GetCurSel();
				if (idx < 1) idx = 1;
				pDoc->ppObjs[t]->iBorderSize = idx;


			}
		}
		pView->Invalidate();
	}
}

void CPropDlg::SetObject(Doc * pd, View * pv)
{
	pDoc  = pd;
	pView = pv;
	if (pDoc && pDoc->GetSelectedCount() > 0)
	{
		bool bMulti = pDoc->GetSelectedCount() > 1;

		if (bMulti)
		{
			dlgSheet1.wndEditX.EnableWindow(false);
			dlgSheet1.wndEditHeight.EnableWindow(false);
			dlgSheet1.wndEditY.EnableWindow(false);
			dlgSheet1.wndEditWidth.EnableWindow(false);

			dlgSheet1.wndEditX.SetWindowText("");
			dlgSheet1.wndEditHeight.SetWindowText("");
			dlgSheet1.wndEditY.SetWindowText("");
			dlgSheet1.wndEditWidth.SetWindowText("");
		}
		else
		{
			dlgSheet1.wndEditX.EnableWindow(true);
			dlgSheet1.wndEditHeight.EnableWindow(true);
			dlgSheet1.wndEditY.EnableWindow(true);
			dlgSheet1.wndEditWidth.EnableWindow(true);
		}

		CString cs;
		for (int t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				if (!bMulti)
				{
					cs.Format("%d", pDoc->ppObjs[t]->rc.left);
					dlgSheet1.wndEditX.SetWindowText(cs);
					cs.Format("%d", pDoc->ppObjs[t]->rc.Height());
					dlgSheet1.wndEditHeight.SetWindowText(cs);
					cs.Format("%d", pDoc->ppObjs[t]->rc.top);
					dlgSheet1.wndEditY.SetWindowText(cs);
					cs.Format("%d", pDoc->ppObjs[t]->rc.Width());
					dlgSheet1.wndEditWidth.SetWindowText(cs);
				}
				dlgSheet1.bBold = pDoc->ppObjs[t]->bBold;
				dlgSheet1.bItalic = pDoc->ppObjs[t]->bItalic;
				dlgSheet1.bUnderline = pDoc->ppObjs[t]->bUnderline;

				dlgSheet1.csFontName = pDoc->ppObjs[t]->cFont;
				dlgSheet1.csFontSize.Format("%d", pDoc->ppObjs[t]->iSize);

//				SelectById(&(dlgSheet2.wndCbHAlign), pDoc->ppObjs[t]->uiTextFormat);
//				SelectById(&(dlgSheet2.wndCbVAlign), pDoc->ppObjs[t]->uiTextFormat);

				if (pDoc->ppObjs[t]->uiTextFormat&DT_CENTER) dlgSheet2.wndCbHAlign.SetCurSel(1);
				else if (pDoc->ppObjs[t]->uiTextFormat&DT_RIGHT) dlgSheet2.wndCbHAlign.SetCurSel(2);
				else dlgSheet2.wndCbHAlign.SetCurSel(0);

				if (pDoc->ppObjs[t]->uiTextFormat&DT_VCENTER) dlgSheet2.wndCbVAlign.SetCurSel(1);
				else if (pDoc->ppObjs[t]->uiTextFormat&DT_BOTTOM) dlgSheet2.wndCbVAlign.SetCurSel(2);
				else dlgSheet2.wndCbVAlign.SetCurSel(0);

				dlgSheet2.csId = pDoc->ppObjs[t]->cId;
				dlgSheet2.csId2 = pDoc->ppObjs[t]->cId2;
				dlgSheet2.csCond = pDoc->ppObjs[t]->cCond;

				dlgSheet3.crBack = pDoc->ppObjs[t]->crBack;
				dlgSheet3.crText = pDoc->ppObjs[t]->crFront;
				dlgSheet3.crBdr  = pDoc->ppObjs[t]->crBdr;


				if (pDoc->ppObjs[t]->iBack == 0) dlgSheet3.wndBckType.SetCurSel(1);
				else dlgSheet3.wndBckType.SetCurSel(0);

				if (pDoc->ppObjs[t]->iBorder == 1) dlgSheet3.wndBorder.SetCurSel(1);
				else if (pDoc->ppObjs[t]->iBorder == 2) dlgSheet3.wndBorder.SetCurSel(2);
				else dlgSheet3.wndBorder.SetCurSel(0);

				dlgSheet3.wndBorderSize.SetCurSel(pDoc->ppObjs[t]->iBorderSize);

//enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoVLine, pfoHLine, pfoSubForm };
//				if (iType == pfoLine || iType == pfoLine || iType == pfoLine || iType == pfoLine)
				{
					dlgSheet3.wndLineType.EnableWindow(true);
					if (pDoc->ppObjs[t]->exInfo == 1) dlgSheet3.wndLineType.SetCurSel(1);
					else dlgSheet3.wndLineType.SetCurSel(0);
				}
/*				if (iType == pfoLine || iType == pfoRect || iType == pfoHLine || iType == pfoVLine)
				{
					dlgSheet3.iLineWidth = pDoc->ppObjs[t]->exInfo;
				}
				else dlgSheet3.wndLineType.EnableWindow(false);*/
			}
		}
		dlgSheet1.UpdateData(false);
		dlgSheet2.UpdateData(false);
		dlgSheet3.UpdateData(false);
	
	}
}


