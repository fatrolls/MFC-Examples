#if !defined(AFX_CNTRITEM_H__D065BD85_43C2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CNTRITEM_H__D065BD85_43C2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CWordPadDoc;
class CWordPadView;

class CWordPadCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CWordPadCntrItem)
public:
	CWordPadCntrItem(REOBJECT* preo = NULL, CWordPadDoc* pContainer = NULL);
	CWordPadDoc *GetDocument(){return (CWordPadDoc*)CRichEditCntrItem::GetDocument();}
	CWordPadView *GetActiveView(){return (CWordPadView*)CRichEditCntrItem::GetActiveView();}
	//{{AFX_VIRTUAL(CWordPadCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

public:
	~CWordPadCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CNTRITEM_H__D065BD85_43C2_11D1_9C9A_444553540000__INCLUDED_)
