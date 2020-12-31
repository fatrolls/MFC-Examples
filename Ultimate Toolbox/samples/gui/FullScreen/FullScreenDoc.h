// FullScreenDoc.h : interface of the CFullScreenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FULLSCREENDOC_H__2690A074_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_)
#define AFX_FULLSCREENDOC_H__2690A074_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFullScreenDoc : public CDocument
{
protected: // create from serialization only
	CFullScreenDoc();
	DECLARE_DYNCREATE(CFullScreenDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFullScreenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFullScreenDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENDOC_H__2690A074_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_)
