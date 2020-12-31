// SrvrItem.h : interface of the CEx27aSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__1EAAB6CA_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_SRVRITEM_H__1EAAB6CA_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx27aSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CEx27aSrvrItem)

// Constructors
public:
	CEx27aSrvrItem(CEx27aDoc* pContainerDoc);

// Attributes
	CEx27aDoc* GetDocument() const
		{ return (CEx27aDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27aSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx27aSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__1EAAB6CA_6011_11D0_848F_00400526305B__INCLUDED_)
