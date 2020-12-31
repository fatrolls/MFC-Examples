// CntrItem.h : interface of the CMyWordCntrItem class
//

#if !defined(AFX_CNTRITEM_H__C85C9090_A154_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_CNTRITEM_H__C85C9090_A154_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyWordDoc;
class CMyWordView;

class CMyWordCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CMyWordCntrItem)

// Constructors
public:
	CMyWordCntrItem(REOBJECT* preo = NULL, CMyWordDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CMyWordDoc* GetDocument()
		{ return (CMyWordDoc*)CRichEditCntrItem::GetDocument(); }
	CMyWordView* GetActiveView()
		{ return (CMyWordView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWordCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CMyWordCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__C85C9090_A154_11D2_8E53_006008A82731__INCLUDED_)
