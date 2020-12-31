#if !defined(AFX_STYLEDLG_H__BD4A8884_1D2C_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_STYLEDLG_H__BD4A8884_1D2C_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CStyleDlg : public CDialog
{
public:
	CStyleDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CStyleDlg)
	enum { IDD = IDD_DIALOG_STYLE };
	long	m_lEsp;
	BOOL	m_bBgdStyle;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CStyleDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_STYLEDLG_H__BD4A8884_1D2C_11D1_9C9A_444553540000__INCLUDED_)
