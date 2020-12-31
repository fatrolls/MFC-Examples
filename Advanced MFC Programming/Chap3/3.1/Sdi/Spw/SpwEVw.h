#if !defined(AFX_SPWEVW_H__D3F202B6_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWEVW_H__D3F202B6_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CSpwEView : public CEditView
{
protected:
	CSpwEView();
	DECLARE_DYNCREATE(CSpwEView)

public:
	//{{AFX_VIRTUAL(CSpwEView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

protected:
	virtual ~CSpwEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CSpwEView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SPWEVW_H__D3F202B6_FC3A_11D0_9C9A_444553540000__INCLUDED_)
