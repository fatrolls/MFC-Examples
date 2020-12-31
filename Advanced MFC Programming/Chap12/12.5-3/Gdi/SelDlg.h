#if !defined(AFX_SELDLG_H__62BD6401_2F60_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_SELDLG_H__62BD6401_2F60_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CSelDlg : public CDialog
{
public:
	CSelDlg(CWnd *pParent = NULL);
	HWND GetSelectedWnd(){return m_hWnd;}
	void DrawSelection(CPoint, BOOL=FALSE);

	//{{AFX_DATA(CSelDlg)
	enum { IDD = IDD_DIALOG_SELECT };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	BOOL m_bCaptureOn;
	HICON m_iconCursor;
	HICON m_iconBlank;
	HCURSOR m_curSelect;
	HCURSOR m_curSave;
	CRect m_rectSelect;
	HWND m_hWnd;
	//{{AFX_MSG(CSelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SELDLG_H__62BD6401_2F60_11D1_9C9A_444553540000__INCLUDED_)
