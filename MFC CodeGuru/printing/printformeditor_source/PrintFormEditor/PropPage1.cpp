// PropPage1.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PropPage1.h"

#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 dialog
extern bool bLockingProperty;

CPropPage1::CPropPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CPropPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropPage1)
	bBold = FALSE;
	bItalic = FALSE;
	bUnderline = FALSE;
	csFontName = _T("");
	csFontSize = _T("");
	//}}AFX_DATA_INIT
	pDoc = NULL;
	pView = NULL;
}

/*
	DDX_Control(pDX, IDC_ED_YSIZE, wndEditHeight);
	DDX_Control(pDX, IDC_ED_Y, wndEditY);
	DDX_Control(pDX, IDC_ED_XSIZE, wndEditWidth);
	DDX_Control(pDX, IDC_ED_X, wndEditX);
*/

void CPropPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ED_YSIZE, wndEditHeight);
	DDX_Control(pDX, IDC_ED_Y, wndEditY);
	DDX_Control(pDX, IDC_ED_XSIZE, wndEditWidth);
	DDX_Control(pDX, IDC_ED_X, wndEditX);

	if (pDoc && pView && !(pDX->m_bSaveAndValidate))
	{
		if (pDoc->GetSelectedCount() > 0)
		{
			bool bMulti = pDoc->GetSelectedCount() > 1;

			wndEditX.EnableWindow(false);
			wndEditHeight.EnableWindow(false);
			wndEditY.EnableWindow(false);
			wndEditWidth.EnableWindow(false);
			if (bMulti)
			{
				wndEditX.EnableWindow(false);
				wndEditHeight.EnableWindow(false);
				wndEditY.EnableWindow(false);
				wndEditWidth.EnableWindow(false);

				wndEditX.SetWindowText("");
				wndEditHeight.SetWindowText("");
				wndEditY.SetWindowText("");
				wndEditWidth.SetWindowText("");
			}
/*			else
			{
				wndEditX.EnableWindow(true);
				wndEditHeight.EnableWindow(true);
				wndEditY.EnableWindow(true);
				wndEditWidth.EnableWindow(true);
			}
*/
			CString cs;
			for (int t = 0; t < pDoc->iFormObj; t++)
			{
				if (pDoc->ppObjs[t]->bSelected)
				{
					if (!bMulti)
					{
						cs.Format("%d", pDoc->ppObjs[t]->rc.left);
						wndEditX.SetWindowText(cs);
						cs.Format("%d", pDoc->ppObjs[t]->rc.Height());
						wndEditHeight.SetWindowText(cs);
						cs.Format("%d", pDoc->ppObjs[t]->rc.top);
						wndEditY.SetWindowText(cs);
						cs.Format("%d", pDoc->ppObjs[t]->rc.Width());
						wndEditWidth.SetWindowText(cs);
					}
					bBold = pDoc->ppObjs[t]->bBold;
					bItalic = pDoc->ppObjs[t]->bItalic;
					bUnderline = pDoc->ppObjs[t]->bUnderline;

					csFontName = pDoc->ppObjs[t]->cFont;
					csFontSize.Format("%d", pDoc->ppObjs[t]->iSize);
				}
			}
		}
	}

	//{{AFX_DATA_MAP(CPropPage1)
	DDX_Check(pDX, IDC_CHK_BOLD, bBold);
	DDX_Check(pDX, IDC_CHK_ITALIC, bItalic);
	DDX_Check(pDX, IDC_CHK_UNDERLINE, bUnderline);
	DDX_Text(pDX, IDC_STATIC_FONT, csFontName);
	DDX_Text(pDX, IDC_STATIC_SIZE, csFontSize);
	//}}AFX_DATA_MAP

	if (pDoc && pView && pDX->m_bSaveAndValidate && pDoc->GetSelectedCount() > 0)
	{
		bool bMulti = pDoc->GetSelectedCount() > 1;

		CString cs;
		
		for (int t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
/*				if (!bMulti)
				{
					wndEditX.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.left = atoi(cs);

					wndEditWidth.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.right = pDoc->ppObjs[t]->rc.left + atoi(cs);

					wndEditY.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.top = atoi(cs);

					wndEditHeight.GetWindowText(cs);
					pDoc->ppObjs[t]->rc.bottom = pDoc->ppObjs[t]->rc.top + atoi(cs);
				}
*/
				pDoc->ppObjs[t]->bBold = bBold ? true : false;
				pDoc->ppObjs[t]->bItalic = bItalic ? true : false;
				pDoc->ppObjs[t]->bUnderline = bUnderline ? true : false;

				lstrcpy(pDoc->ppObjs[t]->cFont, csFontName);
				pDoc->ppObjs[t]->iSize = atoi(csFontSize);
			}
		}
		pView->Invalidate();
	}
}


BEGIN_MESSAGE_MAP(CPropPage1, CDialog)
	//{{AFX_MSG_MAP(CPropPage1)
	ON_BN_CLICKED(IDC_BT_FONT, OnBtFont)
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_CHK_BOLD, OnChkBold)
	ON_BN_CLICKED(IDC_CHK_ITALIC, OnChkItalic)
	ON_BN_CLICKED(IDC_CHK_UNDERLINE, OnChkUnderline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 message handlers

void CPropPage1::OnBtFont() 
{
	UpdateData(true);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	CString cs;

	lstrcpy(lf.lfFaceName, csFontName);
	lf.lfHeight = atoi(csFontSize) + 2;

	if (bBold)		lf.lfWeight = 700;
	lf.lfItalic = bItalic;
	lf.lfUnderline = bUnderline;

	bLockingProperty = true;

	CFontDialog cf(&lf, CF_EFFECTS | CF_SCREENFONTS, NULL, this);
	if (cf.DoModal())
	{
		SetDlgItemText(IDC_STATIC_FONT, cf.GetFaceName());
		SetDlgItemInt(IDC_STATIC_SIZE, cf.GetSize() / 10);
//		csFontSize.Format("%d", cf.GetSize() / 10 );

		CheckDlgButton(IDC_CHK_BOLD, cf.IsBold() ? 1 : 0);
		CheckDlgButton(IDC_CHK_ITALIC, cf.IsItalic() ? 1 : 0);
		CheckDlgButton(IDC_CHK_UNDERLINE, cf.IsUnderline() ? 1 : 0);

//		bBold = cf.IsBold();
//		bItalic = cf.IsBold();
		UpdateData(true);//false);
	}
	SetFocus();
	bLockingProperty = false;
}

void CPropPage1::OnCancel() { }
void CPropPage1::OnOK() {}

void CPropPage1::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	if (!pNewWnd || pNewWnd != GetParent())
	{
		GetParent()->SendMessage(WM_KILLFOCUS, (WPARAM) pNewWnd->GetSafeHwnd());
	}
}

void CPropPage1::OnChkBold() 
{
	UpdateData();	
}

void CPropPage1::OnChkItalic() 
{
	UpdateData();	
}

void CPropPage1::OnChkUnderline() 
{
	UpdateData();	
}
