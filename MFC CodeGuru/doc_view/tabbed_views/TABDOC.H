// TabDoc.h : interface of the CTabDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABDOC_H__E22ADFAE_5063_11D1_8E9B_4854E827046F__INCLUDED_)
#define AFX_TABDOC_H__E22ADFAE_5063_11D1_8E9B_4854E827046F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTabDoc : public CDocument
{
protected: // create from serialization only
	CTabDoc();
	DECLARE_DYNCREATE(CTabDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDOC_H__E22ADFAE_5063_11D1_8E9B_4854E827046F__INCLUDED_)
