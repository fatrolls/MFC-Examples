// ex13aDoc.h : interface of the CEx13aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX13ADOC_H__DFF9FC29_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
#define AFX_EX13ADOC_H__DFF9FC29_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx13aDoc : public CDocument
{
protected: // create from serialization only
	CEx13aDoc();
	DECLARE_DYNCREATE(CEx13aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx13aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx13aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX13ADOC_H__DFF9FC29_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
