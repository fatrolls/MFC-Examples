// ex11aDoc.h : interface of the CEx11aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11ADOC_H__7D11C12D_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX11ADOC_H__7D11C12D_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx11aDoc : public CDocument
{
protected: // create from serialization only
	CEx11aDoc();
	DECLARE_DYNCREATE(CEx11aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11ADOC_H__7D11C12D_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
