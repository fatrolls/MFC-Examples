#include "stdafx.h"
#include "GDI.h"
#include "MainFrm.h"
#include "GDIDoc.h"
#include "ColorBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CColorBar::CColorBar():CDialogBar()
{
	//{{AFX_DATA_INIT(CColorBar)
	//}}AFX_DATA_INIT
}


void CColorBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBar)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorBar, CDialogBar)
	//{{AFX_MSG_MAP(CColorBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CColorBar::InitButtons()
{
	int i;

	for(i=0; i<COLOR_BUTTON_NUM; i++)
	{
		m_btnColor[i].SetPalIndex(i);
		m_btnColor[i].SubclassDlgItem(IDC_BUTTON_COLOR1+i, this);
	}
	m_btnFB.SubclassDlgItem(IDC_BUTTON_FB, this);
	return TRUE;
}

BOOL CColorBar::Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID) 
{
	if(!CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID))return FALSE;
	return InitButtons();
}

BOOL CColorBar::Create(CWnd *pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID)
{
	if(!CDialogBar::Create(pParentWnd, lpszTemplateName, nStyle, nID))return FALSE;
	return InitButtons();
}

void CColorBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	CRect rect;
	CGDIDoc *pDoc;

	for(i=0; i<COLOR_BUTTON_NUM; i++)
	{
		m_btnColor[i].GetWindowRect(rect);
		ScreenToClient(rect);
		if(rect.PtInRect(point))
		{
			pDoc=
			(
				(CGDIDoc *)((CMainFrame *)
				(
					AfxGetApp()->m_pMainWnd)
				)->GetActiveDocument()
			);
			pDoc->SetFgdIndex(m_btnColor[i].GetPalIndex());
			m_btnFB.Invalidate(FALSE);
			break;
		}
	}
	CDialogBar::OnLButtonDown(nFlags, point);
}

void CColorBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	CRect rect;
	CGDIDoc *pDoc;

	for(i=0; i<COLOR_BUTTON_NUM; i++)
	{
		m_btnColor[i].GetWindowRect(rect);
		ScreenToClient(rect);
		if(rect.PtInRect(point))
		{
			pDoc=
			(
				(CGDIDoc *)((CMainFrame *)
				(
					AfxGetApp()->m_pMainWnd)
				)->GetActiveDocument()
			);
			pDoc->SetBgdIndex(m_btnColor[i].GetPalIndex());
			m_btnFB.Invalidate(FALSE);
			break;
		}
	}
	CDialogBar::OnRButtonDown(nFlags, point);
}

void CColorBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int i, j;
	CRect rect;
	CGDIDoc *pDoc;

	for(i=0; i<COLOR_BUTTON_NUM; i++)
	{
		m_btnColor[i].GetWindowRect(rect);
		ScreenToClient(rect);
		if(rect.PtInRect(point))
		{
			CColorDialog dlg;
			if(dlg.DoModal() == IDOK)
			{
				COLORREF color;
				CPalette *pPal;
				PALETTEENTRY palEntry;

				color=dlg.GetColor();
				pDoc=
				(
					(CGDIDoc *)((CMainFrame *)
					(
						AfxGetApp()->m_pMainWnd)
					)->GetActiveDocument()
				);
				pPal=pDoc->GetPalette();
				ASSERT(pPal->GetSafeHandle());
				palEntry.peRed=GetRValue(color);
				palEntry.peGreen=GetGValue(color);
				palEntry.peBlue=GetBValue(color);
				palEntry.peFlags=NULL;
				pPal->SetPaletteEntries
				(
					m_btnColor[i].GetPalIndex(),
					1,
					&palEntry
				);
				for(j=0; j<COLOR_BUTTON_NUM; j++)m_btnColor[j].Invalidate(FALSE);
				m_btnFB.Invalidate(FALSE);
			}
			break;
		}
	}
	CDialogBar::OnLButtonDblClk(nFlags, point);
}

void CColorBar::UpdateAllButtons()
{
	int i;

	for(i=0; i<COLOR_BUTTON_NUM; i++)m_btnColor[i].Invalidate(FALSE);
	m_btnFB.Invalidate(FALSE);
}
