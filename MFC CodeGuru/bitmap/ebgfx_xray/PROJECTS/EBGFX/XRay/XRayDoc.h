// XRayDoc.h : interface of the CXRayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XRAYDOC_H__1394446D_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_XRAYDOC_H__1394446D_CFB1_11D1_91CA_0020AFF82585__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CXRayDoc : public CDocument
{
protected: // create from serialization only
	CXRayDoc();
	DECLARE_DYNCREATE(CXRayDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXRayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXRayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXRayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRAYDOC_H__1394446D_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
