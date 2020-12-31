#include "stdafx.h"
#include "GDI.h"
#include "SelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSelDlg::CSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelDlg)
	//}}AFX_DATA_INIT
	m_bCaptureOn=FALSE;
	m_iconCursor=AfxGetApp()->LoadIcon(IDI_ICON_CURSOR);
	ASSERT(m_iconCursor);
	m_iconBlank=AfxGetApp()->LoadIcon(IDI_ICON_BLANK);
	ASSERT(m_iconBlank);
	m_curSelect=AfxGetApp()->LoadCursor(IDC_CURSOR_SELECT);
	ASSERT(m_curSelect);
	m_hWnd=NULL;
}

void CSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelDlg, CDialog)
	//{{AFX_MSG_MAP(CSelDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;
}

void CSelDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;

	CDialog::OnLButtonDown(nFlags, point);
	GetDlgItem(IDC_STATIC_CURSOR)->GetWindowRect(rect);
	ScreenToClient(rect);
	if(rect.PtInRect(point))
	{
		SetCapture();
		((CStatic *)GetDlgItem(IDC_STATIC_CURSOR))->SetIcon(m_iconBlank);
		GetDlgItem(IDC_STATIC_CURSOR)->Invalidate();
		m_curSave=::SetCursor(m_curSelect);
		m_bCaptureOn=TRUE;
		m_rectSelect=CRect(0, 0, 0, 0);
		m_hWnd=NULL;
	}
}

void CSelDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	if(m_bCaptureOn == TRUE)
	{
		DrawSelection(point, TRUE);
		::ReleaseCapture();
		((CStatic *)GetDlgItem(IDC_STATIC_CURSOR))->SetIcon(m_iconCursor);
		::SetCursor(m_curSave);
		m_bCaptureOn=FALSE;
	}
}

void CSelDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	DrawSelection(point);
	CDialog::OnMouseMove(nFlags, point);
}

void CSelDlg::DrawSelection(CPoint point, BOOL bErase)
{
	if(m_bCaptureOn == TRUE)
	{
		CWnd *pWnd;
		CWindowDC dc(CWnd::GetDesktopWindow());
		int nRop2Mode;
		CRgn rgn;
		CRgn rgnDesk;
		CRect rect;

		GetWindowRect(rect);
		rgn.CreateRectRgnIndirect(rect);
		AfxGetApp()->m_pMainWnd->GetWindowRect(rect);
		rgnDesk.CreateRectRgnIndirect(rect);
		rgn.CombineRgn(&rgnDesk, &rgn, RGN_OR);
		rgnDesk.DeleteObject();
		CWnd::GetDesktopWindow()->GetWindowRect(rect);
		rgnDesk.CreateRectRgnIndirect(rect);
		rgn.CombineRgn(&rgnDesk, &rgn, RGN_DIFF);
		dc.SelectClipRgn(&rgn);

		nRop2Mode=dc.SetROP2(R2_NOT);

		ClientToScreen(&point);
		pWnd=WindowFromPoint(point);

		if
		(
		     pWnd->GetSafeHwnd() != GetSafeHwnd() && 
			 pWnd->GetSafeHwnd() != AfxGetApp()->m_pMainWnd->GetSafeHwnd()
	    )
		{
			if(pWnd->GetSafeHwnd() != m_hWnd)
			{
				if(m_rectSelect.IsRectEmpty() != TRUE)
				{
					dc.Rectangle(m_rectSelect);
				}
				pWnd->GetWindowRect(m_rectSelect);
				dc.Rectangle(m_rectSelect);
				m_hWnd=pWnd->GetSafeHwnd();
			}
		}
		else
		{
			if(m_rectSelect.IsRectEmpty() != TRUE)
			{
				dc.Rectangle(m_rectSelect);
				m_rectSelect=CRect(0, 0, 0, 0);
			}
			m_hWnd=NULL;
		}
		if(bErase == TRUE && m_rectSelect.IsRectEmpty() != TRUE)
		{
			dc.Rectangle(m_rectSelect);
			m_rectSelect=CRect(0, 0, 0, 0);
		}
		
		dc.SetROP2(nRop2Mode);
		dc.SelectClipRgn(NULL);
	}
}
