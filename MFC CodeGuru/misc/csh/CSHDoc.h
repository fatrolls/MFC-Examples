// CSHDoc.h : interface of the CCSHDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSHDOC_H__73AC62DE_CCD6_11D1_8018_A601086D0638__INCLUDED_)
#define AFX_CSHDOC_H__73AC62DE_CCD6_11D1_8018_A601086D0638__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCSHDoc : public CDocument
{
protected: // create from serialization only
	CCSHDoc();
	DECLARE_DYNCREATE(CCSHDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSHDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCSHDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCSHDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHDOC_H__73AC62DE_CCD6_11D1_8018_A601086D0638__INCLUDED_)
