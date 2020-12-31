// ImageViewerDoc.h : interface of the CImageViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEVIEWERDOC_H__AEC8616D_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
#define AFX_IMAGEVIEWERDOC_H__AEC8616D_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageViewerDoc : public CDocument
{
protected: // create from serialization only
	CImageViewerDoc();
	DECLARE_DYNCREATE(CImageViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEWERDOC_H__AEC8616D_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
