// ex26aDoc.h : interface of the CEx26aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26ADOC_H__BE45444F_5F51_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26ADOC_H__BE45444F_5F51_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx26aDoc : public CDocument
{
protected: // create from serialization only
	CEx26aDoc();
	DECLARE_DYNCREATE(CEx26aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26ADOC_H__BE45444F_5F51_11D0_848F_00400526305B__INCLUDED_)
