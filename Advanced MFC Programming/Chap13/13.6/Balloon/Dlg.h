#if !defined(AFX_DLG_H__0D5B7B68_3BDF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DLG_H__0D5B7B68_3BDF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CBalloonDlg : public CDialog
{
public:
	CBalloonDlg(CWnd* pParent=NULL);
	//{{AFX_DATA(CBalloonDlg)
	enum { IDD = IDD_BALLOON_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CBalloonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	CPoint m_ptMouse;
	BOOL m_bCapture;
	//{{AFX_MSG(CBalloonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DLG_H__0D5B7B68_3BDF_11D1_9C9A_444553540000__INCLUDED_)
