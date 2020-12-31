#if !defined(AFX_TEXTVIEW_H__9A773A62_342E_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_TEXTVIEW_H__9A773A62_342E_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CTextView : public CEditView
{
protected:
	CTextView();
	DECLARE_DYNCREATE(CTextView)

public:
	//{{AFX_VIRTUAL(CTextView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

protected:
	virtual ~CTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CTextView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TEXTVIEW_H__9A773A62_342E_11D1_9C9A_444553540000__INCLUDED_)
