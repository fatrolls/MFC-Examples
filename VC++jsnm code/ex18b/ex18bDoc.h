// ex18bDoc.h : interface of the CEx18bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX18BDOC_H__870AB901_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX18BDOC_H__870AB901_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef CArray<CRect, CRect&> CRectArray;

class CEx18bDoc : public CDocument
{
public:
	enum { nLinesPerPage = 12 };
	enum { nMaxEllipses = 50 };
	CRectArray m_ellipseArray;

protected: // create from serialization only
	CEx18bDoc();
	DECLARE_DYNCREATE(CEx18bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx18bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx18bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx18bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18BDOC_H__870AB901_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
