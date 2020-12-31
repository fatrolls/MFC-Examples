// MdLessPpshDoc.h : interface of the CMdLessPpshDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDLESSPPSHDOC_H__D1BCD702_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_MDLESSPPSHDOC_H__D1BCD702_F032_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMdLessPpshDoc : public CDocument
{
protected: // create from serialization only
	CMdLessPpshDoc();
	DECLARE_DYNCREATE(CMdLessPpshDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdLessPpshDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMdLessPpshDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMdLessPpshDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDLESSPPSHDOC_H__D1BCD702_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
