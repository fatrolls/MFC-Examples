#if !defined(AFX_DIRVIEW_H__D1AB5354_4563_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DIRVIEW_H__D1AB5354_4563_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include <afxcview.h>

class CDirView : public CTreeView
{
protected:
	CDirView();
	DECLARE_DYNCREATE(CDirView)

public:
	//{{AFX_VIRTUAL(CDirView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

protected:
	virtual ~CDirView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDirView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DIRVIEW_H__D1AB5354_4563_11D1_9C9A_444553540000__INCLUDED_)
