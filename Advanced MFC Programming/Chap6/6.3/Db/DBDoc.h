#if !defined(AFX_DBDOC_H__6F1FA2E0_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBDOC_H__6F1FA2E0_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "PSht.h"

class CDBDoc : public CDocument
{
protected:
	CMLPropertySheet *m_ptrDlg;
	CDBDoc();
	DECLARE_DYNCREATE(CDBDoc)

public:
	//{{AFX_VIRTUAL(CDBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDBDoc)
	afx_msg void OnPropertysheetModeless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBDOC_H__6F1FA2E0_130A_11D1_9C9A_444553540000__INCLUDED_)
