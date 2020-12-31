// HyperbarDemoDoc.h : interface of the CHyperbarDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HYPERBARDEMODOC_H__93024CB4_9B6B_4AA9_A459_CA47E3D6A866__INCLUDED_)
#define AFX_HYPERBARDEMODOC_H__93024CB4_9B6B_4AA9_A459_CA47E3D6A866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHyperbarDemoDoc : public CDocument
{
protected: // create from serialization only
	CHyperbarDemoDoc();
	DECLARE_DYNCREATE(CHyperbarDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperbarDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHyperbarDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHyperbarDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERBARDEMODOC_H__93024CB4_9B6B_4AA9_A459_CA47E3D6A866__INCLUDED_)
