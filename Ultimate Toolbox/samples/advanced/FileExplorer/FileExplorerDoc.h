// FileExplorerDoc.h : interface of the CFileExplorerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEEXPLORERDOC_H__10814F8F_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
#define AFX_FILEEXPLORERDOC_H__10814F8F_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileExplorerDoc : public CDocument
{
protected: // create from serialization only
	CFileExplorerDoc();
	DECLARE_DYNCREATE(CFileExplorerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileExplorerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEXPLORERDOC_H__10814F8F_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
