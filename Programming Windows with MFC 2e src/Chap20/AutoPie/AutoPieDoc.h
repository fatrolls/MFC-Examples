// AutoPieDoc.h : interface of the CAutoPieDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPIEDOC_H__3B5BA312_3B72_11D2_AC82_006008A8274D__INCLUDED_)
#define AFX_AUTOPIEDOC_H__3B5BA312_3B72_11D2_AC82_006008A8274D__INCLUDED_

#include "AutoChart.h"	// Added by ClassView
#include "AutoWindow.h"	// Added by ClassView
#include "AutoToolbar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoPieDoc : public CDocument
{
protected: // create from serialization only
	CAutoPieDoc();
	DECLARE_DYNCREATE(CAutoPieDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPieDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRevenue (int nQuarter, int nNewValue);
	int GetRevenue (int nQuarter);
	virtual ~CAutoPieDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CAutoToolbar m_autoToolbar;
	CAutoWindow m_autoWindow;
	CAutoChart m_autoChart;
	int m_nRevenues[4];
	//{{AFX_MSG(CAutoPieDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAutoPieDoc)
	afx_msg LPDISPATCH GetChart();
	afx_msg void SetChart(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetWindow();
	afx_msg void SetWindow(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetToolbar();
	afx_msg void SetToolbar(LPDISPATCH newValue);
	afx_msg void Quit();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPIEDOC_H__3B5BA312_3B72_11D2_AC82_006008A8274D__INCLUDED_)
