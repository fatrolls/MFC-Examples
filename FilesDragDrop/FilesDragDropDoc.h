// FilesDragDropDoc.h : interface of the CFilesDragDropDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESDRAGDROPDOC_H__131ADCE5_B7CC_4114_9666_B8D3057FF7B6__INCLUDED_)
#define AFX_FILESDRAGDROPDOC_H__131ADCE5_B7CC_4114_9666_B8D3057FF7B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFilesDragDropDoc : public CDocument
{
protected: // create from serialization only
	CFilesDragDropDoc();
	DECLARE_DYNCREATE(CFilesDragDropDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesDragDropDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilesDragDropDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilesDragDropDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESDRAGDROPDOC_H__131ADCE5_B7CC_4114_9666_B8D3057FF7B6__INCLUDED_)
