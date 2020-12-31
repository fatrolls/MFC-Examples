// ex06aDoc.h : interface of the CEx06aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX06ADOC_H__0A7D2CB5_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
#define AFX_EX06ADOC_H__0A7D2CB5_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx06aDoc : public CDocument
{
protected: // create from serialization only
	CEx06aDoc();
	DECLARE_DYNCREATE(CEx06aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx06aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx06aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06ADOC_H__0A7D2CB5_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
