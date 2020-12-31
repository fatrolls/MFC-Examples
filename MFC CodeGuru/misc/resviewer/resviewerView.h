// resviewerView.h : interface of the CResviewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESVIEWERVIEW_H__213309CD_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
#define AFX_RESVIEWERVIEW_H__213309CD_AD73_11D1_8358_00A0244DBC26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//LRESULT RsrcDefDlgProc( HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);

class CResviewerView : public CView
{
protected: // create from serialization only
	CResviewerView();
	DECLARE_DYNCREATE(CResviewerView)

// Attributes
public:
	CResviewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResviewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResviewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResviewerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HGLOBAL m_lpGHDlgTmplt;
	LPVOID m_lpDlgTmplt;
	HWND m_dialogRsrcWnd;
	CDialog *m_mydlg;
	void CreateResourceDialog();
	DWORD m_dwRsrcID;
	DWORD m_dwRsrcType;
	CHAR  m_szRsrcName[255];
};

#ifndef _DEBUG  // debug version in resviewerView.cpp
inline CResviewerDoc* CResviewerView::GetDocument()
   { return (CResviewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESVIEWERVIEW_H__213309CD_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
