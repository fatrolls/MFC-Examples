// ex15aView.h : interface of the CEx15aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX15AVIEW_H__4D011035_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_)
#define AFX_EX15AVIEW_H__4D011035_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx15aView : public CFormView
{
protected: // create from serialization only
	CEx15aView();
	DECLARE_DYNCREATE(CEx15aView)

public:
	//{{AFX_DATA(CEx15aView)
	enum { IDD = IDD_EX15A_FORM };
	int		m_nGrade;
	CString	m_strName;
	//}}AFX_DATA

// Attributes
public:
	CEx15aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx15aView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx15aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx15aView)
	afx_msg void OnEnter();
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateControlsFromDoc();
};

#ifndef _DEBUG  // debug version in ex15aView.cpp
inline CEx15aDoc* CEx15aView::GetDocument()
   { return (CEx15aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX15AVIEW_H__4D011035_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_)
