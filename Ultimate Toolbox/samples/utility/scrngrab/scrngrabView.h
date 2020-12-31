// scrngrabView.h : interface of the CScrngrabView class
//
/////////////////////////////////////////////////////////////////////////////

#include "OXDIB.h"


class CScrngrabView : public CFormView
{
protected: // create from serialization only
	CScrngrabView();
	DECLARE_DYNCREATE(CScrngrabView)

public:
	//{{AFX_DATA(CScrngrabView)
	enum { IDD = IDD_SCRNGRAB_FORM };
	CStatic	m_stcImage;
	int		m_nCaptOption;
	//}}AFX_DATA

// Attributes
public:
	CScrngrabDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrngrabView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawRslt(COXDIB* pDib);
	virtual ~CScrngrabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bCapturing;

// Generated message map functions
protected:
	//{{AFX_MSG(CScrngrabView)
	afx_msg void OnCaptButton();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptButtonEntire();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in scrngrabView.cpp
inline CScrngrabDoc* CScrngrabView::GetDocument()
   { return (CScrngrabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
