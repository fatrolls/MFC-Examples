// ex08aDoc.h : interface of the CEx08aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX08ADOC_H__19177891_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08ADOC_H__19177891_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx08aDoc : public CDocument
{
protected: // create from serialization only
	CEx08aDoc();
	DECLARE_DYNCREATE(CEx08aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08ADOC_H__19177891_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
