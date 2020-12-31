#if !defined(AFX_PAGEDIALOG_H__266F38B5_4D6E_11D2_A730_525400DAF3CE__INCLUDED_)
#define AFX_PAGEDIALOG_H__266F38B5_4D6E_11D2_A730_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageDialog dialog

class CPageDialog : public CWnd
{
// Construction
public:
	CPageDialog() : CWnd() { };

	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd, CRect rect,
		UINT nID, DWORD dwStyle=WS_VISIBLE|WS_CHILD);

	virtual BOOL IsRefreshAvailable() { return FALSE; }
	virtual void Refresh() { };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageDialog)
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual void OnInitDialog() { UpdateData(FALSE); }

	// Generated message map functions
	//{{AFX_MSG(CPageDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEDIALOG_H__266F38B5_4D6E_11D2_A730_525400DAF3CE__INCLUDED_)
