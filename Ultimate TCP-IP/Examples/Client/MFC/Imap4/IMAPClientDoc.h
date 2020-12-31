// IMAPClientDoc.h : interface of the CIMAPClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAPCLIENTDOC_H__1FE0A7DA_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_IMAPCLIENTDOC_H__1FE0A7DA_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning ( disable : 4511 4512 )


class CIMAPClientDoc : public CDocument
{
protected: // create from serialization only
	CIMAPClientDoc();
	DECLARE_DYNCREATE(CIMAPClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMAPClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIMAPClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIMAPClientDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAPCLIENTDOC_H__1FE0A7DA_27E9_11D3_B75D_00203596449E__INCLUDED_)
