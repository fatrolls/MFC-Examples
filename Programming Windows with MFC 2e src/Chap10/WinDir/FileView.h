// FileView.h : interface of the CFileView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVIEW_H__18BD7B80_95C6_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_FILEVIEW_H__18BD7B80_95C6_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagITEMINFO {
    CString     strFileName; 
    DWORD       nFileSizeLow; 
    FILETIME    ftLastWriteTime; 
} ITEMINFO;

class CFileView : public CListView
{
protected: // create from serialization only
	CFileView();
	DECLARE_DYNCREATE(CFileView)

// Attributes
public:
	CWinDirDoc* GetDocument();

// Operations
public:
	static int CALLBACK CompareFunc (LPARAM lParam1, LPARAM lParam2,
	    LPARAM lParamSort);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	int Refresh (LPCTSTR pszPath);
	virtual ~CFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CString m_strPath;
	void FreeItemMemory ();
	BOOL AddItem (int nIndex, WIN32_FIND_DATA* pfd);
	CImageList m_ilSmall;
	CImageList m_ilLarge;
	//{{AFX_MSG(CFileView)
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnFileNewDirectory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FileView.cpp
inline CWinDirDoc* CFileView::GetDocument()
   { return (CWinDirDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEVIEW_H__18BD7B80_95C6_11D2_8E53_006008A82731__INCLUDED_)
