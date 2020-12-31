// OcxTestDoc.h : interface of the COcxTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCXTESTDOC_H__ED5CE7A4_B2C3_11D0_968D_444553540000__INCLUDED_)
#define AFX_OCXTESTDOC_H__ED5CE7A4_B2C3_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COcxTestDoc : public CDocument
{
protected: // create from serialization only
	COcxTestDoc();
	DECLARE_DYNCREATE(COcxTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COcxTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COcxTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COcxTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXTESTDOC_H__ED5CE7A4_B2C3_11D0_968D_444553540000__INCLUDED_)
