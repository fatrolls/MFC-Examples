#if !defined(AFX_EDITVIEW_H__D1C586B6_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_EDITVIEW_H__D1C586B6_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CIniEditView : public CEditView
{
protected:
	CIniEditView();
	DECLARE_DYNCREATE(CIniEditView)

public:
	//{{AFX_VIRTUAL(CIniEditView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

protected:
	virtual ~CIniEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CIniEditView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_EDITVIEW_H__D1C586B6_3E3F_11D1_9C9A_444553540000__INCLUDED_)
