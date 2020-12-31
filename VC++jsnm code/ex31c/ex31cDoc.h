// ex31cDoc.h : interface of the CEx31cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31CDOC_H__496552FB_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
#define AFX_EX31CDOC_H__496552FB_957C_11D0_85C0_97AC5D47DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx31cDoc : public CRichEditDoc
{
protected: // create from serialization only
	CEx31cDoc();
	DECLARE_DYNCREATE(CEx31cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CEx31cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31CDOC_H__496552FB_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
