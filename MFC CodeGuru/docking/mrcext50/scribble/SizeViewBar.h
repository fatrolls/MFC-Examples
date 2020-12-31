#if !defined(AFX_SIZEVIEWBAR_H__14EC9881_72DD_11D1_BA8A_006097DA5345__INCLUDED_)
#define AFX_SIZEVIEWBAR_H__14EC9881_72DD_11D1_BA8A_006097DA5345__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SizeViewBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSizeViewBar window

class CSizeViewBar : public CMRCSizeControlBar
{
	DECLARE_DYNCREATE(CSizeViewBar)
	// Construction
public:
	CSizeViewBar();

// Attributes
public:
	CView	* m_pChildView;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizeViewBar)
	//}}AFX_VIRTUAL
	void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

// Implementation
public:
	virtual ~CSizeViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSizeViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CSizeBarDocTemplate : public CMultiDocTemplate
{
public:
	DECLARE_DYNAMIC(CSizeBarDocTemplate)
	CSizeBarDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
										 CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	//CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther);
	CDocument* OpenDocumentFile(LPCTSTR lpszPathName,
		BOOL bMakeVisible);

	CFrameWnd* CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIZEVIEWBAR_H__14EC9881_72DD_11D1_BA8A_006097DA5345__INCLUDED_)
