// AutoPanDoc.h : interface of the CAutoPanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPANDOC_H__4E9C271E_CFCD_11D1_87BA_400011900025__INCLUDED_)
#define AFX_AUTOPANDOC_H__4E9C271E_CFCD_11D1_87BA_400011900025__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CAutoPanDoc : public CDocument
{
protected: // create from serialization only
	CAutoPanDoc();
	DECLARE_DYNCREATE(CAutoPanDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPanDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPANDOC_H__4E9C271E_CFCD_11D1_87BA_400011900025__INCLUDED_)
