// ex11Doc.h : interface of the CEx11Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11DOC_H__289CB96C_3A41_11D1_9774_004033298A13__INCLUDED_)
#define AFX_EX11DOC_H__289CB96C_3A41_11D1_9774_004033298A13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx11Doc : public CDocument
{
protected: // create from serialization only
	CEx11Doc();
	DECLARE_DYNCREATE(CEx11Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11DOC_H__289CB96C_3A41_11D1_9774_004033298A13__INCLUDED_)
