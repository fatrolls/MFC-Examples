// GLTESTDoc.h : interface of the CGLTESTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLTESTDOC_H__8B45E64B_9455_11D1_95A6_E0175F8E7830__INCLUDED_)
#define AFX_GLTESTDOC_H__8B45E64B_9455_11D1_95A6_E0175F8E7830__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGLTESTDoc : public CDocument
{
protected: // create from serialization only
	CGLTESTDoc();
	DECLARE_DYNCREATE(CGLTESTDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLTESTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLTESTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGLTESTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLTESTDOC_H__8B45E64B_9455_11D1_95A6_E0175F8E7830__INCLUDED_)
