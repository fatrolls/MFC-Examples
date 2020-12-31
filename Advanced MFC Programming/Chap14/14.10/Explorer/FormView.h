#if !defined(AFX_FORMVIEW_H__82DF4F21_4700_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_FORMVIEW_H__82DF4F21_4700_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#define BORDER_WIDTH		10

class CDirFormView : public CFormView
{
protected:
	char m_szPath[_MAX_PATH];
	CDirFormView();
	DECLARE_DYNCREATE(CDirFormView)

public:
	CString GetDir(HTREEITEM);
	void AddDirs(HTREEITEM, BOOL);
	void AddChildrenChildren(HTREEITEM);
	void ResizeTreeView();
	//{{AFX_DATA(CDirFormView)
	enum { IDD = IDD_DIALOG_VIEW };
	CTreeCtrl	m_tcDir;
	//}}AFX_DATA

public:
	//{{AFX_VIRTUAL(CDirFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	virtual ~CDirFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//{{AFX_MSG(CDirFormView)
	afx_msg void OnDestroy();
	afx_msg void OnClickTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemExpandingTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_FORMVIEW_H__82DF4F21_4700_11D1_9C9A_444553540000__INCLUDED_)
