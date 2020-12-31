// ex04cDoc.h : interface of the CEx04cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04CDOC_H__94911C09_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04CDOC_H__94911C09_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx04cDoc : public CDocument
{
protected: // create from serialization only
	CEx04cDoc();
	DECLARE_DYNCREATE(CEx04cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx04cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04CDOC_H__94911C09_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
