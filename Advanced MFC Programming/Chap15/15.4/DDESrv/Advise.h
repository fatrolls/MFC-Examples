#if !defined(AFX_ADVISE_H__D31D4041_4AE9_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_ADVISE_H__D31D4041_4AE9_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CAdviseDialog : public CDialog
{
public:
	CAdviseDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CAdviseDialog)
	enum { IDD = IDD_DIALOG_ADVISE };
	CString	m_szText;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAdviseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdviseDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ADVISE_H__D31D4041_4AE9_11D1_9C9A_444553540000__INCLUDED_)
