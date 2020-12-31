// CntrItem.h : interface of the CEx31cCntrItem class
//

#if !defined(AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
#define AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx31cDoc;
class CEx31cView;

class CEx31cCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEx31cCntrItem)

// Constructors
public:
	CEx31cCntrItem(REOBJECT* preo = NULL, CEx31cDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CEx31cDoc* GetDocument()
		{ return (CEx31cDoc*)CRichEditCntrItem::GetDocument(); }
	CEx31cView* GetActiveView()
		{ return (CEx31cView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31cCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx31cCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
