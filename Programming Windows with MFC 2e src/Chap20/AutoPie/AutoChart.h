#if !defined(AFX_AUTOCHART_H__3B5BA31E_3B72_11D2_AC82_006008A8274D__INCLUDED_)
#define AFX_AUTOCHART_H__3B5BA31E_3B72_11D2_AC82_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoChart.h : header file
//

#define ID_ERROR_OUTOFRANGE 100

/////////////////////////////////////////////////////////////////////////////
// CAutoChart command target

class CAutoChart : public CCmdTarget
{
	DECLARE_DYNCREATE(CAutoChart)

	CAutoChart();           // protected constructor used by dynamic creation

// Attributes
public:
	virtual ~CAutoChart();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoChart)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAutoChart)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAutoChart)
	afx_msg BOOL Save(LPCTSTR pszPath);
	afx_msg long GetRevenue(short nQuarter);
	afx_msg void SetRevenue(short nQuarter, long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCHART_H__3B5BA31E_3B72_11D2_AC82_006008A8274D__INCLUDED_)
