// StuView.h : interface of the CStudentView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUVIEW_H__1A036EAB_821A_11D0_8FE2_00C04FC2A0C2__INCLUDED_)
#define AFX_STUVIEW_H__1A036EAB_821A_11D0_8FE2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CStudentView : public CFormView
{
protected:
	POSITION      m_position; // current position in document list
	CStudentList* m_pList;    // copied from document

protected: // create from serialization only
	CStudentView();
	DECLARE_DYNCREATE(CStudentView)

public:
	//{{AFX_DATA(CStudentView)
	enum { IDD = IDD_STUDENT };
	int		m_nGrade;
	CString	m_strName;
	//}}AFX_DATA

// Attributes
public:
	CStudentDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStudentView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStudentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void ClearEntry();
	virtual void InsertEntry(POSITION position);
	virtual void GetEntry(POSITION position);

// Generated message map functions
protected:
	//{{AFX_MSG(CStudentView)
	afx_msg void OnClear();
	afx_msg void OnCommandHome();
	afx_msg void OnCommandEnd();
	afx_msg void OnCommandPrev();
	afx_msg void OnCommandNext();
	afx_msg void OnCommandIns();
	afx_msg void OnCommandDel();
	afx_msg void OnUpdateCommandHome(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandDel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StuView.cpp
inline CStudentDoc* CStudentView::GetDocument()
   { return (CStudentDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUVIEW_H__1A036EAB_821A_11D0_8FE2_00C04FC2A0C2__INCLUDED_)
