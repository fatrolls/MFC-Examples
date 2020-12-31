// ex04aDoc.h : interface of the CEx04aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04ADOC_H__B188BE3F_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04ADOC_H__B188BE3F_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx04aDoc : public CDocument
{
protected: // create from serialization only
	CEx04aDoc();
	DECLARE_DYNCREATE(CEx04aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx04aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04ADOC_H__B188BE3F_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
